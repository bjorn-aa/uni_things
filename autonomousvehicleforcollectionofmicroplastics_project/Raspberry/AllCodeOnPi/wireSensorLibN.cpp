#include "./wireSensorLibN.h"

int fd;
char previousChar = '0';
int currentDigit = 0;
int dataArray[4] = {0,0,0,0};
int wireLimit1 = 600;
int wireLimit2 = 600;
int wireUpperLimit1 = 780;
int wireUpperLimit2 = 780;
volatile int wireInput1 = 0;
volatile int wireInput2 = 0;	
pthread_t wireID;

//Retrieving sensor limit from file to variable.
int LimitToVar(int sensor)
{
	int currentLimit = 0;
	std::string limitstr;
	std::string str = "./savedValues/limit" + std::to_string(sensor) + ".txt";
	const char* file = str.c_str();
	
	std::ifstream limitFile (file);
	if (limitFile.is_open())
	{
		while(getline(limitFile, limitstr))
		{
			std::istringstream ss(limitstr);
			ss >> currentLimit;
		}
		limitFile.close();
	}
	return currentLimit;
}

//Writing sensor limit to file.
void WriteLimit(int limit, int sensor)
{
	std::string str = "echo " + std::to_string(limit) + " > ./savedValues/limit" + std::to_string(sensor) + ".txt";
	const char* dataToWrite = str.c_str();
	system(dataToWrite);
}

//Thread for receiving the wire sensor information from Arduino.
void* WireThread(void* vptr)
{
	wiringPiSetup();
	pinMode(29, OUTPUT);
	
	if((fd=serialOpen("/dev/ttyUSB0",115200))<0){
    std::cout << "Unable to connect to Nano" << std::endl;
	if((fd=serialOpen("/dev/ttyUSB1",115200))<0){
    std::cout << "Unable to connect to Nano" << std::endl;
	if((fd=serialOpen("/dev/ttyUSB2",115200))<0){
    std::cout << "Unable to connect to Nano" << std::endl;
	if((fd=serialOpen("/dev/ttyUSB3",115200))<0){
    std::cout << "Unable to connect to Nano" << std::endl;
	}
	}
	}
	}
	
	int rawInput = 0;
	int sensor = 0;
	
	//Sending high or low to Arduino GPIO.
	while(1)
	{
	if (!sensor)
		digitalWrite(29, LOW);
	else
		digitalWrite(29, HIGH);
	
	usleep(100000);
	
	//Adding characters to circular array.
	while(1)
	{
		for(int i=0; i<3; i++)
		{
			dataArray[i] = dataArray[i+1];
		}
		dataArray[3] = serialGetchar(fd);
		
		if (dataArray[0] == 10)
			break;
	}
	
	//Characters from array to integer.
	if (dataArray[0] == 10 && dataArray[2] == 13 && dataArray[3] == 10)
		rawInput = 0;
	else
		rawInput = (dataArray[1]-48)*100 + (dataArray[2]-48)*10 + (dataArray[3]-48);

	//Resetting array.
	for (int i=0; i<4; i++)
	{
		dataArray[i] = 0;
	}
	
	//Flushing serial.
	serialFlush(fd);
	
	//std::cout << rawInput << std::endl;
	
	//Writing to global variable.
	if(!sensor)
	{
		wireInput1 = rawInput;
		//std::cout << wireInput1 << std::endl;
		sensor++;
	}
	else
	{
		wireInput2 = rawInput;
		//std::cout << wireInput2 << std::endl;
		sensor = 0;
	}
	}
}

//Initialization of wire sensing.
void WireInit(void)
{
	system("sudo mkdir savedValues");
	
	//Setting up wiringPi.
	wiringPiSetup();
	
	//Creating and starting wire sensing thread.
	pthread_create( &wireID, NULL, &WireThread, NULL);
	
	wireLimit1 = LimitToVar(0);
	wireLimit2 = LimitToVar(1);
	
	std::cout << "Current wire limit right: " << wireLimit1 << std::endl;
	std::cout << "Current wire limit left: " << wireLimit2 << std::endl;		
}

//Reading the wire sensor information set by the thread.
int WireRead(int sensor)
{	
	int returnValue = 0;
	if(!sensor)
		returnValue = wireInput1;
	else
		returnValue = wireInput2;
	
	return returnValue;
}

int WireReadProportional(int sensor)
{	
	int returnValue = 0;
	if(!sensor)
		returnValue = ceil((wireInput1/wireLimit1)*1000);
	else
		returnValue = ceil((wireInput2/wireLimit2)*1000);
	//
	std::cout << wireInput1 << "  " << wireInput2 << std::endl;
	std::cout << returnValue << std::endl;	
	
	return returnValue;
}

void WireLimit(int limit1, int limit2)
{
	wireLimit1 = limit1;
	wireLimit2 = limit2;
	WriteLimit(WIRE_SENSOR_RIGHT, limit1);
	WriteLimit(WIRE_SENSOR_LEFT, limit2);
}

//Function that returns true if one of the wire values is above the limit.
bool WireClose(void)
{
	if (wireInput1 > wireLimit1 || wireInput2 > wireLimit2)
		return TRUE;
	else
		return FALSE;
}

bool WireClose(int sensor)
{
	if (!sensor)
	{
		if (wireInput1 > wireLimit1)
			return TRUE;
		else
			return FALSE;
	}
	else
	{
		if (wireInput2 > wireLimit2)
			return TRUE;
		else
			return FALSE;
	}
}
