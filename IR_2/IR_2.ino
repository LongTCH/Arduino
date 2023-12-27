#include <Arduino.h>
#include "DHT.h"
#include <IRremote.hpp>
#define IR_SEND_PIN 12

#define LINE_PIN 4
#define LIGHT_PIN 0
#define GAS_PIN 0
#define DHT_PIN 4

#define TRIGGER_PIN 4
#define ECHO_PIN 5

#define JOY_X 0
#define JOY_X 1
#define JOY_BUTTON 7

#define DHTPin 4
#define DHTType DHT11
DHT HT(DHTPin, DHTType);

void setup() {
  Serial.begin(9600);
  IrSender.begin(IR_SEND_PIN);
  // For line
  pinMode(LINE_PIN, INPUT);

  // For Joystick
  pinMode(JOY_BUTTON, INPUT);

  // For Sieuam
  pinMode(TRIGGER_PIN, INPUT);
  pinMode(ECHO_PIN, INPUT);
}

uint16_t address = 0x3A13;
int_fast8_t repeats = 0;

void loop() {
  int line = digitalRead(LINE_PIN);
  // int gas = analogRead(GAS_PIN);
  // int light = analogRead(LIGHT_PIN);

  Serial.println(line);

  // For Sieuam
  // digitalWrite(TRIGGER_PIN, LOW);
  // delayMicroseconds(2);
  // digitalWrite(TRIGGER_PIN, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(TRIGGER_PIN, LOW);
  // duration = pulseIn(ECHO_PIN, HIGH);
  // distance = duration * 0.034 / 2.0;
  // Serial.print("khoang cach = ");
  // Serial.print(distance);
  // Serial.print("cm\n");

  if (line == 0) {
    IrSender.sendNEC(address, 0x0, repeats);
  } else {
    IrSender.sendNEC(address, 0x1, repeats);
  }
  delay(200);
}