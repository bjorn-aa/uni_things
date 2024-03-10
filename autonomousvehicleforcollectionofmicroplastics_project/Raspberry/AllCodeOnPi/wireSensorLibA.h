#ifndef WIRESENSORLIBA_H_
#define WIRESENSORLIBA_H_

#define WIRE_SENSOR_RIGHT 0
#define WIRE_SENSOR_LEFT 1

#include <wiringPi.h>
#include <wiringSerial.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>

extern int wireDistanceRight;
extern int wireDistanceLeft;

//
void WireInit(void);
void WireCal(void);
void WireCalCurrent(void);
int WireRead(int);
int RawInput(int);
void WireLimit(int, int);
bool WireClose(int);
int LimitToVar(int);
void WriteLimit(int, int);

#endif
