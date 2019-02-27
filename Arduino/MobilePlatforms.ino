#include <EnableInterrupt.h>
#include "PID.h"
#include "Motor.h"
#include "RosInOut.h"

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
pid Pid;
RosInOut ros;

int xval,yval;

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
  
  float error = 0, pid = 0;
  int velocity1 = 0;velocity2 = 0;
  int velocity3 = 0;velocity4 = 0;
  
  //xval = ros.readSerial();
  //yval = ros.readSerial()+1;
 /* 
  Serial.print("|M1|");
  Serial.print(M1encoderPos, DEC);
  Serial.print("|M2|");
  Serial.print(M2encoderPos, DEC);
  Serial.print("|M3|");
  Serial.print(M3encoderPos, DEC);
  Serial.print("|M4|");
  Serial.println(M4encoderPos, DEC);
  */
  
  velocity3 = Pid.velocity(M3encoderPos,timeBetFrames);
  if (velocity3 < 0)
  {
    error = Pid.error(-35,velocity3);
    pid = Pid.PIDD(error,-35, timeBetFrames, Pid.kp,Pid.ki,Pid.kd);

  }
  else if (velocity3 > 0)
  {
    error = Pid.error(35,velocity3);
    pid = Pid.PIDD(error,35, timeBetFrames, Pid.kp,Pid.ki,Pid.kd);
  }
  motor.RunMotors(motor.M4,1, motor.E4,60+pid);
  
  Serial.print("|Vel|");
  Serial.print(VVelocity);
  Serial.print("\t|err|");
  Serial.print(error);
  Serial.print("\t|PID|");
  Serial.println(pid);
  
  timeBetFrames = millis() - timer;
  delay(50 - timeBetFrames); //Run at 100Hz
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
