

#include <IRremote.h>

const int RECV_PIN = 2;
const int BEEP_PIN = 4;
const int SEND_PIN = 3;



IRrecv irrecv(RECV_PIN);
IRsend irsend;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  
 pinMode(BEEP_PIN, OUTPUT);  
 
digitalWrite(BEEP_PIN,LOW);


 
}
const int LEN = 4;

const int CODES_NUM=17;
unsigned long CODES[CODES_NUM] =
{  16750695,16753245,16736925,16769565,16720605,16712445,16761405,16769055,16754775,16748655,16738455,16756815,16718055,16734885,16730805,16716015,16726215};

unsigned char VALUES[CODES_NUM] = {0,1,2,3,4,5,6,7,8,9,'*','#','u','r','d','l','o'};

//char all[9999] ={0};
char all[9] ={0};

int lastSent[LEN] = {0,0,0,0};
int current = 0;
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
    //Serial.println(results.value);
    for (int i=0;i<CODES_NUM;++i)
    {
        if (results.value == CODES[i])
        {        
          Serial.print( (int)VALUES[i]);
 
        return true;
        }
   }


  return false;
}
int join(int a,int b,int c,int d)
{
  return a*1000+b*100+c*10+d;
}
void split(int num, int* a)
{
  a[0]=num/1000;
  num-=1000*(a[0]);
  a[1]=num/100;
  num-=100*(a[1]);
  a[2]=num/10;
  num-=10*(a[2]);
  a[3]=num;
}
void send4(int num)
{
  int a[4];
 split(num,a);
 for (int i=0;i<LEN;++i)
 {
  send1(a[i]);
 }

 
}

bool check(int num)
{
  int lastSent[LEN]={0};
  int currnet = 0;
  for (int i=0;i<num;++i)
  {
      int a[4];
      split(num,a);
      for (int j=0;j<LEN;++j)
      {
         lastSent[currnet] = a[j];
         if (num==join( lastSent[currnet], lastSent[(currnet-1)%LEN], lastSent[(currnet-2)%LEN], lastSent[(currnet-3)%LEN]))
         {
          return false;
         }

      }
  }
  return true;
}
void send1(int num)
{
  lastSent[current] = num;

  int mult(1);
  int total = 0;
  for (int i=0;i<LEN;++i,mult*=10)
  {
    total+=mult*lastSent[(current-i)%LEN];
  }
  //all[total] = 1;
  current++;
  current= current%LEN;
  irsend.sendNEC(CODES[num],  32) ;
  delay(170);
  Serial.print(num);
}
void loop()
{
  int x=32; int y = 80;
  for (int i=0;i<9999;++i)
  {
   //  irsend.sendNEC(CODES[1],  x) ; delay(y);
    //  irsend.sendNEC(CODES[0],  x) ; delay(y);
     //  irsend.sendNEC(CODES[1],  x) ; delay(y);
      //  irsend.sendNEC(CODES[0],  x) ; delay(y);
   if (check(i))
    {
      send4(i);
    }
  }

}
