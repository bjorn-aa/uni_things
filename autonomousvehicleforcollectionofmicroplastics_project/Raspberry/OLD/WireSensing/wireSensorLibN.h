#ifndef WIRESENSORLIBN_H_
#define WIRESENSORLIBN_H_

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
#include <math.h>

void WireInit(void);
void WireCal(void);
void WireCalCurrent(void);
int WireRead(int);
int WireReadProportional(int);
void WireLimit(int, int);
bool WireClose(void);
bool WireClose(int);
int LimitToVar(int);
void WriteLimit(int, int);

#endif
