#include <Servo.h>
#include <Arduino_FreeRTOS.h>
#include <IRremote.hpp>
const int servoPin = 9;

Servo servo_9;

const int IR_RECEIVE_PIN = 2;


void setup() {
  Serial.begin(19200);
  IrReceiver.begin(IR_RECEIVE_PIN);
  servo_9.attach(9);
  xTaskCreate(servoSpin, "servoSpin", 256, NULL, 1, NULL);
}

int degree = 90;
void servoSpin() {
  while (true) {
    servo_9.write(degree);
    vTaskDelay(500 / portTICK_PERIOD_MS);  // delay 1 second
    servo_9.write(0);
    vTaskDelay(500 / portTICK_PERIOD_MS);  // delay 1 second
  }
}


void loop() {
  if (IrReceiver.decode()) {
    uint16_t address = IrReceiver.decodedIRData.address;
    // Serial.print("address: ");
    Serial.println(address);
    if (address == 0x3A13) {
      uint8_t command = IrReceiver.decodedIRData.command;
      Serial.print("command: ");
      Serial.println(command);
      if (command == 0x0) {
        degree = 180;
      }
      else degree  = 90;
    }
    IrReceiver.resume();
  }
  
}