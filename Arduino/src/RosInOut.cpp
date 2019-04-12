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
        *char2int = 0;
     }
  }
  return(ID);
}

int *RosInOut::readPos()
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
        
        VectorXY[0] = char2int[3]*100;
        VectorXY[0] += char2int[4]*10;
        VectorXY[0] += char2int[5]*1;

        VectorXY[1] = char2int[7]*100;
        VectorXY[1] += char2int[8]*10;
        VectorXY[1] += char2int[9]*1;
        *char2int = 0;
     }
  }
  return(VectorXY);
}

int *RosInOut::readAng()
{
  static int Angle[1];
  if(Serial.available())
  {
     serialInput = Serial.read();
     char2int[increment] = (int)serialInput - 48;
     increment++;
        
     if (serialInput == '>')
     {
        increment = 0;
        
         Angle[0] = char2int[11]*100;
         Angle[0] += char2int[12]*10;
         Angle[0] += char2int[13]*1;
        *char2int = 0;
     }
  }
  return(Angle);
}

void RosInOut::readTar()
{
  if(Serial.available())
  {
     serialInput = Serial.read();
     char2int[increment] = (int)serialInput - 48;
     increment++;

     if (serialInput == '>')
     {
        increment = 0;
        int dim = char2int[3]*100;
        dim += char2int[4]*10;
        dim += char2int[5]*1;
        
        for(int x = 0; x< ((dim+1)/4); x++)
        {
          Path[x] = char2int[7+4*x]*100;
          Path[x] += char2int[8+4*x]*10;
          Path[x] += char2int[9+4*x]*1;

          Path[x+1] = char2int[11+4*x]*100;
          Path[x+1] += char2int[12+4*x]*10;
          Path[x+1] += char2int[13+4*x]*1;
          numPoints++;
        }
        *char2int = 0;
     }
  }
}
