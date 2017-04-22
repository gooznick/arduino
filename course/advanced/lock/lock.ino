
#include <IRremote.h>
#include <Servo.h>

const int RECV_PIN = 2;
const int BEEP_PIN = 3;
const int BUTTON_PIN = 5;

const int SERVO_PIN = 4;

int CLOSE(0);
int OPEN(90);
IRrecv irrecv(RECV_PIN);
Servo servo;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  
 pinMode(BEEP_PIN, OUTPUT);  
  pinMode(BUTTON_PIN, INPUT_PULLUP);  
digitalWrite(BEEP_PIN,LOW);

  setLock(true);
   Serial.println( "begin ");
}

void setLock(bool lock)
{
  servo.attach(SERVO_PIN);
  servo.write(lock?CLOSE:OPEN); 
  delay(1000); 
  servo.detach();
}

const int CODES_NUM=10;
unsigned long CODES[CODES_NUM][2] =
{
  {16753245,1},   {16736925,2},    {16769565,3},     {16720605,4},
      {16712445,5},       {16761405,6},        {16769055,7},  {16754775,8},  {16748655,9}, {16750695,0}
      };
      const int LEN =4;
 char mem[LEN] = {0};
char current = 0;
char code[LEN] = {0,0,6,4};
char lock_code[LEN] = {1,0,1,0};
char code_perm[LEN] = {0,0,0,0};

bool checkCode(char* who)
{
  for (int i=0;i<LEN;++i)
  {
    if (mem[(current+i)%LEN] != who[i])
    {
      return false;
    }
  }
  clearMem();
  return true;
}
void beep()
{
   digitalWrite(BEEP_PIN,HIGH);
   delay(10);
   digitalWrite(BEEP_PIN,LOW);
    delay(30);
}
bool storeCode()
{
  decode_results results;
   if (!irrecv.decode(&results))
   {
    return false;
   }
   beep();
  irrecv.resume(); // resume receiver

    if (results.decode_type != NEC || results.value == REPEAT)
    {  
        return false;
    }

    for (int i=0;i<CODES_NUM;++i)
    {
        if (results.value == CODES[i][0])
        {
          Serial.print( (int)current);
         // Serial.print( " : ");
         // Serial.println( (int)CODES[i][1]);
          mem[current] = CODES[i][1];
          current++;
          current=current%LEN;
        return true;
        }
   }


  return false;
}

void clearMem()
{
  for (int i=0;i<LEN;++i)
    mem[i] = -9;
}
void printCode()
{Serial.print( "Code: ");
    for (int i=0;i<LEN;++i)
  {
    Serial.print(  (int)code[i]);
   Serial.print( " ");
  }
  Serial.println();
}
void saveMode()
{
   Serial.println( "save mode ");
    setLock(false);
        for (int i=0;i<5;++i)
        beep();
printCode();
  for (int i=0;i<LEN;)
  {
    if (storeCode())
    {
     
     code[i]= mem[(current+LEN-1) % LEN];
      mem[(current+LEN-1) % LEN]=-1;
       ++i;
    }
  }
        for (int i=0;i<5;++i)
        beep();
        printCode();
 clearMem();
  
}
void loop()
{
  servo.detach();
    if ( storeCode() )
    {
      if (checkCode(code)) 
      {
         setLock(false);
        Serial.println( "OPEN");     
      }
      if (checkCode(code_perm)) 
      {
         setLock(false);
        Serial.println( "OPEN perm");     
      }     
      if (checkCode(lock_code)) 
      {
         setLock(true);
        Serial.println( "LOCK");     
      }
    }
    if (!digitalRead(BUTTON_PIN))
    {

      // save mode
      saveMode();
    }
    
    

}
