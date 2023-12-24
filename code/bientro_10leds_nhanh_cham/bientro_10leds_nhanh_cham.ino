int pin = 5;
int leds = 10;
int pin_leds[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4};
int value = 0;

void setup(){
  for (int i = 0; i < leds; i++){
    pinMode(pin_leds[i], OUTPUT);
  }
}

void loop(){
  for (int i = 0; i < leds; i++){
    value = analogRead(pin);
    value = value/2 + 100;
    digitalWrite(pin_leds[i], HIGH);
    delay(value);
    digitalWrite(pin_leds[i], LOW);
    delay(value);
  }
}
