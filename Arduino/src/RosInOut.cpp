#include "RosInOut.h"

int *RosInOut::readID()
{
  while(Serial.available()>0)
  {
     //delay(20);
     serialInput = Serial.read();
     char2int[increment] = Serial.parseInt();
     increment++;
        
     if (serialInput == ')')
     {
        //Serial.flush();
        increment = 0; 
        Position[0] = char2int[0];
        Position[1] = char2int[1];
        Position[2] = char2int[2];
        break;
     }
  }
  return(Position);
}

int *RosInOut::readVel()
{
  if(Serial.available())
  {
     serialInput = Serial.read();
     char2int[increment] = Serial.parseInt();
     increment++;
        
     if (serialInput == ')')
     {
        increment = 0; 
        Vel[0] = char2int[0];
        Vel[1] = char2int[1];
     }
  }
  return(Vel);
}

void RosInOut::readPos()
{
     while(Serial.available() > 0)
     {  
        serialInput = Serial.read();
        char2int[numPoints] =  Serial.parseInt();
        Position[numPoints] = char2int[numPoints];
        numPoints++;
     
        if (serialInput == '\n') 
        {
           *char2int = 0;
           *Position = {0};
           numPoints = 0;
           break;
        }
      }
}

void RosInOut::readTar()
{
     while(Serial.available() > 0)
     { 
        serialInput = Serial.read();
        char2int[numPoints] =  Serial.parseInt();
        Path[numPoints] = char2int[numPoints];
        numPoints++;
     
        if (serialInput == '\n') 
        {
          *char2int = 0;
          *Path = {0};
          numPoints = 0;
          break;
        }
      }
}
