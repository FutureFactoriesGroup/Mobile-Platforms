#ifndef _PID_
#define _PID_

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class pid                  // create PID class
{
  public:
    int Velocity = 0;
    int prevPos = 0;
    float c;
    double Input,Output,Setpoint;
    double Kp = 0.85,Ki = 0.012,Kd = 0; // PID variables and gains
    
    int velocity(int pos, long tim);  // motor angular velocity                               
    float error(float a, float b);    // error for feedback calculations
};

#endif _PID_
