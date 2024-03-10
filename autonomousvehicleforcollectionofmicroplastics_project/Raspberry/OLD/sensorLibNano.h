#ifndef SENSORLIBNANO_H_
#define SENSORLIBNANO_H_

#define Error_1 0							// Temperatur Error
#define Error_2 1							// Humidity Error

// ------------------ From wireSensorLibN below  --------------------------

// From wireseonsor lib 
#define WIRE_SENSOR_RIGHT 0
#define WIRE_SENSOR_LEFT 1

#include <wiringPi.h>						// For Serial comunication 
#include <wiringSerial.h>					// Part of WiringPi
#include <iostream>							// in/out
#include <unistd.h>							// POSIX operating system API

#include "./autonomousMode.h"				// autonomusMode includes 
#include "./pwmlib.h"						// For motor stop 

// From wireSensorLib 

//#include <wiringPi.h>
//#include <wiringSerial.h>
#include <errno.h>
#include <stdio.h>
//#include <iostream>
#include <string>
//#include <unistd.h>
#include <fstream>
#include <sstream>

extern int wireDistanceRight;
extern int wireDistanceLeft;

void WireInit(void);
void WireCal(void);
void WireCalCurrent(void);
int WireRead(int);
void WireLimit(int, int);
bool WireClose(void);
int LimitToVar(int);
void WriteLimit(int, int);

// ------------------ From wireSensorLibN Above  --------------------------

void SensorInit(void);
void GetOther(void);
bool AtBase(void);
void RainOn(void);
void ErrorOther(int temp);

#endif
