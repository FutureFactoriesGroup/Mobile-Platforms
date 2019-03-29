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
    int char2int[50];
    int increment = 0;
    int VectorX = 0;
    int VectorY = 0;

  public:
    char ID;
    char readPosID();       
    int readPosX(); 
    int readPosY(); //read in serial data and convert it to an integer
    
    char readTarID(); 
    int readTarX(); 
    int readTarY();
};

#endif  __ROSINOUT__
