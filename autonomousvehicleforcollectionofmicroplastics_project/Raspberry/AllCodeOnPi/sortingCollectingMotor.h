#ifndef SORTINGCOLLECTINGMOTOR_H_
#define SORTINGCOLLECTINGMOTOR_H_

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <wiringPi.h>
#include <softPwm.h>

#define RANGE		10

void initSortingCollectingMotor(int pin);
void startSortingCollectingMotor(int range);
void stopSortingCollectingMotor();

#endif