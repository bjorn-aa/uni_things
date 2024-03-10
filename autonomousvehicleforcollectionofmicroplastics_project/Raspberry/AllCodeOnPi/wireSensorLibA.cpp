#include</home/pi/sem5/wireSensorLibA.h>

int wInterp1[6] = {0};
int wInterp2[6] = {0};
int fd;
char previousChar = '0';
int currentDigit = 0;
int dataArray[4] = {0,0,0,0};
int wireLimit1 = 700;
int wireLimit2 = 700;

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

void WriteFile(int input, int file)
{
	std::string str = "echo " + std::to_string(input) + " > /home/pi/sem5/savedValues/wInterp" + std::to_string(file) + ".txt";
	const char* dataToWrite = str.c_str();
	system(dataToWrite);
}

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

void WriteLimit(int limit, int sensor)
{
	std::string str = "echo " + std::to_string(limit) + " > /home/pi/sem5/savedValues/limit" + std::to_string(sensor) + ".txt";
	const char* dataToWrite = str.c_str();
	system(dataToWrite);
}

void WireInit(void)
{
	system("sudo mkdir savedValues");
	
	system("echo 21 > /sys/class/gpio/export");
    system("echo out > /sys/class/gpio/gpio21/direction");
	system("echo 20 > /sys/class/gpio/export");
    system("echo out > /sys/class/gpio/gpio20/direction");
	
	wiringPiSetup();
	if((fd=serialOpen("/dev/ttyUSB0",115200))<0){
    std::cout << "Unable to open serial device" << std::endl;
	if((fd=serialOpen("/dev/ttyUSB1",115200))<0){
    std::cout << "Unable to open serial device" << std::endl;
	if((fd=serialOpen("/dev/ttyUSB2",115200))<0){
    std::cout << "Unable to open serial device" << std::endl;
	if((fd=serialOpen("/dev/ttyUSB3",115200))<0){
    std::cout << "Unable to open serial device" << std::endl;
	}
	}
	}
	}
	
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

int RawInput(int sensor)
{
	char received;
	int rawInput = 0;
	
	while(1)
	{
	if (!sensor)
		system("echo 0 > /sys/class/gpio/gpio21/value");
	else
		system("echo 1 > /sys/class/gpio/gpio21/value");
	
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
	
	if (dataArray[0] == 10 && dataArray[2] == 13 && dataArray[3] == 10)
		rawInput = 0;
	else
		rawInput = (dataArray[1]-48)*100 + (dataArray[2]-48)*10 + (dataArray[3]-48);

	for (int i=0; i<4; i++)
	{
		dataArray[i] = 0;
	}
	
	serialFlush(fd);
	if (sensor == 0)
	{
		if (rawInput < wireLimit1)
			break;
	}
	if (sensor == 1)
	{
		if (rawInput < wireLimit2)
			break;
	}
	}

	return rawInput;
}

void WireCal(void)
{
	while(1)
	{
	std::cout << "Beginning calibration of wire sensors." << std::endl;
	std::cout << "Position vehicle at 1cm distance to wire. Press enter to continue..." << std::endl;
	std::cin.get();
	wInterp1[3] = RawInput(1);
	wInterp2[3] = RawInput(0);
	
	WriteFile(wInterp1[3], 0);
	WriteFile(wInterp2[3], 1);
	
	std::cout << "Position vehicle at 5cm distance to wire. Press enter to continue..." << std::endl;
	std::cin.get();
	wInterp1[5] = RawInput(1);
	wInterp2[5] = RawInput(0);
	
	WriteFile(wInterp1[5], 2);
	WriteFile(wInterp2[5], 3);
	
	if (wInterp1[3] != 0 && wInterp2[3] != 0 && wInterp1[5] != 0 && wInterp1[5] != 0)
		break;
	else
		std::cout << "Invalid reading!" << std::endl;
	}
}

void WireCalCurrent(void)
{
	std::cout << FileToVar(0) << std::endl;
	std::cout << FileToVar(1) << std::endl;
	std::cout << FileToVar(2) << std::endl;
	std::cout << FileToVar(3) << std::endl;
}

int WireRead(int pin)
{
	int wireDistance = 0;
	int input = 0;
	
	if (!pin)
	{
		input = RawInput(1);
		wireDistance += (input*wInterp1[2] - input*wInterp1[4] + wInterp1[3]*wInterp1[4] - wInterp1[5]*wInterp1[2]) / (wInterp1[3] - wInterp1[5]);
	}
	else
	{
		input = RawInput(0);
		wireDistance += (input*wInterp2[2] - input*wInterp2[4] + wInterp2[3]*wInterp2[4] - wInterp2[5]*wInterp2[2]) / (wInterp2[3] - wInterp2[5]);
	}
	
	return wireDistance;
}

void WireLimit(int limit1, int limit2)
{
	wireLimit1 = limit1;
	wireLimit2 = limit2;
}

bool WireClose(int sensor)
{
	int input = RawInput(sensor);
	if (input > wireLimit1 || input > wireLimit2)
		return TRUE;
	else
		return FALSE;
}

