#include <Wire.h>

// C++ code
//

//DO NOT MODIFY
uint8_t slaveAddress = 0b0001000;
int tolerance = 75;
int keys[] = {0, 820, 330};
int correct = 0;

const int toleranceLED = 2;
const int correctLED1 = 11;
const int correctLED2 = 10;
const int correctLED3 = 9;

void setup()
{
  //DO NOT MODIFY
  Serial.begin(9600); //Debugging Purposes
  pinMode(correctLED1, OUTPUT);
  pinMode(correctLED2, OUTPUT);
  pinMode(correctLED3, OUTPUT);
  pinMode(toleranceLED, OUTPUT);
  
  //Write your code here
  Wire.begin();
}

void loop()
{
  //Write your code here
  Wire.requestFrom(slaveAddress,2);
  
  while (Wire.available()) {
    int c = Wire.read();
    Serial.println(c);
  }
  //Keep this for smooth simulation
  delay(50);
}

//Write any additional functions here
