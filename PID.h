#ifndef _PID_
#define _PID_

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class pid                  // create motor control class
{
  public:
    float prevError  = 0;
    float prevSetPoint = 0;
    float InputErrorTotal = 0;
    float p=0,i=0,d=0,cont=0;
    float y = 0,yT = 0, N = 0.15;  

                              // PID variables and gains
                              float RKp = 8,RKi = 0,RKd = 10;
                              float PKp = 8,PKi = 0,PKd = 10;
                                   
    float error(float a, float b);  // error for feedback calculations
    float pid(float InputError,float SetPoint,unsigned long timeBetFrames,float Kp, float Ki, float Kd);  // PID controller                                 
};

#endif _PID_
