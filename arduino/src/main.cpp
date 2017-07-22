#include "Arduino.h"

#define POTI_THRESH 2.0
#define POTI_MEANS 100
#define BOUNDS_COUNT 3

int analogPin = 3;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5

int val = 0;           // variable to store the value read
int oldVal = 0;
int boundNr = 0;
double redVal = 0;

void setup()
{
  Serial.begin(9600);          //  setup serial
}

void loop()
{
  redVal = 0;
  for(int i = 0; i < POTI_MEANS; i++)
  {
    redVal += analogRead(analogPin);
  }
  redVal = redVal / (double) POTI_MEANS;
  if( abs(redVal - (double) oldVal) > POTI_THRESH )
  {
    val = (int) redVal; 
    
    for(boundNr = 1; boundNr <= BOUNDS_COUNT; boundNr++)
    {
      if(val <= boundNr * 1024 / BOUNDS_COUNT) break;
    }
  }

  Serial.println(boundNr);             // debug value
  oldVal = val;
  delay(100);
}
