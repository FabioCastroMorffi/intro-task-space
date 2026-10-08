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

int ledArr[3] = {correctLED1, correctLED2, correctLED3};
uint8_t b1 = 0, b2 = 0;

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
  
  while (Wire.available() >= 2) {
    b1 = Wire.read();
    b2 = Wire.read();
  }
  uint16_t b1b2 = (b1 << 8) | b2;
  uint16_t potValue = b1b2 & 0x3FF;
  uint16_t region = tolerance + potValue;
  bool buttonState = b1b2 >> 15;
  
  if (correct != 3 && region >= keys[correct] && potValue <= keys[correct]) {
    digitalWrite(toleranceLED, HIGH);
  }
  else {
    digitalWrite(toleranceLED, LOW);
  }

  if (buttonState) {
    if (correct == 3) {
      digitalWrite(ledArr[2], LOW);
      correct--;
    }
    else if (region >= keys[correct] && potValue <= keys[correct]) {
      digitalWrite(ledArr[correct], HIGH);
      correct++;
    }
    else {
      if (correct) {
        digitalWrite(ledArr[correct-1], LOW);
        correct--;
      }
    }
  }
  //Keep this for smooth simulation
  delay(50);
}

//Write any additional functions here
