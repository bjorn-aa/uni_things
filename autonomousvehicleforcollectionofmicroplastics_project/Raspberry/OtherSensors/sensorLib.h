#ifndef SENSORLIB_H_
#define SENSORLIB_H_

#define ULTRASONIC_LEFT (1)
#define ULTRASONIC_RIGHT (2)


#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "./pwmlib.h"

void SensorInit(void);
int GetWeight(void);
uint8_t UltrasonicCheck(void);

#endif
