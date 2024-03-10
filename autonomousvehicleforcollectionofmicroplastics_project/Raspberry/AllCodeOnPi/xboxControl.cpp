/*
 * xboxControl.cpp
 * 
 * Copyright 2019  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
#include "xboxControl.h"
#include <stdio.h>
#include <cstdlib>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "sortingCollectingMotor.h"
#include "pwmlib.h"
 
#define maxAxisValue 32767.0
bool useController;
float pwmMultipliers[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1 }; // to reduce the max pwm by a multiplier i.e. 0.8
int pwmMultiplierCounter = 0;
bool isPwmMultiplierPressed = false, isPwmMultiplierResetPressed = false, isTotalStopPressed = false, isCollectingSortingPressed = false;
bool isXboxControllerConnected = false;

char *extract_controller_jsname();

void xboxControlInit()
{
	printf("Trying to find controller\n");
	std::string deviceName = "/dev/input/";
	std::string eventName = extract_controller_jsname();
	if(eventName != "")
	{
		usleep(100 * 1000);
		deviceName += eventName;
		printf("%s\n", deviceName.c_str());
		if(!startDeviceConnection(deviceName.c_str())) //js0 or event7
		{
			printf("controller not found\n");
			isXboxControllerConnected = false;
		}
		else
		{
			printJoystickInformation();
			MotorInit();
			rumbleTest();
			isXboxControllerConnected = true;
		}
	}
	else isXboxControllerConnected = false;
}

bool getIsXboxControllerConnected()
{
	return isXboxControllerConnected;
}

void xboxControlCheckButtons()
{
	short value, valueTwo;
	
	// Y button
	getButtonValue(3, &value);
	if(value)
	{
		if(!useController)
		{
			useController = true;
			printf("\n");
			printf("button Y pressed\n");
			printf("\n");
		}
		
	}
	
	if(useController)
	{
		// X button
		getButtonValue(2, &value);
		if(value)
		{
			if(useController)
			{
				useController = false;
				printf("\n");
				printf("button X pressed quiting xbox control\n");
				printf("\n");
				startSortingCollectingMotor(0);
				MotorVelocity(0, 0);
			}
			return;
		}
		
		// 3 lines button
		getButtonValue(7, &value);
		if(value)
		{
			if(!isPwmMultiplierPressed)
			{
				pwmMultiplierCounter++;
				if(pwmMultiplierCounter > 10) pwmMultiplierCounter = 0;
				printf("\n");
				printf("button with 3 lines pressed\n");
				printf("\n");
				isPwmMultiplierPressed = true;
				doRumble(pwmMultiplierCounter + 1, 25000);
			}
		}
		else
		{
			isPwmMultiplierPressed = false;
		}
		
		// Picture button
		getButtonValue(6, &value);
		if(value)
		{
			if(!isPwmMultiplierResetPressed)
			{
				pwmMultiplierCounter = 0;
				printf("\n");
				printf("button with pictures pressed\n");
				printf("\n");
				isPwmMultiplierResetPressed = true;
				doRumble(pwmMultiplierCounter + 1, 25000);

			}
		}
		else
		{
			isPwmMultiplierResetPressed = false;
		}
		
		// Picture B - Total stop - 
		getButtonValue(1, &value);
		if(value)
		{
			if(!isTotalStopPressed)
			{
				printf("\n");
				printf("button B - Total stop - pressed\n");
				printf("\n");
				isTotalStopPressed = true;
				MotorVelocity(0, 0);
			}
		}
		else
		{
			isTotalStopPressed = false;
		}
		
		// Picture B - Total stop - 
		getButtonValue(4, &value);
		getButtonValue(5, &valueTwo);
		if(value && valueTwo)
		{
			if(!isCollectingSortingPressed)
			{
				printf("\n");
				printf("button LB and RB - Start collecting and sorting - pressed\n");
				printf("\n");
				isCollectingSortingPressed = true;
				startSortingCollectingMotor(5);
			}
		}
		else
		{
			isCollectingSortingPressed = false;
		}
		
		
		
		usleep(100 * 1000);
	}
}

void calculateDirection(bool isDirectionForwaredLeft, bool isDirectionForwaredRight)
{
	if(!isDirectionForwaredLeft && !isDirectionForwaredRight)
	{
		MotorDirection(FORWARD);
	}
	else if(isDirectionForwaredLeft && isDirectionForwaredRight)
	{
		MotorDirection(BACKWARD);
	}
	else if(isDirectionForwaredLeft && !isDirectionForwaredRight)
	{
		MotorDirection(LEFT);
	}
	else if(!isDirectionForwaredLeft && isDirectionForwaredRight)
	{
		MotorDirection(RIGHT);
	}
}
short xboxControlHandleAbsoluteAxis(short value, bool * isDirectionForwared)
{
	short pwmSpeed = 0;
	if(value > 0)
	{
		(*isDirectionForwared) = false;
		pwmSpeed = (value / maxAxisValue) * 100;
		if(pwmSpeed > 99) pwmSpeed = 99;
		
		return short(pwmSpeed * pwmMultipliers[pwmMultiplierCounter]);
	}
	else if(value < 0)
	{
		(*isDirectionForwared) = true;
		value = abs(value);
		pwmSpeed = (value / maxAxisValue) * 100;
		if(pwmSpeed > 99) pwmSpeed = 99;
		
		return short(pwmSpeed * pwmMultipliers[pwmMultiplierCounter]);
	}
	else
	{
		return 0;
	}
}
void xboxControlCheckAxis()
{
	short value;
	short pwmSpeedLeft, pwmSpeedRight;
	bool isDirectionForwaredLeft, isDirectionForwaredRight;
	
	if(getAxisValue(1, &value))
	{
		pwmSpeedLeft = xboxControlHandleAbsoluteAxis(value, &isDirectionForwaredLeft);
		if(pwmSpeedLeft)
		{
			printf("absolute right joystick\n");
			printf("pwmspeed is %d, value is %d and direction is %s\n\n\n", pwmSpeedLeft, value, isDirectionForwaredLeft ? "forward" : "backwards");
		}
	}
	if(getAxisValue(4, &value))
	{
		pwmSpeedRight = xboxControlHandleAbsoluteAxis(value, &isDirectionForwaredRight);
		if(pwmSpeedRight)
		{
			printf("absolute left joystick\n");
			printf("pwmspeed is %d, value is %d and direction is %s\n\n\n", pwmSpeedRight, value, isDirectionForwaredRight ? "forward" : "backwards");
		}
	}
	
	if(pwmSpeedLeft || pwmSpeedRight)
	{
		MotorVelocity(pwmSpeedLeft, pwmSpeedRight);
		calculateDirection(isDirectionForwaredLeft , isDirectionForwaredRight);
	}
}

void xboxControlHandler()
{
	if(isXboxControllerConnected)
	{
		handleJoystickEvents();
		xboxControlCheckButtons();
	
		if(useController)
		{
			xboxControlCheckAxis();
		}
	}
}

bool isXboxControllerEnabled()
{
	return useController;
}

void xboxControlFree()
{
	endDeviceConnection();
}



char *extract_controller_jsname()
{
    FILE *fp = NULL;
    char buffer[1024];
    char *eventname = NULL;
	struct stat bufferStat;
	if(stat("/proc/bus/input/devices", &bufferStat) == 0)
	{
		fp = fopen("/proc/bus/input/devices", "r");
		if (!fp) {
			int err = errno;
			fprintf(stderr, "Unable to open file. %s\n", strerror(err));
			return NULL;
		}
		memset(buffer, 0, sizeof(buffer));
		while (fgets(buffer, sizeof(buffer), fp)) {
			char *ptr = NULL;
			if ((ptr = strstr(buffer, "Handlers="))) {
				ptr += strlen("Handlers=");
				ptr = strstr(ptr, "js");
				if (ptr) {
					char *ptr2 = strchr(ptr, ' ');
					if (ptr2)
						*ptr2 = '\0';
					eventname = strdup(ptr);
					if (!eventname) {
						fprintf(stderr, "Out of memory.\n");
						break;
					}
				}
			}
			if (strstr(buffer, "Phys=b8:3f:26:a7:c1:8d")) {
				fprintf(stderr, "Xbox controller js is /dev/input/%s\n", eventname);
				break;
			}
		}
		
		fclose(fp);
	}

    return eventname != NULL ? eventname : (char *)"";
}
