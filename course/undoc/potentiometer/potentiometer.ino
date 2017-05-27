

void setup() 
{

  pinMode(13, OUTPUT);
  
}



void loop()
{
 int hamten = analogRead(0);
 
 digitalWrite(13,LOW);
 delay(hamten);
 digitalWrite(13,HIGH);
delay(hamten);
}

