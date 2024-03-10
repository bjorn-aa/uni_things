#include</home/pi/sem5/wireSensorLibA.h>

int analogIn1 = 0;
int analogIn2 = 0;
int raw1 = 0;
int raw2 = 0;
char testchar = '\n';
int limit1 = 0;
int limit2 = 0;


int main(void)
{
	WireInit();
	std::cout << "Welcome to the wire calibration program. Position the sensors above the wire fence and enter a limit. Enter a limit for each sensor just above the shows output values" << std::endl;
	
	for( ;; )
	{
	std::cout << "Enter limit for right sensor:" << std::endl;
	std::cin >> limit1;
	std::cout << "Enter limit for left sensor:" << std::endl;
	std::cin >> limit2;
	
	WireLimit(limit1, limit2);
	
	WriteLimit(limit1, 0);
	WriteLimit(limit2, 1);
	
	raw1 = RawInput(WIRE_SENSOR_RIGHT);
	raw2 = RawInput(WIRE_SENSOR_LEFT);

	std::cout << "Left sensor: "<< raw2 << "   Right sensor: " << raw1 << std::endl;
	

	}

	return 0;
}
