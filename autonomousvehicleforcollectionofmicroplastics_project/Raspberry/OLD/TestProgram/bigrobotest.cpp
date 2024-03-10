#include <pwmlib.h>

int duty1 = 0;
int duty2 = 0;
int dir = FORWARD;
int driveTime = 5000;

int main(void)
{
	MotorInit(12000, 100, 0, 100);
	
	MotorDirection(FORWARD);
	
	for(;;)
	{
		std::cout << "Enter duty cycle 1 (0-1024):" << std::endl;
		std::cin << duty1;
		std::cout << "Enter duty cycle 2 (0-1024):" << std::endl;
		std::cin << duty2;
		std::cout << "Enter direction (0-3):" << std::endl;
		std::cin << dir;
		std::cout << "Enter time to drive (ms):" << std::endl;
		std::cin << driveTime;
		
		MotorDirection(dir);
		MotorVelocity(duty1, duty2);
		usleep(driveTime*1000);
		MotorVelocity(0);
	
	
	return 0;
}