/*
A0 = Rain sensor 
A1 = Ir sensor 
A2 = for wire sensor 
A3 = for wire sensor 
*/

// For the temp and humididy sensor 
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Initialize DHT sensor for normal 16mhz Arduino:
DHT dht = DHT(4, DHT11);                                    // DHT11 initilized on Digital pin 4 

int wireIn1 = 0;
int wireIn2 = 0;
int RaspGPIO20 = 0;
int RaspGPIO21 = 0;

char piCommand = '0';

void setup() {
  pinMode(A0, INPUT);                                       // A0 is rain sensor, green wire 
  pinMode(A1, INPUT);                                       // A1 is IR sensor, Green wire 

  pinMode(A2, INPUT);                                       // Analog for Wire sensor 1  
  pinMode(A3, INPUT);                                       // Analog for Wire sensor 2 
  
  pinMode(5, INPUT);                                        // Digital pin 1 connected to GPIO20
  pinMode(6, INPUT);                                        // Digital pin 2 connected to GPIO21

  // Setup sensor:
  dht.begin();

  Serial.begin(115200);
}

void loop() {
  unsigned int sensorVariable = 0 ;           

  // Check what we want 
  RaspGPIO20 = digitalRead(9);            
  RaspGPIO21 = digitalRead(10);     

   Serial.println("Pin1: ");
   Serial.println(RaspGPIO20);
   Serial.println("Pin2: ");
   Serial.println(RaspGPIO21);

  // Update the sensor 
  wireIn1 = analogRead(A2);                   // Get values for left wire sensor 
  wireIn2 = analogRead(A3);                   // Get values for right wire sensor 
  
  if ( getTemp() )
    bitSet(sensorVariable, 0);                // 0001       - if high then it is to hot 
  if ( getHumidy() )
    bitSet(sensorVariable, 1);                // 0010       - If high then it is to humid
  if ( getRain() )                      
    bitSet(sensorVariable, 2);                // 0100       - If high then it is raining 
  if ( getIR() )
    bitSet(sensorVariable, 3);                // 1000       - If high then robot is at base


  // Print out 
  if (RaspGPIO20 == 1 && RaspGPIO21 == 0)
    Serial.println(wireIn1);
  if (RaspGPIO20 == 0 && RaspGPIO21 == 1)
    Serial.println(wireIn2);
  if (RaspGPIO20 == 1 && RaspGPIO21 == 1)
    Serial.println(sensorVariable);
}

int getTemp(){
  int maxTemp = 70; 
  
  // Read the temperature as Celsius:
  float value = dht.readTemperature();

  if (value > maxTemp)
    return 1; 
  else 
    return 0;
}

int getHumidy(){
  int maxHumidy = 90;

  // Read the humidity in %:
  float value = dht.readHumidity();

  if ( value > maxHumidy )
      return 1; 
  else 
    return 0;
}

int getRain(){
  int thresholdValue = 500;
  int value = analogRead(A0);
  
  if (value < thresholdValue)
      return 1; 
  else 
    return 0; 
}

int getIR(){
  int value = 0;
  int thresholdValue = 100;
  
  value = analogRead(A1); 
  
  if (value < thresholdValue)
    return 1; 
  else
    return 0; 
}
