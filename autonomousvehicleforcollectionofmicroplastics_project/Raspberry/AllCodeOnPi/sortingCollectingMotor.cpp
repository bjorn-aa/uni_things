#include "sortingCollectingMotor.h"

int motorPin = 0;

void initSortingCollectingMotor(int pin)
{
	wiringPiSetup();
	softPwmCreate(pin, 0, RANGE);
	motorPin = pin;
}

void startSortingCollectingMotor(int range)
{
	if(range > 10) range = 10;
	else if (range < 0) range = 0;
		
	softPwmWrite(motorPin, range) ;
    delay(10);
}

void stopSortingCollectingMotor()
{
	softPwmStop(motorPin);
}