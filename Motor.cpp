#include "Motor.h"

#include <Servo.h>

extern Servo Motor1,Motor2,Motor3,Motor4;

void Initialise::init_motors()
{
  Motor1.attach(M1);
  Motor2.attach(M2);
  Motor3.attach(M3);
  Motor4.attach(M4);                 // intialise the motors to pins
}
void Motors::RunMotors(Servo* Motor,int Gain)
{
  int x = 0;
    
   if(Gain > 2000)
   {
        x = 2000;                      // Actuator Limit Saturation 
   }
   if(Gain < 1000)
   {
        x = 1000;                      // Actuator Limit Saturation 
   }
   else
   {
        x = Gain;              
   }
   Motor->writeMicroseconds(x);       // write gain to motors
}
