#define photo 0
#define laser 10
#define buzzer 8
#define led 4
#define leds 3

        #define speakerOut 8    
byte names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};  
int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
byte melody[] = "2d2a1f2c2d2a2d2c2f2d2a2c2d2a1f2c2d2a2a2g2p8p8p8p";
int count = 0;
int count2 = 0;
int count3 = 0;
int MAX_COUNT = 24;
int statePin = LOW;
void melodyPlay()
{
   analogWrite(speakerOut, 0);     
  for (count = 0; count < MAX_COUNT; count++) {
    statePin = !statePin;
  
    for (count3 = 0; count3 <= (melody[count*2] - 48) * 30; count3++) {
      for (count2=0;count2<8;count2++) {
        if (names[count2] == melody[count*2 + 1]) {       
          analogWrite(speakerOut,500);
          delayMicroseconds(tones[count2]);
          analogWrite(speakerOut, 0);
          delayMicroseconds(tones[count2]);
        } 
        if (melody[count*2 + 1] == 'p') {
          // make a pause of a certain size
          analogWrite(speakerOut, 0);
          delayMicroseconds(500);
        }
      }
    }
  } 
}
void setup()
{
  Serial.begin(9600);
  Serial.println("Ready!"); 
  pinMode(laser, OUTPUT); 
  pinMode(buzzer, OUTPUT); 
  for (int i=led;i<led+leds;++i)
  {
  pinMode(i, OUTPUT); 
   digitalWrite(i,LOW);
  }
  
  digitalWrite(laser,LOW);
  digitalWrite(buzzer,LOW);
 
}
const int waitReset = 300;
const int threshold = 950
;
int wait = waitReset;
int faults = 0;

void fault()
{
  for (int i=0;i<10;++i)
  {
  digitalWrite(buzzer,HIGH);
  delay(10);
  digitalWrite(buzzer,LOW);
   delay(100);
  }
}

void beep()
{
  digitalWrite(buzzer,HIGH);
   digitalWrite(laser,HIGH);
  delay(50);
  digitalWrite(buzzer,LOW);
   digitalWrite(laser,LOW);
}
void readAndDelay(int time)
{
  const int total = 20;
  for (int i=0;i<total;++i)
  {
    if ( analogRead(photo) >threshold )
    {
     
      digitalWrite(led+faults,HIGH);
      ++faults;
       if (faults==3)
       {
         eog();
       }
       fault();
       delay(1000);
    }

    delay(time/total);
  
  }
  
}
void eog()
{
   digitalWrite(laser,LOW);
  for (;;)
  {
    melodyPlay();
    analogWrite(buzzer,800);
    delay(10);
       analogWrite(buzzer,500);
    delay(20);
 
    digitalWrite(buzzer,LOW);
    delay(150);
  }
   
}
void loop() 
{
  beep();
  readAndDelay(wait);
  wait -= 15;
  if (wait<0)
  {
      digitalWrite(buzzer,HIGH);
      analogWrite(laser,800);
      readAndDelay(200);
       digitalWrite(buzzer,LOW);
      digitalWrite(laser,LOW);
      wait = waitReset;
  }
  
  int a = analogRead(0);
  Serial.print(a); 
  Serial.print(" "); 

}
