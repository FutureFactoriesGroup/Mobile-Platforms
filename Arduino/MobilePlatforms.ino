#include <EnableInterrupt.h>
#include "Motor.h"
#include "RosInOut.h"
#include "PID.h"

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

Motor motor;
RosInOut ros;
pid Pid1;

int xval,yval;
char id;

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

void loop()
{
  timer = millis();
  
  id = ros.readID();
  
  if (id == 'A')
  {
     xval = ros.readX();
     yval = ros.readY();
     
    Serial.print(xval);
    Serial.print(" \t ");
    Serial.println(yval);
  }
  else
  {
     Serial.print(M1encoderPos, DEC);
     Serial.print(" \t ");
     
     int velocity1 = Pid1.velocity(M1encoderPos,timeBetFrames);
     Serial.print(velocity1);
     Serial.print(" \t ");
     
     int Tagret = 100;
     float error1 = 0, pid1 = 0;
     error1 = Pid1.error(Tagret,velocity1);
     pid1 = Pid1.PIDD(error1,Tagret,timeBetFrames, Pid1.kp,Pid1.ki,Pid1.kd);
     motor.RunMotors(motor.M1,1,motor.E1,(int)pid1);
     Serial.println((int)pid1);
     
     //motor.Forward(100,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
     //motor.Stop();
  }
  
  /*motor.RunMotors(motor.M4,1,motor.E4,100);
  Serial.print("|M1|");
  Serial.print(M1encoderPos, DEC);
  Serial.print("|M2|");
  Serial.print(M2encoderPos, DEC);
  Serial.print("|M3|");
  Serial.print(M3encoderPos, DEC);
  Serial.print("|M4|");
  Serial.println(M4encoderPos, DEC);
  */
  
  timeBetFrames = millis() - timer;
  //delay(50 - timeBetFrames); //Run at 100Hz
}
    
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
