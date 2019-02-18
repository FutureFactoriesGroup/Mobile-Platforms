#ifndef __ROSINOUT__
#define __ROSINOUT__

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class RosInOut                  // create ROS Communication class
{
  private:
    char serialInput;
    int char2int[9];
    int increment = 0;

  public:
    int *readSerial();
};

#endif  __ROSINOUT__
