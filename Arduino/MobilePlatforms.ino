
#include "PID.h"
#include "Motor.h"


unsigned long timer = 0;
unsigned long timeBetFrames = 0;

float timeStep = 0.1;

Motor motor;

void setup()
{
  motor.init_motors();
}

void loop()
{
  timer = millis();
  motor.Forward(200);
  timeBetFrames = millis() - timer;
  delay((timeStep*100) - timeBetFrames); //Run at 100Hz
}
