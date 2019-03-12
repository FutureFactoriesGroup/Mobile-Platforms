#ifndef _MOTOR_
#define _MOTOR_

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Motor
{
  public:
    const int E1 = 11;  //<Motor1 Speed
    const int E2 = 3;   //<Motor2 Speed
    const int E3 = 6;   //<Motor3 Speed
    const int E4 = 5;   //<Motor4 Speed

    const int M1 = 12;  //<Motor1 Direction
    const int M2 = 4;   //<Motor2 Direction
    const int M3 = 7;   //<Motor3 Direction
    const int M4 = 8;   //<Motor4 Direction
  
    void init_motors();           // initialise the motors
    void RunMotors(int Motor,int DGain,int Direction,int Gain);   // transmits commands to motors
    
    void Forward(int Target,long timeBetFrames,int enc1,int enc2,int enc3,int enc4);
    void Backward(int Target,long timeBetFrames,int enc1,int enc2,int enc3,int enc4);
    void Left(int Target,long timeBetFrames,int enc1,int enc2,int enc3,int enc4);       // movement
    void Right(int Target,long timeBetFrames,int enc1,int enc2,int enc3,int enc4);
    void rotateLeft(int Target,long timeBetFrames,int enc1,int enc2,int enc3,int enc4);
    void rotateRight(int Target,long timeBetFrames,int enc1,int enc2,int enc3,int enc4);
    void Stop();
};

#endif _MOTOR_
