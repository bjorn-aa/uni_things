#include "./pwmLibMini.h"
#include "./wireSensorLibN.h"
#include "./sensorLib.h"
#include "./autonomousMode.h"


int main(void)
{
	wiringPiSetup();
	pinMode(28, INPUT);
	
	MotorInit();
	WireInit();
	SensorInit();
	WireLimit(600, 600);
	
	MotorDirection(FORWARD);
	MotorVelocity(90);
	
	//MotorSetManual(90,90,90,90,100,100,100,100);
	
	//Stating autonomous mode with manual velocity.
	AutoModeStart(99, 90, 99, 90, 99, 90, 99, 90);
	
	sleep(20);
	
	while(1)
	{
		if (digitalRead(28))
			break;
	}
	
	//Stop autonomous mode.
	AutoModeStop();
	ReturnToBase();
	
	return 0;
}