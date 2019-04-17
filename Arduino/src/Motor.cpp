#include "Motor.h"
#include "PID.h"
#include <PID_v1.h>

pid Pid[4];
PID PID1(&Pid[0].Input, &Pid[0].Output, &Pid[0].Setpoint,0.875,Pid[0].Ki,Pid[0].Kd, DIRECT);
PID PID2(&Pid[1].Input, &Pid[1].Output, &Pid[1].Setpoint,Pid[1].Kp,Pid[1].Ki,Pid[1].Kd, DIRECT);
PID PID3(&Pid[2].Input, &Pid[2].Output, &Pid[2].Setpoint,0.875,Pid[2].Ki,Pid[2].Kd, DIRECT);
PID PID4(&Pid[3].Input, &Pid[3].Output, &Pid[3].Setpoint,Pid[3].Kp,Pid[3].Ki,Pid[3].Kd, DIRECT);

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

   PID1.SetMode(AUTOMATIC);
   PID2.SetMode(AUTOMATIC);
   PID3.SetMode(AUTOMATIC);
   PID4.SetMode(AUTOMATIC);
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

void Motor::rotateLeft(int Target,long timeBetFrames,int enc1,int enc2,int enc3,int enc4)
{
  Pid[0].Setpoint = Target;
  Pid[1].Setpoint = Target;
  Pid[2].Setpoint = Target;
  Pid[3].Setpoint = Target;
  
  Pid[0].Input = Pid[0].velocity(enc1,timeBetFrames);
  Pid[1].Input = Pid[1].velocity(enc2,timeBetFrames);
  Pid[2].Input = Pid[2].velocity(enc3,timeBetFrames);
  Pid[3].Input = Pid[3].velocity(enc4,timeBetFrames);
  
  PID1.Compute();
  PID2.Compute();
  PID3.Compute();
  PID4.Compute();
  
  RunMotors(M1,1,E1,Pid[0].Output);
  RunMotors(M2,0,E2,Pid[1].Output);
  RunMotors(M3,1,E3,Pid[2].Output);
  RunMotors(M4,0,E4,Pid[3].Output);
}

void Motor::rotateRight(int Target,long timeBetFrames,int enc1,int enc2,int enc3,int enc4)
{
  Pid[0].Setpoint = Target;
  Pid[1].Setpoint = Target;
  Pid[2].Setpoint = Target;
  Pid[3].Setpoint = Target;
  
  Pid[0].Input = Pid[0].velocity(enc1,timeBetFrames);
  Pid[1].Input = Pid[1].velocity(enc2,timeBetFrames);
  Pid[2].Input = Pid[2].velocity(enc3,timeBetFrames);
  Pid[3].Input = Pid[3].velocity(enc4,timeBetFrames);
  
  PID1.Compute();
  PID2.Compute();
  PID3.Compute();
  PID4.Compute();
  
  RunMotors(M1,0,E1,Pid[0].Output);
  RunMotors(M2,1,E2,Pid[1].Output);
  RunMotors(M3,0,E3,Pid[2].Output);
  RunMotors(M4,1,E4,Pid[3].Output);
}

void Motor::Left(int Target,long timeBetFrames,int enc1,int enc2,int enc3,int enc4)
{
  Pid[0].Setpoint = Target;
  Pid[1].Setpoint = Target;
  Pid[2].Setpoint = Target;
  Pid[3].Setpoint = Target;
  
  Pid[0].Input = Pid[0].velocity(enc1,timeBetFrames);
  Pid[1].Input = Pid[1].velocity(enc2,timeBetFrames);
  Pid[2].Input = Pid[2].velocity(enc3,timeBetFrames);
  Pid[3].Input = Pid[3].velocity(enc4,timeBetFrames);
  
  PID1.Compute();
  PID2.Compute();
  PID3.Compute();
  PID4.Compute();
  
  RunMotors(M1,0,E1,Pid[0].Output);
  RunMotors(M2,0,E2,Pid[1].Output);
  RunMotors(M3,1,E3,Pid[2].Output);
  RunMotors(M4,1,E4,Pid[3].Output);
}

void Motor::Right(int Target,long timeBetFrames,int enc1,int enc2,int enc3,int enc4)
{
  Pid[0].Setpoint = Target;
  Pid[1].Setpoint = Target;
  Pid[2].Setpoint = Target;
  Pid[3].Setpoint = Target;
  
  Pid[0].Input = Pid[0].velocity(enc1,timeBetFrames);
  Pid[1].Input = Pid[1].velocity(enc2,timeBetFrames);
  Pid[2].Input = Pid[2].velocity(enc3,timeBetFrames);
  Pid[3].Input = Pid[3].velocity(enc4,timeBetFrames);
  
  PID1.Compute();
  PID2.Compute();
  PID3.Compute();
  PID4.Compute();
  
  RunMotors(M1,1,E1,Pid[0].Output);
  RunMotors(M2,1,E2,Pid[1].Output);
  RunMotors(M3,0,E3,Pid[2].Output);
  RunMotors(M4,0,E4,Pid[3].Output);
}

void Motor::Backward(int Target,long timeBetFrames,int enc1,int enc2,int enc3,int enc4)
{
  Pid[0].Setpoint = Target;
  Pid[1].Setpoint = Target;
  Pid[2].Setpoint = Target;
  Pid[3].Setpoint = Target;
  
  Pid[0].Input = Pid[0].velocity(enc1,timeBetFrames);
  Pid[1].Input = Pid[1].velocity(enc2,timeBetFrames);
  Pid[2].Input = Pid[2].velocity(enc3,timeBetFrames);
  Pid[3].Input = Pid[3].velocity(enc4,timeBetFrames);
  
  PID1.Compute();
  PID2.Compute();
  PID3.Compute();
  PID4.Compute();
  
  RunMotors(M1,0,E1,Pid[0].Output);
  RunMotors(M2,0,E2,Pid[1].Output);
  RunMotors(M3,0,E3,Pid[2].Output);
  RunMotors(M4,0,E4,Pid[3].Output);
}

void Motor::Forward(int Target,long timeBetFrames,int enc1,int enc2,int enc3,int enc4)
{
  Pid[0].Setpoint = Target;
  Pid[1].Setpoint = Target;
  Pid[2].Setpoint = Target;
  Pid[3].Setpoint = Target;
  
  Pid[0].Input = Pid[0].velocity(enc1,timeBetFrames);
  Pid[1].Input = Pid[1].velocity(enc2,timeBetFrames);
  Pid[2].Input = Pid[2].velocity(enc3,timeBetFrames);
  Pid[3].Input = Pid[3].velocity(enc4,timeBetFrames);
  
  PID1.Compute();
  PID2.Compute();
  PID3.Compute();
  PID4.Compute();
  
  RunMotors(M1,1,E1,Pid[0].Output);
  RunMotors(M2,1,E2,Pid[1].Output);
  RunMotors(M3,1,E3,Pid[2].Output);
  RunMotors(M4,1,E4,Pid[3].Output);
}

void Motor::Stop()
{
  RunMotors(M1,1,E1,0);
  RunMotors(M2,0,E2,0);
  RunMotors(M3,1,E3,0);
  RunMotors(M4,0,E4,0);
}
