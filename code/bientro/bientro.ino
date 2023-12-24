int led = 11;
int pin = 5;
int value = 0;

void setup(){
  pinMode(11, OUTPUT);
}

void loop(){
  value = analogRead(pin);
    value /= 4;
    analogWrite(led, value);
}
