#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std ; 

int main(void){
    int serialDeviceId = 0;
	char dataChar = 0;
	
	
	serialDeviceId = serialOpen("/dev/ttyACM0",9600);
	
	cout << "Serial Comunication Started" << endl;
	
    if(serialDeviceId==-1)
     {
     cout<<"Unable to open serial device"<<endl;
     return 1; 
     }  
	 
    if(wiringPiSetup()==-1)
    {
        return 0 ;
    }
	
    while(1) 
    {
		dataChar = serialGetchar(serialDeviceId);
		int dataInt = dataChar - '0';
		//cout << dataInt<< endl;
		
		
		
	    switch(dataInt){
			case 0: 							// 0000
				cout<<"Case : \t---- \t---- \t---- \t----"<<endl;
			break;
			case 1: 							// 0001
				cout<<"Case : \tLeft \t---- \t---- \t----"<<endl;
				break;
			case 2: 							// 0010
				cout<<"Case : \t---- \tMid \t---- \t----"<<endl;
				break;
			case 3:								// 0011
				cout<<"Case : \tLeft  \tMid \t---- \t----"<<endl;
				break;
			case 4:								// 0100
				cout<<"Case : \t---- \t---- \tRight \t----"<<endl;
				break;
			case 5:								// 0101
				cout<<"Case : \tLeft \t---- \tRight \t----"<<endl;
				break;
			case 6: 							// 0110
				cout<<"Case : \t---- \tMid \tRight \t----"<<endl;
				break;
			case 7:								// 0111
				cout<<"Case : \tLeft \tMid \tRight \t---- "<<endl;
				break;
			case 8:								// 1000
				cout<<"Case : \t---- \t---- \t---- \tFull"<<endl;
				break;
			case 9:								// 1001
				cout<<"Case : \tLeft \t---- \t---- \tFull"<<endl;
				break;
			case 10:							// 1010
				cout<<"Case : \t---- \tMid \t---- \tFull"<<endl;
				break;
			case 11:							// 1011
				cout<<"Case : \tLeft \tMid \t---- \tFull"<<endl;
				break;
			case 12:							// 1100
				cout<<"Case : \t---- \t---- \tRight \tFull"<<endl;
				break;
			case 13:							// 1101
				cout<<"Case : \tLeft \t---- \tRight \tFull"<<endl;
				break;
			case 14:							// 1110
				cout<<"Case : \t---- \tMid \tRight \tFull"<<endl;
				break;
			case 15:							// 1111
				cout<<"Case : \tLeft \tMid \tRight \tFull"<<endl;
				break;
			//default :
				//cout<<"default thing"<<endl;
		}
		
		//putchar(serialGetchar(serialDeviceId));
		//fflush(stdout);
    }
    return 0;
}

// compile with sudo g++ cScript cScript.cpp -lwiringPi
// http://wiringpi.com/reference/serial-library/ for wiringSerial library 