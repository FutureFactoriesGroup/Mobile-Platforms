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
    float prevError  = 0;
    float prevSetPoint = 0;
    float InputErrorTotal = 0;
    float p=0,i=0,d=0,cont=0;
    float y = 0,yT = 0, N = 0.15;  

    int Velocity = 0;
    int prevPos = 0;
                              // PID variables and gains
                              float kp = 0.5,ki = 0.01,kd = 0;
                              
    int velocity(int pos, long tim);                               
    float error(float a, float b);  // error for feedback calculations
    float PIDD(float InputError,float SetPoint,unsigned long timeBetFrames,float Kp, float Ki, float Kd);  // PID controller                                 
};

#endif _PID_
