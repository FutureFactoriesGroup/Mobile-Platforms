#include "RosInOut.h"

int *RosInOut::readSerial()
{
  static int VectorXY[2];
  if(Serial.available())
  {
     serialInput = Serial.read();
     char2int[increment] = (int)serialInput - 48;
     increment++;
        
     if (serialInput == '>')
     {
        increment = 0;
     
        VectorXY[0] = char2int[1]*100;
        VectorXY[0] += char2int[2]*10;
        VectorXY[0] += char2int[3]*1;

        VectorXY[1] = char2int[5]*100;
        VectorXY[1] += char2int[6]*10;
        VectorXY[1] += char2int[7]*1;
     }
  }
  return(VectorXY);
}
