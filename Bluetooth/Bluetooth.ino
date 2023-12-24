#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11);
// int line = 4;
// int value = 0;
// const int triPin = 5;
// const int echoPin = 3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // BTSerial.begin(9600);
  // pinMode(line, INPUT);
  // pinMode(triPin, OUTPUT);
  // pinMode(echoPin, INPUT);
  BTSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BTSerial.available()){
    // Serial.write(BTSerial.read());
    String c = BTSerial.readString();
    Serial.println(c);
    delay(5);
  }
  
  if (Serial.available()){
    // BTSerial.write(Serial.read());
    char c = Serial.read();
    BTSerial.write(c);
    delay(5);
  }
  // digitalWrite(triPin, LOW);
  // delayMicroseconds(2);
  // digitalWrite(triPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(triPin, LOW);
  // long duration = pulseIn(echoPin, HIGH);
  // float distance = duration*0.034/2.0;
  // BTSerial.write(distance > 20 ? '1' : '0');
  // delay(500);
}


