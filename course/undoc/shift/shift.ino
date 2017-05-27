/*
  Shift Register Example
 for 74HC595 shift register

 This sketch turns reads serial input and uses it to set the pins
 of a 74HC595 shift register.

 Hardware:
 * 74HC595 shift register attached to pins 2, 3, and 4 of the Arduino,
 as detailed below.
 * LEDs attached to each of the outputs of the shift register

 Created 22 May 2009
 Created 23 Mar 2010
 by Tom Igoe

 */

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  
}
int hamten = 0; 

void loop()
{
//  registerWrite(255);
 
registerWrite(~1);
registerWrite(~9);
registerWrite(~13);
registerWrite(~15);
registerWrite(~47);
registerWrite(~111);
registerWrite(~239);
registerWrite(~239);
registerWrite(~111);
registerWrite(~47);
registerWrite(~15);
registerWrite(~13);
registerWrite(~9);
registerWrite(~1);
registerWrite(~1);


}

// This method sends bits to the shift register:

void registerWrite(int bitsToSend) {
  digitalWrite(latchPin, LOW);
   digitalWrite(clockPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);
  digitalWrite(latchPin, HIGH);
  hamten = analogRead(0);
   delay(hamten);
}
