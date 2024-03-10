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

extern int currentAccTime;

void MotorSetManual(int[8]);
void MotorInit(void);
void MotorInit(int, int);
void MotorInit(int, int, int, int);
void MotorAcceleration(int, int);
void MotorAcceleration(int, int, int);
void MotorAccelerationStop(void);
void MotorVelocity(int);
void MotorVelocity(int, int);
void MotorVelocityAcc(int, int);
void MotorVelocityAcc(int, int, int);
void MotorDirection(int);

#endif
