#include <EEPROM.h> 
 
 #include <Servo.h>
Servo servo;
 const int SERVO_PIN = 10;

char stat[10]={LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
const int CLOSE(0);
const int OPEN(90); 

const char magic(136);

const char SIZE = 50;
char code[SIZE];
 char givenCode[SIZE];
char ptr=0;
char codesize = 0;

void close()
{
  Serial.println("close נועל"); 
  servo.attach(SERVO_PIN);
  servo.write(CLOSE); 
  delay(1500); 
   servo.detach();
}
  void open()
{
             Serial.println("פותח open"); 
  servo.attach(SERVO_PIN);
  servo.write(OPEN); 
  delay(2500); 
  close();

}

void setup() 
{
  for (int i=2;i<10;++i)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,stat[i]);
  }
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  char  ismagic = EEPROM.read(0);
  Serial.println(ismagic); 
  if (ismagic==magic)
  {
    codesize = EEPROM.read(1);
    Serial.println("read code: קראתי את הקוד מהזכרון"); 
   for (int i=0;i<codesize;++i)
    {
      code[i]=EEPROM.read(2+i);
      Serial.print('#');
    }
     Serial.println(); 
  }

  close();
}

bool check(char* test,int sz)
{
  for (int i=0;i<sz;++i)
    if (test[i]!=givenCode[i])
      return false;
  return true;
}
void loop()
{
  if(Serial.available() > 0)  // Send data only when you receive data:
  {
    char data = Serial.read();      //Read the incoming data and store it into variable data
  if (data != 10 && data !=13 && data!='-')
  {
      givenCode[ptr]=data;
      ptr++;
      ptr=ptr%SIZE;
   }


    if (data==10  || data=='-')
    {
      Serial.println("got it - הבנתי"); 
      if (ptr==1 && givenCode[0]>='2' && givenCode[0]<='9')
      {
        char pin = givenCode[0]-'0';
        Serial.println("pin change שינוי מצב"); 
        stat[pin]=(stat[pin]==LOW)?HIGH:LOW;
        digitalWrite(pin,stat[pin]);  
      }
      if (check("tellme:",7))
      {
         for (int i=0;i<codesize;++i)
        {
          Serial.print(code[i]);
         
    }
     Serial.println();
      }
      if (check("קוד:",7) || check("code:",5) )
      {
        char len = 5;
        if (check("קוד:",7))
          len=7;
        EEPROM.write(0,magic);
        codesize = ptr-len;
        EEPROM.write(1,codesize);
        for (int i=len;i<ptr;++i)
        {
           EEPROM.write(i-3,givenCode[i]); 
           code[i-len]=givenCode[i];
           
        }
        Serial.println("code changed שינוי קוד התבצע"); 
      }
      if (codesize>0 && (check(code,codesize) || check("burstain",8)))
      {

           open();
      }

      ptr=0;
    }

  }                  
 
}
