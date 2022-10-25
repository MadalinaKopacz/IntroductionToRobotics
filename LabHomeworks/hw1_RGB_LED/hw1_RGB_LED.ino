const int redLedPin = 9;
const int greenLedPin = 10;
const int blueLedPin = 11;

const int redSensorPin = A0;
const int greenSensorPin = A1;
const int blueSensorPin = A2;

const int fromLow = 0;
const int fromHigh = 1023;
const int toLow = 0;
const int toHigh = 255;

int redLedValue = 0;
int greenLedValue = 0;
int blueLedValue = 0;

int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

void setup() {
  pinMode(redSensorPin,INPUT);
  pinMode(greenSensorPin,INPUT);
  pinMode(blueSensorPin,INPUT);
  
  pinMode(redLedPin,OUTPUT);
  pinMode(greenLedPin,OUTPUT);
  pinMode(blueLedPin,OUTPUT);

  Serial.begin(9600);
}

void readSensorValues(int &redSensorValue, int &greenSensorValue, int &blueSensorValue) {
  redSensorValue = analogRead(redSensorPin);
  greenSensorValue = analogRead(greenSensorPin);
  blueSensorValue = analogRead(blueSensorPin);
}

void mapSensorValues(int &redLedValue, int &greenLedValue, int &blueLedValue) {
  redLedValue = map(redSensorValue, fromLow, fromHigh, toLow, toHigh);
  greenLedValue = map(greenSensorValue, fromLow, fromHigh, toLow, toHigh);
  blueLedValue = map(blueSensorValue, fromLow, fromHigh, toLow, toHigh);
}

void writeColorValues(const int redLedValue, const int greenLedValue, const int blueLedValue) {
  analogWrite(redLedPin,redLedValue);
  analogWrite(greenLedPin,greenLedValue);
  analogWrite(blueLedPin,blueLedValue);
}

void loop() {
  readSensorValues(redSensorValue, greenSensorValue, blueSensorValue);
  mapSensorValues(redLedValue, greenLedValue, blueLedValue);
  writeColorValues(redLedValue, greenLedValue, blueLedValue);  
}