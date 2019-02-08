#include "PID.h"
#include "Motor.h"
#include <Servo.h>

unsigned long timer = 0;
unsigned long timeBetFrames = 0;

float timeStep = 0.1;

void setup()
{
}

void loop()
{
  timer = millis();
  
  timeBetFrames = millis() - timer;
  delay((timeStep*100) - timeBetFrames); //Run at 100Hz
}
