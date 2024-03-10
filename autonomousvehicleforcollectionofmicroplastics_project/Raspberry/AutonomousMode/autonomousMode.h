#ifndef AUTONOMOUSMODE_H_
#define AUTONOMOUSMODE_H_

#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include "./pwmlib.h"
//#include "./wireSensorLibN.h"
#include "./sensorLibNano.h"					// Replaceing wireSensorLibN
#include "./sensorLib.h"

void AutoModeStart(int);
void AutoModeStart(int, int);
void AutoModeStart(int, int, int, int, int, int, int, int);
void AutoModeStop(void);

#endif