#ifndef _MOTOR_
#define _MOTOR_

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <Servo.h>

class Motor
{
  public:
    int M1 = 3;     // Top Left
    int M2 = 5;     // Bottom Left
    int M3 = 6;     // Top Right
    int M4 = 9;     // Bottom Right                 Motor Pin assignments

    void init_motors();           // initialise the motors
    void RunMotors(Servo* Motor,int Gain);   // transmits commands to motors
}

#endif _MOTOR_
