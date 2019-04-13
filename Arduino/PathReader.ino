/*
  Reading a serial ASCII-encoded string.

 This sketch demonstrates the Serial parseInt() function.
 It looks for an ASCII string of comma-separated values.
 It parses them into ints, and uses those to fade an RGB LED.

 Circuit: Common-Cathode RGB LED wired like so:
 * Red anode: digital pin 3
 * Green anode: digital pin 5
 * Blue anode: digital pin 6
 * Cathode : GND

 created 13 Apr 2012
 by Tom Igoe
 
 modified 14 Mar 2016
 by Arturo Guadalupi

 This example code is in the public domain.
 */

void setup() 
{
  // initialize serial:
  Serial.begin(9600);

}

char serialInput;
int numPoints = 0;
int Path[50] = {0};
int char2int[50] = {0};
void loop() 
{
  while(Serial.available() > 0)
  {
     serialInput = Serial.read();
     if(serialInput == 'P')
     {
      char2int[numPoints] =  Serial.parseInt();
      Path[numPoints] = char2int[numPoints];
      numPoints++;
     
      if (serialInput == '\n') 
      {
        for(int x = 0;x < numPoints; x++)
        {
          Serial.println(Path[x]); 
        }
        *char2int = 0;
        *Path = {0};
        numPoints = 0;
      }
    }
  }
}








