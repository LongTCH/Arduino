#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11);
// int line = 4;
// int value = 0;
// const int triPin = 5;
// const int echoPin = 3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(7, INPUT);
  // pinMode(line, INPUT);
  // pinMode(triPin, OUTPUT);
  // pinMode(echoPin, INPUT);
  // BTSerial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t val = digitalRead(7);
  Serial.println(val);
  // if (BTSerial.available()){
  //   // Serial.write(BTSerial.read());
  //   String c = BTSerial.readString();
  //   Serial.println(c);
  //   delay(5);
  // }
  
  BTSerial.println(val);
  
  // if (Serial.available()){
  //   // BTSerial.write(Serial.read());
  //   char c = Serial.read();
  //   BTSerial.write(c);
  //   delay(5);
  // }
  // digitalWrite(triPin, LOW);
  // delayMicroseconds(2);
  // digitalWrite(triPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(triPin, LOW);
  // long duration = pulseIn(echoPin, HIGH);
  // float distance = duration*0.034/2.0;
  // BTSerial.write(distance > 20 ? '1' : '0');
  delay(500);
}


