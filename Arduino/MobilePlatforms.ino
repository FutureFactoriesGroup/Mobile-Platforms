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

int i = 0;
double xpos,ypos;
double xtar,ytar;
double angpos,angtar;
double xCmd,yCmd,aCmd;
double xerr,yerr,angerr;
bool runn = 0;
char id = NULL;

//----------------------------------------------CLASS INSTANTIATIONS---------------------------------//
Motor motor;
RosInOut ros;
pid Pidxya;
PID PIDx(&xpos, &xCmd, &xtar,1,0.2,0.1, DIRECT);
PID PIDy(&ypos, &yCmd, &ytar,1,0.2,0.1, DIRECT);
PID PIDa(&angpos, &aCmd,&angtar,1,0.2,0.1, DIRECT);
//---------------------------------------------SETUP FUCNTION----------------------------------------//
void setup()
{
  Serial.begin (9600);
  motor.init_motors();
  
  PIDx.SetMode(AUTOMATIC);
  PIDy.SetMode(AUTOMATIC);
  PIDa.SetMode(AUTOMATIC);
  
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
//<P,047,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400>
//<A,110,220,120>
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
     for(int x = 1;x<ros.numPoints/2;x++)
     {
        X[x-1] = ros.Path[2*x - 1];
     }
     for(int x = 1;x<(ros.numPoints)/2;x++)
     {
       Y[x-1] = ros.Path[2*x];
     }

     while(i<(ros.numPoints/2)-1)
     {

        xtar = X[i];
        ytar = Y[i];
     
        while(1)
        {
          ros.readPos();

          angpos = ros.Position[3];
          angpos = angpos/100;

          int x = xtar - xpos;
          int y = ytar - ypos;
         
          angtar = atan(x/y);

          angerr = Pidxya.error(angtar,angpos);
          
          PIDa.Compute();
          if (angerr>0)
          {
            motor.rotateLeft(aCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else if(angerr<0)
          {
            motor.rotateRight(aCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else
          {
            motor.Stop();
            break;
          }
          Serial.print(angtar);
          Serial.print(" \t ");
          Serial.print(angpos);
          Serial.print(" \t ");
          Serial.println(aCmd);
        }
        
        while(1)
        {
          ros.readPos();

          xpos = ros.Position[1];

          xerr = Pidxya.error(xtar,xpos);
        
          PIDx.Compute();
  
          if (xerr>0)
          {
             motor.Forward(xCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else if(xerr<0)
          {
            motor.Backward(xCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else
          {
            motor.Stop();
            break;
          }
          Serial.print(xtar);
          Serial.print(" \t ");
          Serial.print(xpos);
          Serial.print(" \t ");
          Serial.println(xCmd);
        }
        
        while(1)
        {
          ros.readPos();

          ypos = ros.Position[2];

          yerr = Pidxya.error(ytar,ypos);
          
          PIDy.Compute();
          
          if (yerr>0)
          {
            motor.Left(yCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else if(yerr<0)
          {
            motor.Right(yCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else
          {
            motor.Stop();
            break;
          }
          Serial.print(ytar);
          Serial.print(" \t ");
          Serial.print(ypos);
          Serial.print(" \t ");
          Serial.println(yCmd);
        }
        
        if(xerr == 0 && yerr == 0 && angerr == 0)
        {
             i++;
        }
        
       }
       i = 0;
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
