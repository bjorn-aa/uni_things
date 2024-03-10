#include "./autonomousMode.h"

int vel1 = 0;
int vel2 = 0;
int vA[8] = {0,0,0,0,0,0,0,0}; //FL, FR, BL, BR, LL, LR, RL, RR
int inp1 = 0;
int inp2 = 0;
int count = 0;
int manual = false;

pthread_t autoID;

//Autonomous mode thread.
void* AutoThread(void* vptr)
{
	while(1)
	{
		MotorDirection(FORWARD);
		if (!manual)
			MotorVelocity(vel1, vel2);
		else
			MotorSetManual(vA[0], vA[1], vA[2], vA[3], vA[4], vA[5], vA[6], vA[7]);
		
		/* inp1 = RawInput(0);
		inp2 = RawInput(1);
		
		std::cout << inp1 << "   " << inp2 << std::endl; */
		//
		
		std::cout << WireRead(0) << "   " << WireRead(1) << std::endl;
		
		//If a wire is withing the limit, stop, drive backward, 
		//turn a random amount to the left or right.
		if(WireClose())
		{
			MotorVelocity(0);
			usleep(500000);
				if (!manual)
				MotorVelocity(vel1, vel2);
				else
				MotorSetManual();
			MotorDirection(BACKWARD);
			usleep(500000);
			int dir = rand() % 2;
				if (!manual)
				MotorVelocity(vel1, vel2);
				else
				MotorSetManual();

			if(!dir)
				MotorDirection(LEFT);
			else
				MotorDirection(RIGHT);
			int turnTime = rand() % 200000 + 500000;
			usleep(turnTime);
			MotorVelocity(0);
			usleep(500000);
			
			
		}
		
		//If an ultrasonic sensor is triggered, stop, drive backward, 
		//turn a random amount to the left or right.
		if (UltrasonicCheck() == ULTRASONIC_LEFT)
		{
			MotorVelocity(0);
			usleep(5000);
				if (!manual)
				MotorVelocity(vel1, vel2);
				else
				MotorSetManual();
			MotorDirection(BACKWARD);
			usleep(500000);
				if (!manual)
				MotorVelocity(vel1, vel2);
				else
				MotorSetManual();
			MotorDirection(RIGHT);
			usleep(500000);
			MotorVelocity(0);
			usleep(5000);
		}
		if (UltrasonicCheck() == ULTRASONIC_RIGHT)
		{
			
			MotorVelocity(0);
			usleep(5000);
				if (!manual)
				MotorVelocity(vel1, vel2);
				else
				MotorSetManual();
			MotorDirection(BACKWARD);
			usleep(500000);
				if (!manual)
				MotorVelocity(vel1, vel2);
				else
				MotorSetManual();
			MotorDirection(LEFT);
			usleep(500000);
			MotorVelocity(0);
			usleep(5000);
		}
			
	}
	
	return vptr;
}

//Functions for starting autonomous mode thread, either one velocity,
//two separate velocities or manual velocity.
void AutoModeStart(int velocity)
{
	manual = false;
	vel1 = velocity;
	vel2 = velocity;
	pthread_create(&autoID, NULL, &AutoThread, NULL);
}

void AutoModeStart(int velocity1, int velocity2)
{
	vel1 = velocity1;
	vel2 = velocity2;
	pthread_create(&autoID, NULL, &AutoThread, NULL);
}

void AutoModeStart(int FL, int FR, int BL, int BR, int LL, int LR, int RL, int RR)
{
	manual = true;
	
	vA[0] = FL;
	vA[1] = FR;
	vA[2] = BL;
	vA[3] = BR;
	vA[4] = LL;
	vA[5] = LR;
	vA[6] = RL;
	vA[7] = RR;
	
	pthread_create(&autoID, NULL, &AutoThread, NULL);
}

//Function for stopping the thread.
void AutoModeStop(void)
{
	pthread_cancel(autoID);
	pthread_join(autoID, NULL);
	MotorVelocity(0);
}
