//----------------------------------------HEADER FILES---------------------------------------------//
#include <EnableInterrupt.h>
#include <PID_v1.h>

#include "Motor.h"
#include "RosInOut.h"
#include "PID.h"

//------------------------------------ENCODER PIN DEFINITIONS---------------------------------------//
#define M1PinA  A8
#define M1PinB  A9
#define M2PinA  A10
#define M2PinB  A11
#define M3PinA  A12
#define M3PinB  A13
#define M4PinA  A14
#define M4PinB  A15

unsigned long timer = 0;
unsigned long timeBetFrames = 0;

int M1encoderPos = 0;
int M2encoderPos = 0;
int M3encoderPos = 0;
int M4encoderPos = 0;

int i;
int *xpos,*ypos;
int *xtar,*ytar;
int *ang;
int xCmd,yCmd,aCmd;
bool runn = 0;
char id = NULL;

//----------------------------------------------CLASS INSTANTIATIONS---------------------------------//
Motor motor;
RosInOut ros;
pid Pidxya;
PID PIDx((double*)xpos, (double*)xCmd, (double*)xtar,10,2,0, DIRECT);
PID PIDy((double*)ypos, (double*)yCmd, (double*)ytar,10,2,0, DIRECT);
PID PIDa((double*)ang, (double*)aCmd, 0,10,2,0, DIRECT);
//---------------------------------------------SETUP FUCNTION----------------------------------------//
void setup()
{
  Serial.begin (9600);
  motor.init_motors();
  
  pinMode(M1PinA, INPUT);
  pinMode(M1PinB, INPUT);
  pinMode(M2PinA, INPUT);
  pinMode(M2PinB, INPUT);
  pinMode(M3PinA, INPUT);
  pinMode(M3PinB, INPUT);
  pinMode(M4PinA, INPUT);
  pinMode(M4PinB, INPUT);
  
  enableInterrupt(M1PinA, doM1Encoder, CHANGE);
  enableInterrupt(M2PinA, doM2Encoder, CHANGE);
  enableInterrupt(M3PinA, doM3Encoder, CHANGE);
  enableInterrupt(M4PinA, doM4Encoder, CHANGE);
}

//---------------------------------------Main Control Loop-------------------------------------------//
void loop()
{
  timer = millis();
  
  runn = 1;
  while(runn != 0)
  {
     ros.readTar();
     int pathlenght = ros.Path[0];
     int X[pathlenght],Y[pathlenght];
     for(int x = 1;x<ros.numPoints-1;x++)
     {
        X[x] = ros.Path[x+1];
        Serial.println(X[x]);
     }
     for(int x = 1;x<(ros.numPoints)/2;x++)
     {
       Y[x] = ros.Path[2*x];
     }
       
     while(i<ros.numPoints)
     {
        ros.readPos();

        *xpos = ros.Position[0];
        *ypos = ros.Position[1];
        *ang = ros.Position[2];
           
        *xtar = X[i];
        *ytar = Y[i];
              
         PIDx.Compute();
         PIDy.Compute();
         PIDa.Compute();
  
         if (xCmd>0)
         {
           motor.Forward(xCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
         }
         else if(xCmd<0)
         {
            motor.Backward(xCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
         }
         if (yCmd>0)
         {
            motor.Left(yCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
         }
         else if(yCmd<0)
         {
            motor.Right(yCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
         }
         if (aCmd>0)
         {
            motor.rotateLeft(yCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
         }
         else if(aCmd<0)
         {
            motor.rotateRight(yCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
         }
              
             /* Serial.print(*xpos);
              Serial.print(" \t ");
              Serial.print(*ypos);
              Serial.print(" \t ");
              Serial.print(*ang);
              Serial.print(" \t ");
              Serial.print(*xtar);
              Serial.print(" \t ");
              Serial.print(*ytar);
              Serial.print(" \t ");
              Serial.print(xCmd);
              Serial.print(" \t ");
              Serial.print(yCmd);
              Serial.print(" \t ");
              Serial.println(yCmd);*/
          if(xCmd == 0 && yCmd == 0 && aCmd == 0)
          {
                i++;
          }
       }
       runn = 0;
  }
  motor.Stop();
  timeBetFrames = millis() - timer;
  delay(20 - timeBetFrames); //Run at 12Hz
}

//----------------------------------------------ENCODER SETUP----------------------------------------------//
void doM1Encoder() 
{
  // look for a low-to-high on channel A
  if (digitalRead(M1PinA) == HIGH)
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(M1PinB) == LOW) 
    {
      M1encoderPos = M1encoderPos + 1;         // CW
    }
    else 
    {
      M1encoderPos = M1encoderPos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(M1PinB) == HIGH)
    {
      M1encoderPos = M1encoderPos + 1;          // CW
    }
    else 
    {
      M1encoderPos = M1encoderPos - 1;          // CCW
    }
  }
}

void doM2Encoder() 
{
  // look for a low-to-high on channel A
  if (digitalRead(M2PinA) == HIGH) 
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(M2PinB) == LOW)
    {
      M2encoderPos = M2encoderPos + 1;         // CW
    }
    else 
    {
      M2encoderPos = M2encoderPos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(M2PinB) == HIGH) 
    {
      M2encoderPos = M2encoderPos + 1;          // CW
    }
    else 
    {
      M2encoderPos = M2encoderPos - 1;          // CCW
    }
  }
}

void doM3Encoder() 
{
  // look for a low-to-high on channel A
  if (digitalRead(M3PinA) == HIGH) 
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(M3PinB) == LOW)
    {
      M3encoderPos = M3encoderPos + 1;         // CW
    }
    else 
    {
      M3encoderPos = M3encoderPos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(M3PinB) == HIGH)
    {
      M3encoderPos = M3encoderPos + 1;          // CW
    }
    else 
    {
      M3encoderPos = M3encoderPos - 1;          // CCW
    }
  }
}

void doM4Encoder() 
{
  // look for a low-to-high on channel A
  if (digitalRead(M4PinA) == HIGH) 
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(M4PinB) == LOW) 
    {
      M4encoderPos = M4encoderPos + 1;         // CW
    }
    else
    {
      M4encoderPos = M4encoderPos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(M4PinB) == HIGH) 
    {
      M4encoderPos = M4encoderPos + 1;          // CW
    }
    else
    {
      M4encoderPos = M4encoderPos - 1;          // CCW
    }
  }
}
