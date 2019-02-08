#include "PID.h"

float pid::error(float a, float b)
{
  float c;
  c = a - b;                  // calculate the difference between a and b return as error
  return(c);
}

float pid::pid(float InputError,float SetPoint,unsigned long timeBetFrames,float Kp, float Ki, float Kd)
{
  InputErrorTotal += InputError;
  yT += y;
  
  p = InputError*Kp;
  i = InputErrorTotal*Ki*timeBetFrames;
  //d = (Kd*(InputError-prevError))/timeBetFrames;
  y = N*(InputError - (yT*timeBetFrames));   // Derivative Prefilter
  d = y*Kd;
  cont = p + i + d;
  prevError = InputError;
  
  // integral anti-windup
  if(cont > 200 )
  {
    cont = 200;
    if (InputError > 0)
    {
      InputErrorTotal = 0;
    }
  }
  else if(cont < -200 )
  {
    cont = -200;
    if (InputError < 0)
    {
      InputErrorTotal = 0;
    }
  }
  
  //Derivative Setpoint Weighting
  if((SetPoint - prevSetPoint) == 0)
  {
    d  = 0;
  }
  prevSetPoint = SetPoint;
  
  return(cont);
}
