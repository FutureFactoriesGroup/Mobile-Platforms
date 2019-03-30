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

int xpos,ypos;
int xtar,ytar;
int xCmd,yCmd;

char Posid,Tarid;

//----------------------------------------------CLASS INSTANTIATIONS---------------------------------//
Motor motor;
RosInOut ros;

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
  
  Posid = ros.readPosID();
  Tarid = ros.readTarID();
  
  if (Posid == 'A')
  {
     xpos = ros.readPosX();
     ypos = ros.readPosY();
     
    Serial.print(xpos);
    Serial.print(" \t ");
    Serial.println(xpos);
  }
  else
  {
    motor.Forward(100,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
  }
  
  if (Tarid == 'A')
  {
     xtar = ros.readPosX();
     ytar = ros.readPosY();
     
    Serial.print(xtar);
    Serial.print(" \t ");
    Serial.println(ytar);
  }
  
  xCmd = xtar - xpos;
  yCmd = ytar - ypos;

  while(yCmd > 0)
  {
     motor.Forward(100,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
  }
  while(yCmd < 0)
  {
     motor.Backward(100,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
  }
  /*
  while(xCmd > 0)
  {
     motor.Right(100,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
  }
  while(xCmd < 0)
  {
     motor.Left(100,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
  }
  */
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
