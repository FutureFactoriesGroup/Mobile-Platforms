#include "RosInOut.h"

char RosInOut::readID()
{
  if(Serial.available())
  {
     serialInput = Serial.read();
     char2int[increment] = (int)serialInput - 48;
     increment++;
        
     if (serialInput == '>')
     {
        increment = 0;
        
        ID = (char)char2int[1]+48;
     }
  }
  return(ID);
}

int RosInOut::readX()
{
  if(Serial.available())
  {
     serialInput = Serial.read();
     char2int[increment] = (int)serialInput - 48;
     increment++;
        
     if (serialInput == '>')
     {
        increment = 0;
        
        VectorX = char2int[3]*100;
        VectorX += char2int[4]*10;
        VectorX += char2int[5]*1;
     }
  }
  return(VectorX);
}

int RosInOut::readY()
{
  if(Serial.available())
  {
     serialInput = Serial.read();
     char2int[increment] = (int)serialInput - 48;
     increment++;
        
     if (serialInput == '>')
     {
        increment = 0;
        
        VectorY = char2int[7]*100;
        VectorY += char2int[8]*10;
        VectorY += char2int[9]*1;
     }
  }
  return(VectorY);
}
