#ifndef THREADEDSLEEP_H_
#define THREADEDSLEEP_H_

#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>

void ThreadedSleep(int);
bool ThreadedSleepAwake(void);

#endif