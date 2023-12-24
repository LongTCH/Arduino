#include <Arduino.h>
#include <IRremote.hpp>
#define IR_SEND_PIN 19
#define line 21
void setup() {
  Serial.begin(9600);
  IrSender.begin(IR_SEND_PIN);
  pinMode(line, INPUT);
}

uint16_t address = 0x3A13;
uint8_t command = 0x1;
int_fast8_t repeats = 0;

void loop() {
  int value = digitalRead(line);
  Serial.println(value);
  if (value == 0) {
    IrSender.sendNEC(address, 0x0, repeats);
  } else {
    IrSender.sendNEC(address, 0x1, repeats);
  }
  delay(200);
}