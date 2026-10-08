#include <Wire.h>

// C++ code
//

//DO NOT MODIFY
uint8_t slaveAddress = 0b0001000;
const int button = 10;
const int potPin = 3;

bool prevState = LOW;
uint8_t b1, b2;
// NOTE: First and second byte to be declared;
void setup()
{
  //DO NOT MODIFY
  Serial.begin(9600); //Debugging Purposes
  pinMode(button, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  //Write your code here
  Wire.begin(slaveAddress);
  Wire.onRequest(requestEvent);
}

void loop()
{
  //Write your code here
  uint16_t msg = analogRead(potPin);
  bool currState = digitalRead(button);
  if (currState && !prevState) {
    msg |= 0x8000;
  }
  prevState = currState;

  Wire.beginTransmission()
  //Keep for smooth simulation
  delay(10);
}

//Write any additional functions here
void requestEvent() {
  ;
}
