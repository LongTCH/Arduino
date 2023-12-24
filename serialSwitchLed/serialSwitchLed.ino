int pin = 13;
String setupLed = ""; 
void setup() 
{
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
}
void loop() 
{
  if (Serial.available() > 0) 
  {
    setupLed = Serial.readString(); 
    setupLed.trim();
  } 

  if (setupLed == "ON")
  {digitalWrite(pin, HIGH);
    } else if (setupLed == "OFF"){
      digitalWrite(pin, LOW);
    }
  }

