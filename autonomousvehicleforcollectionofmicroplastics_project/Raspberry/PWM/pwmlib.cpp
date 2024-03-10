#include</home/pi/sem5/pwmLibMini.h>
//
//Defining PWM pins.
int PWMpin1 = 1; //pins 1 and 23
int PWMpin2 = 23;
int minDuty = 0, maxDuty = 100;
bool setManualVel = false;
int manVel[8] = {0,0,0,0,0,0,0,0}; //FL, FR, BL, BR, LL, LR, RL, RR
pthread_t accID;

int maxVelocity = 0;
int accelerationTime = 0;
int controlPin = 0;
int accDuty = 0;
int currentAccTime = 0;
int accDir = 0;

//Set motorVelocities for each direction
void MotorSetManual(void)
{
                setManualVel = true;
}

void MotorSetManual(int FL, int FR, int BL, int BR, int LL, int LR, int RL, int RR)
{
                setManualVel = true;
				manVel[0] = FL;
                manVel[1] = FR;
                manVel[2] = BL;
                manVel[3] = BR;
                manVel[4] = LL;
                manVel[5] = LR;
                manVel[6] = RL;
                manVel[7] = RR;
}

void MotorInit()
{
        //Setting up WiringPi.
        wiringPiSetup();
		std::cout << "WiringPi setup complete." << std::endl;
		pinMode(0, OUTPUT);
		pinMode(22, OUTPUT);
		
        pinMode (PWMpin1, PWM_OUTPUT);
        pinMode (PWMpin2, PWM_OUTPUT);
        std::cout << "Pin mode set." << std::endl;
        pwmSetMode(PWM_MODE_BAL);
        std::cout << "PWM mode set." << std::endl;
        pwmSetClock(4800);
        std::cout << "Clock set." << std::endl;
        pwmSetRange(100);
        std::cout << "Range set." << std::endl;
        std::cout << "Setup complete." << std::endl << std::endl;
}

void MotorInit(int clk, int range)
{
        //Setting up WiringPi.
        wiringPiSetup();
		pinMode(0, OUTPUT);
		pinMode(22, OUTPUT);
		
        std::cout << "WiringPi setup complete." << std::endl;
        pinMode (PWMpin1, PWM_OUTPUT);
        pinMode (PWMpin2, PWM_OUTPUT);
        std::cout << "Pin mode set." << std::endl;
        pwmSetMode(PWM_MODE_MS);
        std::cout << "PWM mode set." << std::endl;
        pwmSetClock(clk);
        std::cout << "Clock set." << std::endl;
        pwmSetRange(range);
        std::cout << "Range set." << std::endl;
        std::cout << "Setup complete." << std::endl << std::endl;

}

void MotorInit(int clk, int range, int minLimit, int maxLimit)
{
        //Setting up WiringPi.
        wiringPiSetup();
		pinMode(0, OUTPUT);
		pinMode(22, OUTPUT);
		
        std::cout << "WiringPi setup complete." << std::endl;
        pinMode (PWMpin1, PWM_OUTPUT);
        pinMode (PWMpin2, PWM_OUTPUT);
        std::cout << "Pin mode set." << std::endl;
        pwmSetMode(PWM_MODE_BAL);
        std::cout << "PWM mode set." << std::endl;
        pwmSetClock(clk);
        std::cout << "Clock set." << std::endl;
        pwmSetRange(range);
        std::cout << "Range set." << std::endl;
        std::cout << "Setup complete." << std::endl << std::endl;

                minDuty = minLimit;
                maxDuty = maxLimit;
}

//Motor acceleration function
void* AccelThread(void* vptr)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	
	int duty = minDuty;
	
	
	for(int i = minDuty; i < maxVelocity; i++)
	{
		if(controlPin == 0)
		{
			MotorDirection(accDir);
			pwmWrite(PWMpin1, duty);
			pwmWrite(PWMpin2, duty);
		}
		if(controlPin == 1)
			pwmWrite(PWMpin1, duty);
		if(controlPin == 2)
			pwmWrite(PWMpin2, duty);
		duty++;
		
		int sleepAmount = 1000000 * accelerationTime / (maxVelocity-minDuty);
                usleep(sleepAmount);
				currentAccTime = currentAccTime + sleepAmount;
				
	}
		currentAccTime = 0;
		pthread_join(accID, NULL);
		return vptr;
}

void MotorAcceleration(int accTime, int maxVel)
{
        setManualVel = false;
		
		accelerationTime = accTime;
        maxVelocity = maxVel;
		controlPin = 0;
		pthread_create( &accID, NULL, &AccelThread, NULL);
}

void MotorAcceleration(int accTime, int maxVel, int pin)
{
        setManualVel = false;
		
		accelerationTime = accTime;
		maxVelocity = maxVel;
		controlPin = pin;
		pthread_create( &accID, NULL, &AccelThread, NULL);
}

void MotorAccelerationStop()
{
                
				pthread_cancel(accID);
				pthread_join(accID, NULL);
}

//Velocity function. Optimal settings: Forward and back 850, right 900, left 1000.
void MotorVelocity(int motorVel)
{
		setManualVel = false;
		
		pwmWrite(PWMpin1, motorVel);
        pwmWrite(PWMpin2, motorVel);

        std::cout << "Velocity set to " << motorVel << "." << std::endl;
}

void MotorVelocity(int motorVel1, int motorVel2)
{
		setManualVel = false;
		
		pwmWrite(PWMpin1, motorVel1);
        pwmWrite(PWMpin2, motorVel2);

        std::cout << "Motor 1 velocity set to " << motorVel1 << "." << std::endl;
        std::cout << "Motor 2 velocity set to " << motorVel2 << "." << std::endl;
}

void MotorVelocityAcc(int motorVel, int accelTime)
{
        setManualVel = false;
		
		MotorAcceleration(accelTime, motorVel);
        std::cout << "Velocity set to " << motorVel << "with acceleration time of " << accelTime << "." << std::endl;
}

void MotorVelocityAcc(int motorVel1, int motorVel2, int accelTime)
{
        setManualVel = false;
		
		controlPin = 1;
		MotorAcceleration(accelTime, motorVel1);
		controlPin = 2;
        MotorAcceleration(accelTime, motorVel2);

        std::cout << "Velocity of motor 1 set to " << motorVel1 << "with acceleration time of " << accelTime << "." << std::endl;
                std::cout << "Velocity of motor 2 set to " << motorVel2 << "with acceleration time of " << accelTime << "." << std::endl;
}

//Direction function.
void MotorDirection(int motordir)
{
        switch(motordir)
        {
        case 0 :
                accDir = 0;
				digitalWrite(0, HIGH);
				digitalWrite(22, HIGH);
                std::cout << "Direction set to FORWARD." << std::endl;
                if(setManualVel)
				MotorVelocity(manVel[0],manVel[1]);
                break;
        case 1 :
                accDir = 1;
				digitalWrite(0, LOW);
				digitalWrite(22, LOW);
                std::cout << "Direction set to BACK." << std::endl;
                if(setManualVel)
				MotorVelocity(manVel[2],manVel[3]);
                break;
        case 2 :
                accDir = 2;
				digitalWrite(0, LOW);
				digitalWrite(22, HIGH);
                std::cout << "Direction set to LEFT." << std::endl;
                if(setManualVel)
				MotorVelocity(manVel[4],manVel[5]);
                break;
        case 3 :
				accDir = 3;
				digitalWrite(0, HIGH);
				digitalWrite(22, LOW);
                std::cout << "Direction set to RIGHT." << std::endl;
                if(setManualVel)
				MotorVelocity(manVel[6],manVel[7]);
                break;
        default :
                MotorVelocity(0);
                std::cout << "ERROR: Velocity set to 0" << std::endl;
                break;
        }

}
