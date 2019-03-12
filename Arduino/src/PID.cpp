#include "PID.h"

int pid::velocity(int pos, long tim)
{
  Velocity = (pos - prevPos)/tim;
  prevPos = pos;                      // calculate the rotational velocity from encoder counts
  return(Velocity);
}

float pid::error(float a, float b)
{
  c = a - b;                          // calculate the difference between a and b return as error
  return(c);
}
