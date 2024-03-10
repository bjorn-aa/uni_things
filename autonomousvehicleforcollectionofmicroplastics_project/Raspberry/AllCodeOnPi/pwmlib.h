#ifndef PWMLIB_H_
#define PWMLIB_H_

#define FORWARD (0)
#define BACKWARD (1)
#define LEFT (2)
#define RIGHT (3)

#include <wiringPi.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>

void MotorSetManual(void);
void MotorSetManual(int, int, int, int, int, int, int, int);
void MotorInit(void);
void MotorInit(int, int);
void MotorInit(int, int, int, int);
void MotorAcceleration(int, int);
void MotorAcceleration(int, int, int);
void MotorAccelerationStop(void);
void MotorVelocity(int);
void MotorVelocity(int, int);	
void MotorDirection(int);
uint8_t CurrentDirection(void);

#endif
