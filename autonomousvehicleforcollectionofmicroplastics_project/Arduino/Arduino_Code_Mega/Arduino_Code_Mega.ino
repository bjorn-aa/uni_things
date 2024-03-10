
#include "HX711.h"

// For weight sensor
float calibration_factor = -212180; //This value is obtained by using the SparkFun_HX711_Calibration sketch
HX711 scale;

void setup() {
// Pin setup
  pinMode(22, OUTPUT);          // Left Ultrasonic        Trigger   Yellow 
  pinMode(23, INPUT);           // Left Ultrasonic        Echo      Green
  pinMode(24, OUTPUT);          // Mid Ultrasonic         Trigger   Yellow
  pinMode(25, INPUT);           // Mid Ultrasonic         Echo      Green
  pinMode(26, OUTPUT);          // Right Ultrasonic       Trigger   Yellow
  pinMode(27, INPUT);           // Right Ultrasonic       Echo      Green 
  pinMode(28, OUTPUT);          // Container Ultrasonic   Trigger   Yellow
  pinMode(29, INPUT);           // Contaienr Ultrasonic   Echo      Green 

// Load Cell setup
  scale.begin(3, 2);                    // Weight sensor  Pin 3 is DOUT(Green), Pin 2 is CLK(Yellow)
  scale.set_scale(calibration_factor);  // Set the calibration factor 
  scale.tare();                         //Assuming there is no weight on the scale at start up, reset the scale to 0

// Serial setup
  Serial.begin(9600);                   // Starts the serial communication
}


void loop() {
  // variables for the load cell
  unsigned int distance = 0;
  unsigned int load = 0;
  
  // Updates the value of distanceVariable and send's it out on the serial 
  distance = ultrasonicRead();
  load = loadCell();

  // serial printin
  if (load != 0)
    Serial.println(load);
  if (distance != 0)
    Serial.println(distance);
}

int loadCell(){
  float loadF = 0;
  unsigned int load = 0; 
  loadF = scale.get_units(), 2;
  load = loadF * 100;

  if (load > 0)
    return load;
  else
    return 0;
}

int ultrasonicLeft(){
  int distanceLeft;
  long duration;
// Clears the trigPin
  digitalWrite(22, LOW);
  delayMicroseconds(10);
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(22, HIGH);
  delayMicroseconds(10);
  digitalWrite(22, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(23, HIGH);
// Calculating the distance
  distanceLeft= duration*0.034/2;
  
  return distanceLeft;
}

int ultrasonicMid(){
  int distanceMid;
  long duration;
// Clears the trigPin
  digitalWrite(24, LOW);
  delayMicroseconds(10);
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(24, HIGH);
  delayMicroseconds(10);
  digitalWrite(24, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(25, HIGH);
// Calculating the distance
  distanceMid= duration*0.034/2;

  return distanceMid;
}

int ultrasonicRight(){
  int distanceRight;
  long duration;
// Clears the trigPin
  digitalWrite(26, LOW);
  delayMicroseconds(10);
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(26, HIGH);
  delayMicroseconds(10);
  digitalWrite(26, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(27, HIGH);
// Calculating the distance
  distanceRight= duration*0.034/2;

  return distanceRight;
}

int ultrasonicContainer(){
  int distanceContainer;
  long duration;
// Clears the trigPin
  digitalWrite(28, LOW);
  delayMicroseconds(10);
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(28, HIGH);
  delayMicroseconds(10);
  digitalWrite(28, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(29, HIGH);
// Calculating the distance
  distanceContainer= duration*0.034/2;

  return distanceContainer;
}

int ultrasonicRead(){
  int distance = 0;
  int distanceMax = 50;
  int distanceMin = 5; 
  int distanceMaxBack = 50;
  int distanceMinBack = 5; 
  int distanceVariable;
  distanceVariable = 0;

  
  //distance = ultrasonicLeft();
  if((ultrasonicLeft() >= distanceMin) && (ultrasonicLeft() <= distanceMax)){
    //ultrasonicLeft();  
    if((ultrasonicLeft() >= distanceMin) && (ultrasonicLeft() <= distanceMax)){
      //Serial.println("Something On the Left");
      bitSet(distanceVariable, 0);
    }
  }
 // ultrasonicMid();
  if((ultrasonicMid() >= distanceMin) && (ultrasonicMid() <= distanceMax)){
   // ultrasonicLeft();  
    if((ultrasonicMid() >= distanceMin) && (ultrasonicMid() <= distanceMax)){
      //Serial.println("Something On the Mid");
      bitSet(distanceVariable, 1);
    }
  }
  //ultrasonicRight();
  if((ultrasonicRight() >= distanceMin) && (ultrasonicRight() <= distanceMax)){
    //ultrasonicLeft();  
    if((ultrasonicRight() >= distanceMin) && (ultrasonicRight() <= distanceMax)){
      //Serial.println("Something On the Right");
      bitSet(distanceVariable, 2);
    }
  }
  //ultrasonicContainer();
  if((ultrasonicContainer() >= distanceMinBack) && (ultrasonicContainer() <= distanceMaxBack)){
    //ultrasonicLeft();  
    if((ultrasonicContainer() >= distanceMinBack) && (ultrasonicContainer() <= distanceMaxBack)){
      //Serial.println("Something On the Right");
      bitSet(distanceVariable, 3);
    }
  }

  /*
  if( ultrasonicContainer() <= 5 ){
    //ultrasonicContainer();  
    if( ultrasonicContainer() <= 5 ){
      //Serial.println("Container Full");
      bitSet(distanceVariable, 3);
    }
  }
  */
  
  return distanceVariable;
}
