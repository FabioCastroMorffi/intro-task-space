#include <Wire.h>

// C++ code
//

//DO NOT MODIFY
uint8_t slaveAddress = 0b0001000;
const int button = 10;
const int potPin = 3;


void setup()
{
  //DO NOT MODIFY
  Serial.begin(9600); //Debugging Purposes
  pinMode(button, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  //Write your code here
  
}

void loop()
{
  //Write your code here

  //Keep for smooth simulation
  delay(10);
}

//Write any additional functions here
