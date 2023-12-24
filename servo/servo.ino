#include <Servo.h>
#include <Arduino_FreeRTOS.h>
Servo servo_9;
int distance;

int degree = 90;
int line = 0;

void servoSpin() {
  while (true) {
    servo_9.write(degree);
    vTaskDelay(500 / portTICK_PERIOD_MS);  // delay 1 second
    servo_9.write(0);
    vTaskDelay(500 / portTICK_PERIOD_MS);  // delay 1 second
  }
}

void setup() {
  servo_9.attach(9);
  pinMode(line, INPUT);
  Serial.begin(9600);
  xTaskCreate(servoSpin, "servoSpin", 512, NULL, 1, NULL);
}

void loop() {
  int val = analogRead(line);
  if (val > 200) {
    degree = 45;
  } else degree = 90;
  Serial.println(val);
}