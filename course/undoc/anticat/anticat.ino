
#include <Servo.h>
Servo testservo;

#define servoPin 9
#define trigPin 7
#define echoPin 8
#define beep 2
#define green 3 
#define red 4 

void setup()
{
   Serial.begin(9600);
  Serial.println("Ready!");  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(beep, OUTPUT);
   pinMode(green, OUTPUT);
    pinMode(red, OUTPUT);
  digitalWrite(beep, LOW);
   digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
   testservo.attach(servoPin);
    testservo.write(0); 
  
}

int near(0);

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
   Serial.println(distance);  
  if (distance >= 10 && distance <= 70 )
  {
    near++;
  }
  else
  {
    near=0;
  }
  if (near >1)
  {
       digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    digitalWrite(beep, HIGH);
    for (int i=0;i<2;++i)
    {
    Serial.println("Shpritz!!!");  
    near = 0;
   
   testservo.write(90);
    delay(700);
   testservo.write(0);
       delay(700);
    }
     digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
      digitalWrite(beep, LOW);
  }
 
  
}
