#include "./wireSensorLibN.h"

int wInterp1[6] = {0};
int wInterp2[6] = {0};
int fd;
char previousChar = '0';
int currentDigit = 0;
int dataArray[4] = {0,0,0,0};
int wireLimit1 = 500;
int wireLimit2 = 500;
volatile int wireInput1 = 0;
volatile int wireInput2 = 0;	
pthread_t wireID;

//Writing distance settings to file.
int FileToVar(int interpolation)
{
	int currentInterp = 0;
	std::string interpstr;
	std::string str = "/home/pi/sem5/savedValues/wInterp" + std::to_string(interpolation) + ".txt";
	const char* file = str.c_str();
	
	std::ifstream interpFile (file);
	if (interpFile.is_open())
	{
		while(getline(interpFile, interpstr))
		{
			std::istringstream ss(interpstr);
			ss >> currentInterp;
			//std::cout << interpstr << std::endl;
		}
		interpFile.close();
	}
	return currentInterp;
}

//Function for writing file.
void WriteFile(int input, int file)
{
	std::string str = "echo " + std::to_string(input) + " > /home/pi/sem5/savedValues/wInterp" + std::to_string(file) + ".txt";
	const char* dataToWrite = str.c_str();
	system(dataToWrite);
}

//Retrieving sensor limit from file to variable.
int LimitToVar(int sensor)
{
	int currentLimit = 0;
	std::string limitstr;
	std::string str = "/home/pi/sem5/savedValues/limit" + std::to_string(sensor) + ".txt";
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
	std::string str = "echo " + std::to_string(limit) + " > /home/pi/sem5/savedValues/limit" + std::to_string(sensor) + ".txt";
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
	
	//int wireInput1 = 0;
	//int wireInput2 = 0;
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
	
	//Setting and receiving distance calibration information.
	wInterp1[2] = 10;
	wInterp2[2] = 10;
	wInterp1[4] = 50;
	wInterp2[4] = 50;
	
	wInterp1[3] = FileToVar(0);
	wInterp2[3] = FileToVar(1);
	wInterp1[5] = FileToVar(2);
	wInterp2[5] = FileToVar(3);
	
	wireLimit1 = LimitToVar(0);
	wireLimit2 = LimitToVar(1);
	
	std::cout << "Current wire limit right: " << wireLimit1 << std::endl;
	std::cout << "Current wire limit left: " << wireLimit2 << std::endl;
	
	//std::cout << wInterp1[3] << std::endl;
	
	if(!wInterp1[3] || !wInterp1[5] || !wInterp2[3] || !wInterp2[5])
	{
		//WireCal();
	}
		
}

//Retrieving current distance calibration.
void WireCalCurrent(void)
{
	std::cout << FileToVar(0) << std::endl;
	std::cout << FileToVar(1) << std::endl;
	std::cout << FileToVar(2) << std::endl;
	std::cout << FileToVar(3) << std::endl;
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

void WireLimit(int limit1, int limit2)
{
	wireLimit1 = limit1;
	wireLimit2 = limit2;
}

//Function that returns true if one of the wire values is above the limit.
bool WireClose(void)
{
	//std::cout << wireInput1 << "   " << wireInput2 << std::endl;
	
	if (wireInput1 > wireLimit1 || wireInput2 > wireLimit2)
		return TRUE;
	else
		return FALSE;
}

