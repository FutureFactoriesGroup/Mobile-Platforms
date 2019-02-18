#include "PID.h"
#include "Motor.h"
#include "RosInOut.h"

unsigned long timer = 0;
unsigned long timeBetFrames = 0;
float timeStep = 0.1;

Motor motor;
pid Pid;
RosInOut ros;

int xval,yval;

void setup()
{
  motor.init_motors();
}

void loop()
{
  timer = millis();
  
  xval = ros.readSerial();
  yval = ros.readSerial()+1;
  
  motor.Forward(200);
  timeBetFrames = millis() - timer;
  delay((timeStep*100) - timeBetFrames); //Run at 100Hz
}
