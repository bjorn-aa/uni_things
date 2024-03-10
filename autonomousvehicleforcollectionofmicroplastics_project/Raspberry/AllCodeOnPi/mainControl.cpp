/*
 * main.c
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
#include "autoDrivingRandom.h"
#include <stdio.h>
#include "sortingCollectingMotor.h"

uint64_t xboxControllerCounter = 0;
uint64_t xboxControllerCheck = 500000000;

int main(int argc, char **argv)
{
	xboxControlInit();
	initSortingCollectingMotor(2);	
	while(1)
	{
		xboxControlHandler();
		if(!isXboxControllerEnabled())
		{
			// Run the random movement pattern.
		}
		
		if(!getIsXboxControllerConnected())
		{
			if(xboxControllerCounter == xboxControllerCheck)
			{
				printf("Checking for xbox controller");
				xboxControllerCounter = 0;
				xboxControlInit();
			}
			else xboxControllerCounter++;
		}
	}
		
	
	return 0;
}

