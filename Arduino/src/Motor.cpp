#include "Motor.h"
#include "PID.h"

pid Pid;

void Motor::init_motors()
{
   pinMode(M1,OUTPUT);
   pinMode(M2,OUTPUT);  
   pinMode(M3,OUTPUT);
   pinMode(M4,OUTPUT);
   
   pinMode(E1,OUTPUT);
   pinMode(E2,OUTPUT);  
   pinMode(E3,OUTPUT);
   pinMode(E4,OUTPUT); // intialise the motors to pins
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

void Motor::Forward(int Tagret,long timeBetFrames,int enc1,int enc2,int enc3,int enc4)
{
  velocity1 = Pid.velocity(enc1,timeBetFrames);
  error1 = Pid.error(Tagret,velocity1);
  pid1 = Pid.PIDD(error1,Tagret, timeBetFrames, Pid.kp,Pid.ki,Pid.kd);
  
  velocity2 = Pid.velocity(enc2,timeBetFrames);
  error2 = Pid.error(Tagret,velocity2);
  pid2 = Pid.PIDD(error2,Tagret, timeBetFrames, Pid.kp,Pid.ki,Pid.kd);

  velocity3 = Pid.velocity(enc3,timeBetFrames);
  error3 = Pid.error(Tagret,velocity3);
  pid3 = Pid.PIDD(error3,Tagret, timeBetFrames, Pid.kp,Pid.ki,Pid.kd);
  
  velocity4 = Pid.velocity(enc4,timeBetFrames);
  error4 = Pid.error(Tagret,velocity4);
  pid4 = Pid.PIDD(error4,Tagret, timeBetFrames, Pid.kp,Pid.ki,Pid.kd);

  RunMotors(M1,1,E1,(int)pid1);
  RunMotors(M2,0,E2,(int)pid2);
  RunMotors(M3,1,E3,(int)pid3);
  RunMotors(M4,0,E4,(int)pid4);
}

void Motor::Backward(int Tagret,long timeBetFrames,int enc1,int enc2,int enc3,int enc4)
{
  RunMotors(M1,0,E1,Tagret);
  RunMotors(M2,1,E2,Tagret);
  RunMotors(M3,0,E3,Tagret);
  RunMotors(M4,1,E4,Tagret);
}

void Motor::Left(int Tagret,long timeBetFrames,int enc1,int enc2,int enc3,int enc4)
{
  RunMotors(M1,0,E1,Tagret);
  RunMotors(M2,0,E2,Tagret);
  RunMotors(M3,1,E3,Tagret);
  RunMotors(M4,1,E4,Tagret);
}

void Motor::Right(int Tagret,long timeBetFrames,int enc1,int enc2,int enc3,int enc4)
{
  RunMotors(M1,1,E1,Tagret);
  RunMotors(M2,1,E2,Tagret);
  RunMotors(M3,0,E3,Tagret);
  RunMotors(M4,0,E4,Tagret);
}

void Motor::rotateLeft(int Tagret,long timeBetFrames,int enc1,int enc2,int enc3,int enc4)
{
  RunMotors(M1,0,E1,Tagret);
  RunMotors(M2,0,E2,Tagret);
  RunMotors(M3,0,E3,Tagret);
  RunMotors(M4,0,E4,Tagret);
}

void Motor::rotateRight(int Tagret,long timeBetFrames,int enc1,int enc2,int enc3,int enc4)
{
  RunMotors(M1,1,E1,Tagret);
  RunMotors(M2,1,E2,Tagret);
  RunMotors(M3,1,E3,Tagret);
  RunMotors(M4,1,E4,Tagret);
}

void Motor::Stop()
{
  RunMotors(M1,1,E1,0);
  RunMotors(M2,0,E2,0);
  RunMotors(M3,1,E3,0);
  RunMotors(M4,0,E4,0);
}
