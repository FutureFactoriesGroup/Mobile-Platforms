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
    int char2int[50] = {0};
    int increment = 0;
    int VectorX = 0;
    int VectorY = 0;

  public:
    char ID;
    char readID();       
    int *readPos(); //read in serial data and convert it to an integer
    int *readTar();
    int *readAng();
};

#endif  __ROSINOUT__
