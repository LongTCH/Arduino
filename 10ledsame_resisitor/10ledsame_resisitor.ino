// C++ code
//
int pin = 0, value = 0, led = 13;
void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{
  value = analogRead(pin);
  digitalWrite(13,HIGH);
  delay(2*value);
  digitalWrite(13,LOW);
  delay(2*value);
  
}