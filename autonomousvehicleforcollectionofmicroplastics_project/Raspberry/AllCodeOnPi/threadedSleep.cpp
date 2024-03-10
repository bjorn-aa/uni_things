#include "./threadedSleep.h"

pthread_t sleepID;
bool awake = false;
int sleepTime = 0;

void* SleepThread(void* vptr)
{
	usleep(sleepTime);
	awake = true;
	pthread_join(sleepID, NULL);
}

void ThreadedSleep(int sleep)
{
	sleepTime = sleep;
	pthread_create(&sleepID, NULL, &SleepThread, NULL);
}

bool ThreadedSleepAwake(void)
{
	if (awake)
		return true;
	else
		return false;
}