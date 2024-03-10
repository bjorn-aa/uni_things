#include "./sensorLib.h"

int fd2;
int weightArray[4] = {0,0,0,0};

//Initialization of GPIO and serial communication.
void SensorInit(void)
{
	system("echo 22 > /sys/class/gpio/export");
    system("echo out > /sys/class/gpio/gpio22/direction");
	
	wiringPiSetup();
	if((fd2=serialOpen("/dev/ttyACM0",9600))<0){
		std::cout << "Unable to open serial device" << std::endl;
		if((fd2=serialOpen("/dev/ttyACM1",9600))<0){
			std::cout << "Unable to open serial device" << std::endl;
			if((fd2=serialOpen("/dev/ttyACM2",9600))<0){
			std::cout << "Unable to open serial device" << std::endl;
				if((fd2=serialOpen("/dev/ttyACM3",9600))<0){
					std::cout << "Unable to open serial device" << std::endl;
				}
			}
		}
	}
}

//Function for retrieving weight information from Arduino.
int GetWeight(void)
{
	int weight = 0;
	system("echo 0 > /sys/class/gpio/gpio22/value");
	
	//Characters to circular array.
	while(1)
	{
		for(int i=0; i<3; i++)
		{
			weightArray[i] = weightArray[i+1];
		}
		weightArray[3] = serialGetchar(fd2);
		
		if (weightArray[0] == 10)
			break;
	}
	
	//Array to integer.
	if (weightArray[0] == 10 && weightArray[2] == 13 && weightArray[3] == 10)
		weight = 0;
	else
		weight = (weightArray[1]-48)*100 + (weightArray[2]-48)*10 + (weightArray[3]-48);

	//Resetting array.
	for (int i=0; i<4; i++)
	{
		weightArray[i] = 0;
	}
	
	//Flushing serial.
	serialFlush(fd2);
	
	return weight*10;
}

//Function for retrieving ultrasonic sensor information from Arduino.
	uint8_t UltrasonicCheck(void)
{	
	int value = 0;
	system("echo 1 > /sys/class/gpio/gpio22/value");
	//Getting character and changing to integer.
	value = serialGetchar(fd2) - 48;
	
	serialFlush(fd2);
	
	std::cout << "ultrasonic value: " << value << std::endl;
	
	if (value == 1 || value == 2 || value == 3 || value == 5 || value == 7 || value == 9 || value == 10 || value == 11 || value == 13 || value == 14 || value == 16)
		return ULTRASONIC_LEFT;
	else
	if (value == 4 || value == 6 || value == 12 || value == 15)
		return ULTRASONIC_RIGHT;
	else
	return 0;
	

	
}