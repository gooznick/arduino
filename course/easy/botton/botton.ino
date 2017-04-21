

void setup()
{
	
	Serial.begin(9600);
	
	pinMode(2, INPUT);
	pinMode(8, OUTPUT);
Serial.write("hello");       

}

void loop()
{
	  if (digitalRead(2))
   { 
     Serial.write("2\npushed\n");
     Serial.flush();
     for (int i=0;i<10;++i)
     {
     digitalWrite(8,HIGH);
     delay(30);
      digitalWrite(8,LOW);
       delay(10);
     }
    
   }

}
