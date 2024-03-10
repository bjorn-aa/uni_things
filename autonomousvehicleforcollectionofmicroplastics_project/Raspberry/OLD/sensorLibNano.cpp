#include "./sensorLibNano.h"

// Dont like useing global but w/e :I 
int errorLogger[3];
bool At_Base = flase; 
bool ErrorCheck;
//
// ------------------------- Changed WireSensorLibN below ---------------------------

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

//Initialization of wire sensing.
void WireInit(void)
{
	system("sudo mkdir savedValues");
	
	// Setting up for other sensor 
	errorLogger[3] = {0,0,0,0};
	ErrorCheck = false; 
	
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

//Thread for receiving the wire sensor information from Arduino.
void* WireThread(void* vptr)
{
	wiringPiSetup();
	pinMode(29, OUTPUT);
	pinMode(28, OUTPUT);
	
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
	
	while(1)
	{
		//Sending high or low to Arduino GPIO.
		if (sensor == 0){						// Retrive data for left(?) wire sensor
			digitalWrite(28, HIGH);				// GPIO 20
			digitalWrite(29, LOW);				// GPIO 21
		}
		else if (sensor == 1){					// Retrive data for right(?) wire sensor
			digitalWrite(28, LOW);				// GPIO 20
			digitalWrite(29, HIGH);				// GPIO 21
		}
		else if (sensor == 2){					// Retrive data for rando sensor 
			digitalWrite(28, HIGH);				// GPIO 20
			digitalWrite(29, HIGH);				// GPIO 21
		}
		else 
			break;
		
		usleep(100000);							// Why sleep for so long? 
		
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
		if(sensor == 0)									// Get from left wire sensor
		{
			wireInput1 = rawInput;
			//std::cout << wireInput1 << std::endl;
			sensor++;
		}
		if(sensor == 1)									// Get from right wire sensor
		{
			wireInput2 = rawInput;
			//std::cout << wireInput2 << std::endl;
			sensor++;
		}
		else if(sensor == 2)							// Get from other sensor
		{
			GetOther(rawInput);
			//std::cout << rawInput << std::endl;
			sensor = 0;
		}
		else
		{
			sensor = 0;
		}
	}
	
}

// ------------------------- Changed WireSensorLibN Above ---------------------------
// ------------------------- UnChanged WireSensorLibN below ---------------------------

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


// ------------------------- UnChanged WireSensorLibN above ---------------------------

void GetOther(int value)
{
	
	if (value & (1 << 0) )									// Temp is high! 					Error Something Wrong! 
		ErrorOther(Error_1);
	if (value & (1 << 1) )									// Humididy is high! 				Error Something Wrong! 
		ErrorOther(Error_2);
	if (value & (1 << 2) )									// Its raining! 					Return to base!
		RainOn();
	if (value & (1 << 3) )									// Robots at base! 					Upload data! 
		AtBase();
}

bool AtBase(void)
{
	// At base, stop motors and upload stuff to db
	At_Base = 1;
	return At_Base;
}

void RainOn(void)
{
	// Its raining, log into db and return to base
	ErrorCheck = true;
	errorLogger[0] = 1;
	ReturnToBase();
}

void ErrorOther(int temp)
{
	// Some action when there is a error 
	if (temp == Error_1)
	{
		// Error temp 2 high, log into db and take action 
		ErrorCheck = true;
		errorLogger[1] = 1;
		MotorVelocity(0);
	}
	if (temp == Error_2)
	{
		// Error humidid 2 high, log into db and take action
		ErrorCheck = true; 
		errorLogger[2] = 1;	
		MotorVelocity(0);
	}
}