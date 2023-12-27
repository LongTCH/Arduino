#include <SoftwareSerial.h>
// #include <Arduino_FreeRTOS.h>
SoftwareSerial BTSerial(10, 11);
// int line = 4;
// int value = 0;
// const int triPin = 5;
// const int echoPin = 3;
#define IN1 3
#define IN2 5
void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  BTSerial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  // xTaskCreate(dc, "dc", 512, NULL, 1, NULL);
  // pinMode(line, INPUT);
  // pinMode(triPin, OUTPUT);
  // pinMode(echoPin, INPUT);
  // BTSerial.begin(38400);
}
String prev = "", c = "";
void dc() {
  while (true) {
    if (c == "0" && prev != c) {
      digitalWrite(IN2, 0);
      for (int i = 200; i <= 255; i += 20) {
        analogWrite(IN1, i);
        delay(500);
      }
    } else if (c == "1" && prev != c) {
      digitalWrite(IN1, 0);
      for (int i = 200; i <= 255; i += 20) {
        analogWrite(IN2, i);
        delay(500);
      }
    }
    prev = c;
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  if (BTSerial.available()) {
    // Serial.write(BTSerial.read());
    c = BTSerial.readStringUntil('\n');
    Serial.println(c + prev);}
  //   if (c.toInt() == 1) {
  //     digitalWrite(IN2, 0);
  //     digitalWrite(IN1, 1);
  //     // for (int i = 200; i <= 255; i += 20) {
  //     //   analogWrite(IN1, i);
  //     //   delay(500);
  //     // }
  //   } else if (c.toInt() == 0) {
  //     digitalWrite(IN1, 0);
  //     digitalWrite(IN2, 1);
  //     // for (int i = 100; i <= 255; i += 10) {
  //     //   analogWrite(IN2, i);
  //     //   delay(1000);
  //     // }
  //   }
  //   prev = c;
  //   delay(5);
  // }
  // if (c.toInt() == 1) {
  // Nhanh dan
  // digitalWrite(IN2, 0);
  // // digitalWrite(IN1, 1);
  // for (int i = 0; i <= 255; i -= 10) {
  //   analogWrite(IN1, i);
  //   delay(500);
  // }
  // delay(2000);
  // // Cham dan
  // for (int i = 255; i >= 0; i -= 10) {
  //   analogWrite(IN1, i);
  //   delay(500);
  // }
  // delay(2000);
  // digitalWrite(IN1, 0);
  // delay(2000);
  // digitalWrite(IN1, 0);
  // // digitalWrite(IN1, 1);
  // for (int i = 100; i <= 255; i += 10) {
  //   analogWrite(IN2, i);
  //   delay(500);
  // }
  // delay(2000);
  // digitalWrite(IN2, 0);
  // delay(2000);
  //   } else if (c.toInt() == 0) {
  //     digitalWrite(IN1, 0);
  //     // digitalWrite(IN2, 1);
  //     for (int i = 100; i <= 255; i += 10) {
  //       analogWrite(IN2, i);
  //       delay(1000);
  //     }
  //   }
  // }
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
  // delay(500);
}
