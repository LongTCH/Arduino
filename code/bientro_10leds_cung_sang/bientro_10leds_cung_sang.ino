int pin = 0;
int led = 11;
int value = 0;
void setup()
{
}

void loop()
{
  value = analogRead(pin);
    value /= 4;
    analogWrite(led, value);
}
