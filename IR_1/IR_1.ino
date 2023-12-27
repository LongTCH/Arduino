#include <Servo.h>
#include <Stepper.h>
#include <Arduino_FreeRTOS.h>
#include <IRremote.hpp>

const int servoPin = 9;

Servo servo;

const int IR_RECEIVE_PIN = 12;

#define SERVO_PIN 9

#define IN1 33
#define IN2 32
#define MAX_SPEED_DC 255
#define MIN_SPEED_DC 150

#define STEP_IN1 18
#define STEP_IN2 19
#define STEP_IN3 22
#define STEP_IN4 23
#define STEP_SPEED 12  //RPM

// Defines the number of steps per rotation
const int stepsPerRevolution = 2048;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, STEP_IN1, STEP_IN3, STEP_IN2, STEP_IN4);
int step_degree = 0;
int degreeToSteps(int degree, int STEPS = stepsPerRevolution) {
  if (degree == 0) return 0;
  return STEPS / (360 / degree);
}

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  // For servo
  servo.attach(SERVO_PIN);
  xTaskCreate(servoSpin, "servoSpin", 256, NULL, 1, NULL);

  // For Stepper
  // xTaskCreate(stepSpin, "stepSpin", 1024, NULL, 1, NULL);
  // myStepper.setSpeed(STEP_SPEED);
}

int degree = 90;
void servoSpin() {
  while (true) {
    servo.write(degree);
    vTaskDelay(500 / portTICK_PERIOD_MS);  // delay 1 second
    servo.write(0);
    vTaskDelay(500 / portTICK_PERIOD_MS);  // delay 1 second
  }
}

void stepSpin(void *args) {
  while (1) {
    myStepper.step(degreeToSteps(step_degree));
    delay(1000);
  }
}

void rotateDC(int HIGH_CHANNEL, int LOW_CHANNEL, int faster) {
  if (faster) {
    analogWrite(LOW_CHANNEL, LOW);
    for (int i = MIN_SPEED_DC; i <= MAX_SPEED_DC; i += 10) {
      analogWrite(HIGH_CHANNEL, i);
      delay(500);
    }
  } else {
    analogWrite(LOW_CHANNEL, LOW);
    for (int i = MAX_SPEED_DC; i >= MIN_SPEED_DC; i -= 10) {
      analogWrite(HIGH_CHANNEL, i);
      delay(500);
    }
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
      } else degree = 90;

      // For DC
      // rotateDC(IN1, IN2, 1);
      // rotateDC(IN2, IN1, 1);
    }
    IrReceiver.resume();
  }
}