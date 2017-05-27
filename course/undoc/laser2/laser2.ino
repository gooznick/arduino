#define photo 0
#define laser 10
#define buzzer 8
#define button 2
#define led 4
#define leds 3
#define serv 12
int const potPin = A1; // analog pin used to connect the potentiometer

#include <Servo.h>

Servo myServo;  // create a servo object

int former;
 int total = 0;

int faults = 0;
const int pointVal = 200;
const int threshold = 800;
const int loadMillis = 2500;

const int wait(300);
const int fire(900);
 long lastfire(0); 
void setup()
{
  Serial.begin(9600);
  Serial.println("Ready!"); 
  pinMode(button, INPUT_PULLUP); 
  pinMode(laser, OUTPUT); 
  pinMode(buzzer, OUTPUT); 
  for (int i=led;i<led+leds;++i)
  {
  pinMode(i, OUTPUT); 
   digitalWrite(i,LOW);
  }
  myServo.attach(serv);
  digitalWrite(laser,LOW);
  digitalWrite(buzzer,LOW);
 lastfire=millis()-loadMillis;
}

 
void fault()
{
  for (int i=0;i<20;++i)
  {
  digitalWrite(buzzer,HIGH);
  delay(10);
  digitalWrite(buzzer,LOW);
   delay(10);
  }
}


void readVal()
{

 
   int val = analogRead(photo);
    if ( val>former && val>threshold  )
    {
     total+=former-val;
     if (total>pointVal)
     {
            digitalWrite(led+faults,HIGH);
      ++faults;
       if (faults==3)
       {
         eog();
       }
       fault();
       total=0;
     }
    }
    former=val;
  
}
void eog()
{
   digitalWrite(laser,LOW);
  for (;;)
  {
      delay(300);
    for (int i=led;i<led+leds;++i)
  {
   digitalWrite(i,HIGH);

  }
    delay(300);
      for (int i=led;i<led+leds;++i)
  {
   

   digitalWrite(i,LOW);
 
  }
    digitalWrite(buzzer,HIGH);
    delay(10);
     digitalWrite(buzzer,LOW);
  }   
}

void loop() 
{
 int j(0);
 int load(1);
  for (;;)
  {

    int potVal = analogRead(potPin);
    
    int  angle = map(potVal, 0, 1023, 0, 179);
   myServo.write(angle);    
    int now =millis();;
   if( !load && now-lastfire>loadMillis)
   {
       digitalWrite(buzzer,HIGH);
    delay(10);
     digitalWrite(buzzer,LOW);
     load=1;
   }
  if ( !digitalRead(button) && load)
  {
    load=0;
    lastfire=now;
    for (int i=0;i<fire/40;++i)
    {
        readVal();
     digitalWrite(laser,HIGH);
   
     delayMicroseconds(400);
     digitalWrite(laser,LOW);
     readVal();
     delay(20);
    }
  }

   ++j;
  if (j%1000 == 0)
  {
      Serial.print(former); 
       Serial.print(" - "); 
        Serial.println(total); 
          readVal();
    digitalWrite(laser,HIGH);
   
     delayMicroseconds(10);
     digitalWrite(laser,LOW);
  }
     
  readVal();
  }

 

}
