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
    const int E1 = 3; //<Motor1 Speed
    const int E2 = 11;//<Motor2 Speed
    const int E3 = 5; //<Motor3 Speed
    const int E4 = 6; //<Motor4 Speed

    const int M1 = 4; //<Motor1 Direction
    const int M2 = 12;//<Motor2 Direction
    const int M3 = 8; //<Motor3 Direction
    const int M4 = 7; //<Motor4 Direction

    void init_motors();           // initialise the motors
    void RunMotors(int Motor,int DGain,int Direction,int Gain);   // transmits commands to motors
    void Forward(int Tagret);
    void Backward(int Tagret);
    void Left(int Tagret);
    void Right(int Tagret);
};

#endif _MOTOR_
