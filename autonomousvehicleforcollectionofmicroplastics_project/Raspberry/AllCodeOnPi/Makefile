CFLAGS = -g -Wall
#VPATH = libs

default: mainControl

mainControl: sortingCollectingMotor.o mtJoystick.o xboxControl.o autonomousMode.o mainControl.o 
	g++ $(CFLAGS) *.o -o mainControl -lwiringPi -lpthread
	
mainControl.o: mainControl.cpp
	g++ $(CFLAGS) -c mainControl.cpp -o mainControl.o

mtJoystick.o: mtJoystick.c
	gcc $(CFLAGS) -c mtJoystick.c -o mtJoystick.o

xboxControl.o: mtJoystick.o pwmlib.o xboxControlRumble.o xboxControl.cpp
	g++ $(CFLAGS) mtJoystick.o pwmlib.o xboxControlRumble.o -c xboxControl.cpp -o xboxControl.o
	
pwmlib.o: pwmlib.cpp
	g++ $(CFLAGS) -c pwmlib.cpp -o pwmlib.o 
	
autoDrivingRandom.o: autoDrivingRandom.cpp
	g++ $(CFLAGS) wireSensorLibA.o -c autoDrivingRandom.cpp -o autoDrivingRandom.o 

# wireSensorLibA.o: wireSensorLibA.cpp
	# g++ $(CFLAGS) -c wireSensorLibA.cpp -o wireSensorLibA.o 
	
xboxControlRumble.o: xboxControlRumble.c
	gcc $(CFLAGS) -c xboxControlRumble.c -o xboxControlRumble.o
	
autonomousMode.o: pwmlib.o wireSensorLibN.o sensorLib.o autonomousMode.cpp
	g++ $(CFLAGS) pwmlib.o wireSensorLibN.o sensorLib.o -c autonomousMode.cpp -o autonomousMode.o
	
wireSensorLibN.o: wireSensorLibN.cpp
	g++ $(CFLAGS) -c wireSensorLibN.cpp -o wireSensorLibN.o
	
sensorLib.o: sensorLib.cpp
	g++ $(CFLAGS) -c sensorLib.cpp -o sensorLib.o
	
sortingCollectingMotor.o: sortingCollectingMotor.cpp
	g++ $(CFLAGS) -c sortingCollectingMotor.cpp -o sortingCollectingMotor.o

clean:
	$(RM) count *o *~
	$(RM) mainControl

#gcc -c -o ./libs/mtJoystic.o ./libs/mtJoystic.c
#gcc -c -o ./libs/mtXboxController.o ./libs/mtXboxController.c
#gcc -c -o ./libs/mtQuaternions.o ./libs/mtQuaternions.c
#gcc -c -o ./libs/mtVector.o ./libs/mtVector.c

#g++ -o mainControll ./libs/mtJoystic.o ./libs/mtXboxController.o ./libs/mtQuaternions.o ./libs/mtVector.o
