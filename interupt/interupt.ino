#define LED 13
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  attachInterrupt(0,displayMicros,FALLING);//RISING khi nhấn nút, tức là ngắt khi nhấn nút
  attachInterrupt(1,displayMillis,FALLING);
}

void loop()
{
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);

}
void displayMicros()
{
  Serial.write("Micros()=");
  Serial.println(micros());
}
void displayMillis()
{
  Serial.write("Millis()=");
  Serial.println(millis());
}
