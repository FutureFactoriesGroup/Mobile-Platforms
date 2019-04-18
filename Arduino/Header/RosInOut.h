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
    int increment = 0;
  public:
    char ID;
    int Path[200];
    int char2int[30];
    int Position[3];
    int numPoints = 0;
    
    int *readID();       
    void readPos(); //read in serial data and convert it to an integer
    void readTar();
};

#endif  __ROSINOUT__
