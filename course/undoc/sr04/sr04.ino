#include <LiquidCrystal.h> 
LiquidCrystal lcd(12, 11, 5, 4, 3, 6); 
/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#define trigPin 7
#define echoPin 8
#define beep 2


void setup()
{
  lcd.begin(16, 2); 
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(beep, OUTPUT);
  digitalWrite(beep, LOW);
   lcd.print("Distance:"); 
}

void loop() {
  int distance;

  lcd.setCursor(0, 1);
  if (distance >= 250 || distance <= 0)
  {
    lcd.print("Out of range");
   delay(70);
  }
  else 
  {
    digitalWrite(beep, HIGH);
    delay(50);
     digitalWrite(beep, LOW);
     
    lcd.print(distance); 
     lcd.print(" cm           "); 
     if (distance>0 && distance<20) delay(50);
 if (distance>20 && distance<40) delay(100);
   if (distance>40 && distance<60) delay(150);
   if (distance>60 && distance<80) delay(200);
   if (distance>80 && distance<100) delay(250);
   if (distance>100 ) delay(350);
   
  }
  
}
