int led = 13, pin = 7, value = 0;
void setup()
{
  pinMode(led, OUTPUT);  
  pinMode(pin, INPUT);
  digitalWrite(led, HIGH);
}

void loop()
{
  value = digitalRead(pin);
  digitalWrite(led, value);
}