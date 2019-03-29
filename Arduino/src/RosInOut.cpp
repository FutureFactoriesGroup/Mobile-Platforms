#include "RosInOut.h"

char RosInOut::readPosID()
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

int RosInOut::readPosX()
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

int RosInOut::readPosY()
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

char RosInOut::readPosID()
{
  if(Serial.available())
  {
     serialInput = Serial.read();
     char2int[increment] = (int)serialInput - 48;
     increment++;
        
     if (serialInput == '>')
     {
        increment = 0;
        
        ID = (char)char2int[11]+48;
     }
  }
  return(ID);
}

int RosInOut::readTarX()
{
  if(Serial.available())
  {
     serialInput = Serial.read();
     char2int[increment] = (int)serialInput - 48;
     increment++;
        
     if (serialInput == '>')
     {
        increment = 0;
        
        VectorX = char2int[13]*100;
        VectorX += char2int[14]*10;
        VectorX += char2int[15]*1;
     }
  }
  return(VectorX);
}

int RosInOut::readTarY()
{
  if(Serial.available())
  {
     serialInput = Serial.read();
     char2int[increment] = (int)serialInput - 48;
     increment++;
        
     if (serialInput == '>')
     {
        increment = 0;
        
        VectorY = char2int[17]*100;
        VectorY += char2int[18]*10;
        VectorY += char2int[19]*1;
     }
  }
  return(VectorY);
}
