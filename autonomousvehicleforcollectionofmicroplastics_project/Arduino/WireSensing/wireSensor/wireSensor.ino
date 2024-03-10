int wireIn1 = 0;
int wireIn2 = 0;
int wireToRead = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  wireIn1 = analogRead(14);
  wireIn2 = analogRead(15);
  wireToRead = digitalRead(5);

  if (!readAllowed)
  {
  if(wireToRead == 0)
  {
    Serial.println(wireIn1);
  }
  else
  {
    Serial.println(wireIn2);
  }
  }
