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

void RosInOut::readPos()
{
  char id = readID();
  if(id == 'A')
  {
     while(Serial.available() > 0)
     { 
        serialInput = Serial.read();
        char2int[numPoints] =  Serial.parseInt();
        Position[numPoints] = char2int[numPoints];
        numPoints++;
     
        if (serialInput == '>') 
        {
           *char2int = 0;
           *Position = {0};
           numPoints = 0;
           break;
        }
      }
   }
}

void RosInOut::readTar()
{
  char id = readID();
  if(id == 'P')
  {
     while(Serial.available() > 0)
     { 
        serialInput = Serial.read();
        char2int[numPoints] =  Serial.parseInt();
        Path[numPoints] = char2int[numPoints];
        numPoints++;
     
        if (serialInput == '>') 
        {
          *char2int = 0;
          *Path = {0};
          numPoints = 0;
          break;
        }
      }
  }
}
