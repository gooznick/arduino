void setup()
{
   pinMode(9, OUTPUT);
   digitalWrite(9, LOW);
}

void  loop()
{
  int r = analogRead(0);
  analogWrite(9,r*4);
}

