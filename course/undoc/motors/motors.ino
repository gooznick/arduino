.    int enable1Pin = 11;
int in1Pin = 10;
int in2Pin = 9;

int enable2Pin = 6;
int in3Pin = 5;
int in4Pin = 4;

int buttonPin = 2;


void setup()
{
pinMode(in1Pin, OUTPUT);
pinMode(in2Pin, OUTPUT);
pinMode(enable1Pin, OUTPUT);
pinMode(in3Pin, OUTPUT);
pinMode(in4Pin, OUTPUT);
pinMode(enable2Pin, OUTPUT);

pinMode(buttonPin, INPUT_PULLUP);

digitalWrite(enable1Pin, HIGH);
digitalWrite(enable2Pin, HIGH);
}

void setMotors( int in1, int in2, int in3,int in4)
  {
    digitalWrite(in1Pin, in1);
    digitalWrite(in2Pin, in2);
     digitalWrite(in3Pin, in3);
    digitalWrite(in4Pin, in4);
  }

void forward(){ setMotors(HIGH,LOW,HIGH,LOW);}
void backward(){ setMotors(LOW,HIGH,LOW,HIGH);}
void left(){ setMotors(HIGH,LOW,LOW,HIGH);}
void right(){ setMotors(LOW,HIGH,HIGH,LOW);}
void stopMotors(){ setMotors(LOW,LOW,LOW,LOW);}

int button = 0;
void loop()
{



   if (digitalRead(buttonPin) == LOW)
   {
    button= (button+1)%5;
   }
   switch (button)
   {
    case 0:stopMotors(); break;
    case 1:forward(); break;
    case 2:backward(); break;
    case 3:left(); break;
    case 4:right(); break;
   }
    delay(200);
 

}
