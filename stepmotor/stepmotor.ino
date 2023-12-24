//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2048;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

int degreeToSteps(int degree, int STEPS = stepsPerRevolution) {
  if (degree == 0) return 0;
  return STEPS / (360 / degree);
}

void setup() {
    // Nothing to do (Stepper Library sets pins as outputs)
    // Rotate CW slowly at 15 RPM
    myStepper.setSpeed(15);
}

void loop() {
    
    // myStepper.setSpeed(15);
    myStepper.step(degreeToSteps(-45));
    delay(1000);
    
    // // Rotate CCW quickly at 10 RPM
    // myStepper.setSpeed(10);
    // myStepper.step(-stepsPerRevolution);
    // delay(1000);
}