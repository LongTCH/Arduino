// C++ code
//

const int ledCount = 10;

int ledPins[]={3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

void setup()
{
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
}

void loop()
{
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
      digitalWrite(ledPins[thisLed], HIGH);
    	delay(1000);
      digitalWrite(ledPins[thisLed], LOW);
    	delay(1000);
    }
}
