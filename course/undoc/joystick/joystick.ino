#include <Servo.h>

#define H 0
#define V 1
#define laser 5
#define sw 4

int counter(0);
int laserF = 5;

Servo srvH,srvV;
double angleH(90),angleV(90);
double zeroH,zeroV;
void setup()
{

  srvH.attach(2); srvV.attach(3);

  srvH.write(angleH); 
   srvV.write(angleV); 
  delay(1000);
  zeroH = analogRead(H);
  zeroV = analogRead(V);
  pinMode(laser, OUTPUT); 
  pinMode(sw, INPUT_PULLUP); 
  digitalWrite(laser,LOW);

}

int sign(double v)
{
  if (v<0) return -1;
  return 1;
}
double SetAngle(double current, int readVal,int zero)
{
  double thresh(25);
  double mov = (readVal-zero);
    if (abs(mov)<thresh) 
    mov=0;
   else
    mov=mov-sign(mov)*thresh;
  
  mov/=8050.0;

  
  current+=mov;
  if (current<0) current = 0;
  if (current>180) current = 180;
  return current;
}
 
void loop() 
{
  
  angleH=SetAngle(angleH,analogRead(H),zeroH);
  srvH.write(angleH); 
  angleV=SetAngle(angleV,analogRead(V),zeroV);
  srvV.write(angleV); 

  int swRead = digitalRead(sw);
  digitalWrite(laser,LOW);

    if (!swRead && (counter%laserF == 0))
    {
      digitalWrite(laser,HIGH);
    }
     
  ++counter;


}
