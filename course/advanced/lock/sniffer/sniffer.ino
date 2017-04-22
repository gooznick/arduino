
#include <IRremote.h>

#include <SevenSegment.h>

const int RECV_PIN = 2;
const int BEEP_PIN = 3;

SevenSegment sevenSegment (10,9,8,7,6,5,4);

IRrecv irrecv(RECV_PIN);


void setup()
{
  Serial.begin(9600);
   Serial.print("listening");
  irrecv.enableIRIn(); // Start the receiver
  
 pinMode(BEEP_PIN, OUTPUT);  
 
digitalWrite(BEEP_PIN,LOW);

sevenSegment.print();
 
}


const int CODES_NUM=17;
unsigned long CODES[CODES_NUM] =
{  16753245,16736925,16769565,16720605,16712445,16761405,16769055,16754775,16748655,16750695,16738455,16756815,16718055,16734885,16730805,16716015,16726215};

unsigned char VALUES[CODES_NUM] = {1,2,3,4,5,6,7,8,9,0,'*','#','u','r','d','l','o'};



void beep()
{
   digitalWrite(BEEP_PIN,HIGH);
   delay(10);
   digitalWrite(BEEP_PIN,LOW);
    delay(30);
}
int storeCode()
{
  decode_results results;
   if (!irrecv.decode(&results))
   {
    return -1;
   }
   beep();
  irrecv.resume(); // resume receiver

    if (results.decode_type != NEC || results.value == REPEAT)
    {  
        return -1;
    }
    
    for (int i=0;i<CODES_NUM;++i)
    {
        if (results.value == CODES[i])
        {        
          char val=VALUES[i];
          if (val<10)
              Serial.print( (int)val);
            else
              Serial.print( val);
          return val;
        }
   }


  return -1;
}

void loop()
{

    int value = storeCode();
    if (value!=-1)
    {
    sevenSegment.print(value );    
    }

    
    

}
