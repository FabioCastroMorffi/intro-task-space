#include <Wire.h>

// C++ code
//

//DO NOT MODIFY
uint8_t slaveAddress = 0b0001000;
const int button = 10;
const int potPin = 3;

bool prevState = 0;
bool lastingState = 0;
uint16_t potValue = 0;

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
  potValue = analogRead(potPin);
  bool currState = digitalRead(button);
  if (currState && !prevState) {
    lastingState = true;
  }
  prevState = currState;

  //Keep for smooth simulation
  delay(10);
}

//Write any additional functions here
void requestEvent() {
  uint16_t msg = potValue;
  if (lastingState) {
    msg |= 0x8000;
    lastingState = false;
  }
  Wire.write(msg >> 8);
  Wire.write(msg & 0xFF);
}
