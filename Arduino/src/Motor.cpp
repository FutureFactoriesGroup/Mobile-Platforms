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

void Motor::Forward(int Tagret)
{
  RunMotors(M1,1,E1,Tagret);
  RunMotors(M2,0,E2,Tagret);
  RunMotors(M3,1,E3,Tagret);
  RunMotors(M4,0,E4,Tagret);
}

void Motor::Backward(int Tagret)
{
  RunMotors(M1,0,E1,Tagret);
  RunMotors(M2,1,E2,Tagret);
  RunMotors(M3,0,E3,Tagret);
  RunMotors(M4,1,E4,Tagret);
}

void Motor::Left(int Tagret)
{
  RunMotors(M1,0,E1,Tagret);
  RunMotors(M2,0,E2,Tagret);
  RunMotors(M3,0,E3,Tagret);
  RunMotors(M4,0,E4,Tagret);
}

void Motor::Right(int Tagret)
{
  RunMotors(M1,1,E1,Tagret);
  RunMotors(M2,1,E2,Tagret);
  RunMotors(M3,1,E3,Tagret);
  RunMotors(M4,1,E4,Tagret);
}
