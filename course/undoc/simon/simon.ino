                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   


int tones[] = { 3830,  3400, 3038,  2864 };

int speakerOut = 6;
void playTone(int num)
{
	int tone_ = tones[num];
	int beat = 16;
	long tempo = 10000;
	int duration = beat * tempo; // Set up timing

	long elapsed_time = 0;
	if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
					 //  played less long than 'duration', pulse speaker HIGH and LOW
		while (elapsed_time < duration) {

			digitalWrite(speakerOut, HIGH);			delayMicroseconds(tone_ / 2);

			// DOWN
			digitalWrite(speakerOut, LOW);
			delayMicroseconds(tone_ / 2);

			// Keep track of how long we pulsed
			elapsed_time += (tone_);
		}
	}

}

// SETUP ============================================
// Set up speaker on a PWM pin (digital 9, 10 or 11)

int stage;
 static const int STAGES = 50;
 int lights[STAGES];
 int in(8);
 int out(2);

void setup()
{
	
	randomSeed(analogRead(0));
	Serial.begin(9600);
	Serial.flush();
	for (int i = 0; i < STAGES;++i)
		lights[i] = random(4);
	for (int i = out; i <= out+4; ++i) 	pinMode(i, OUTPUT);
	for (int i = in; i <= in+4; ++i) 	pinMode(i, INPUT);
	pinMode(13, OUTPUT);
	pinMode(6, OUTPUT);

	stage = 0;
}
void lost()
{
	analogWrite(6, 200);
	delay(500);
	digitalWrite(6, LOW);

	while (1)
	{

		for (int i = 0; i <  4; ++i)
		{
			light(i);
		}
	}
}
void light(int num) // 0 or 1
{
	digitalWrite(13, HIGH);

	playTone(num);


	//delay(100);
	digitalWrite(out+num, HIGH);
	digitalWrite(13, LOW);
	analogWrite(6, 0);
	delay(100);
	digitalWrite(out +num, LOW);

	delay(80);
}
void play()
{
	for (int i = 0; i < stage + 1; ++i)
	{
		light(lights[i]);
	}
}

int singlePush()
{
	int pushed = 0;
	while (!pushed)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (digitalRead(i+in))
			{
				Serial.print(i);
				light(i);
	
				return i;
			}
		}

	}
	return 0;

}
void quiz()
{
	for (int i = 0; i < stage + 1;++i)
	{
		int res = singlePush();
		if (res != lights[i])
			lost();
	}
	delay(300);
}
void loop()
{
	play();
	quiz();
	stage++;


}
