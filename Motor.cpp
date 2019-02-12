#include "Motor.h"

void Motor::init_motors()
{
   pinMode(M1,OUTPUT);
   pinMode(M2,OUTPUT);  
   pinMode(M3,OUTPUT);
   pinMode(M4,OUTPUT);
   
   pinMode(E1,OUTPUT);
   pinMode(E2,OUTPUT);  
   pinMode(E3,OUTPUT);
   pinMode(E4,OUTPUT);// intialise the motors to pins
}

void Motor::RunMotors(int Motor,int DGain,int Direction,int Gain)
{
  int x = 0;
    
   if(Gain > 255)
   {
        x = 255;                      // Actuator Limit Saturation 
   }
   if(Gain < 0)
   {
        x = 0;                      // Actuator Limit Saturation 
   }
   else
   {
        x = Gain;              
   }
  digitalWrite(Motor,DGain);
  analogWrite(Direction,Gain);       // write gain to motors
}

void Motor::Forward()
{
  RunMotors(M1,1,E1,200);
  RunMotors(M2,0,E2,200);
  RunMotors(M3,1,E3,200);
  RunMotors(M4,0,E4,200);
}

void Motor::Backward()
{
}

void Motor::Left()
{
}

void Motor::Right()
{
}
