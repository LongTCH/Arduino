// pin 16-33
#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"
#include <DHT.h>
#include <ESP32Servo.h>
#include <Stepper.h>



const char *ssid = "...";
const char *password = "00000000";

WebServer server(80);

// #define LED 15

#define DHT_PIN 14
#define DHT_TYPE DHT11

#define LINE_PIN 18
#define SERVO_PIN 19
#define LIGHT_PIN 13
#define GAS_PIN 14

#define IN1 33
#define IN2 32

#define TRIGGER 22
#define ECHO 23

#define JOY_X 22
#define JOY_Y 23
#define JOY_BUTTON 23

#define IN1_CHANNEL 0
#define IN2_CHANNEL 1
#define FREQUENCY 5000
#define RESOLUTION 8

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

// DHT dht(DHT_PIN, DHT_TYPE);

// Servo servo;
// int servo_angle = 0;

void setup() {
  Serial.begin(9600);
  // For DHT
  // dht.begin();

  // For SieuAm
  // pinMode(TRIGGER, OUTPUT);
  // pinMode(ECHO, INPUT);

  // For Joystick
  // pinMode(JOY_X, INPUT);
  // pinMode(JOY_Y, INPUT);
  // pinMode(JOY_BUTTON, INPUT);
  // analogReadResolution(10);

  // For DC
  // ledcSetup(IN1_CHANNEL, FREQUENCY, RESOLUTION);
  // ledcSetup(IN2_CHANNEL, FREQUENCY, RESOLUTION);
  // ledcAttachPin(IN1, IN1_CHANNEL);
  // ledcAttachPin(IN2, IN2_CHANNEL);

  // For Servo
  // servo.attach(SERVO_PIN);
  // xTaskCreate(servoSpin, "servoSpin", 1024, NULL, 1, NULL);

  // For StepMotor
  xTaskCreate(stepSpin, "stepSpin", 1024, NULL, 1, NULL);
  myStepper.setSpeed(STEP_SPEED);


  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // WiFi.softAP(ssid, password);
  // IPAddress IP = WiFi.softAPIP();

  // Serial.print("AP IP address: ");
  // Serial.println(IP);

  // Serial.print("Local IP address: ");
  // Serial.println(WiFi.localIP());

  WiFi.begin(ssid, password);
  Serial.println("Kết nối đến WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Đã kết nối thành công!");
  Serial.println("Server started");
  Serial.print("IP Address of network: ");  // will IP address on Serial Monitor
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: https://");
  Serial.print(WiFi.localIP());

  // Routes
  server.on("/", handle_index);
  // server.on("/led", handle_led);
  // server.on("/dht", handle_dht);
  // server.on("/servo", handle_servo);
  server.on("/stepmotor", handle_stepmotor);
  // server.on("/line", handle_line);
  // server.on("/dc", handle_dc);
  // server.on("/distance", handle_sieuam);
  // server.on("/joy", handle_joy);
  server.enableCORS();
  server.begin();
}

// void servoSpin(void *args) {
//   while (1) {
//     servo.write(servo_angle);
//     delay(1000);
//     servo.write(0);
//     delay(1000);
//   }
// }

void stepSpin(void *args) {
  while (1) {
    myStepper.step(degreeToSteps(step_degree));
    delay(1000);
  }
}

String get_html(const char *path) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial.println("Could not open file for reading");
    Serial.print("File: ");
    Serial.println(path);
    return "Sorry but no luck!";
  }
  String content = file.readString();
  return content;
}

void handle_index() {
  Serial.println("Request /");
  server.send(200, "text/html", get_html("/index.html"));
}

void handle_line() {
  int val = digitalRead(LINE_PIN);
  Serial.print("Line: ");
  Serial.println(val);
  server.send(200, "application/json", "{\"value\":" + String(val) + "}");
}

// void handle_dht() {
//   float temperature = dht.readTemperature();
//   float humidity = dht.readHumidity();
//   Serial.print("Temp: ");
//   Serial.println(temperature);
//   Serial.print("Humid: ");
//   Serial.println(humidity);
//   String response = "{\"temperature\": " + String(temperature) + ", \"humidity\":" + String(humidity) + "}";
//   server.send(200, "application/json", response);
// }

void handle_light() {
  int val = analogRead(LIGHT_PIN);
  Serial.print("Light: ");
  Serial.println(val);
  server.send(200, "application/json", "{\"value\":" + String(val) + "}");
}

void handle_gas() {
  int val = analogRead(GAS_PIN);
  Serial.print("Gas : ");
  Serial.println(val);
  server.send(200, "application/json", "{\"value\":" + String(val) + "}");
}

void handle_sieuam() {
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  float duration = pulseIn(ECHO, HIGH);
  float distance = duration * 0.034 / 2.0;
  Serial.print("khoang cach = ");
  Serial.print(distance);
  Serial.print("cm\n");
  server.send(200, "application/json", "{\"value\":" + String(distance) + "}");
}

void rotateDC(int HIGH_CHANNEL, int LOW_CHANNEL, int faster) {
  if (faster) {
    ledcWrite(LOW_CHANNEL, LOW);
    for (int i = 150; i <= 255; i += 5) {
      ledcWrite(HIGH_CHANNEL, i);
      delay(500);
    }
  } else {
    ledcWrite(LOW_CHANNEL, LOW);
    for (int i = 255; i >= 150; i -= 5) {
      ledcWrite(HIGH_CHANNEL, i);
      delay(500);
    }
  }
}
void handle_dc() {
  int direction = server.arg("direction").toInt();
  int faster = server.arg("faster").toInt();
  if (direction == 1) {
    rotateDC(IN1_CHANNEL, IN2_CHANNEL, faster);
  } else {
    rotateDC(IN2_CHANNEL, IN1_CHANNEL, faster);
  }
  server.send(200, "text/plain", "OK");
}

void handle_joy() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);
  int button = analogRead(JOY_BUTTON);
  Serial.println("x= " + x + ",y= " + y + ",button= " + button);
  server.send(200, "application/json", "{\"x\":" + String(x) + ",\"y\":" + String(y)++ ",\"button\":" + String(button) + "}");
}

// void handle_servo() {
//   int angle = server.arg("angle").toInt();
//   servo_angle = angle;
//   Serial.println(angle);
//   server.send(200, "application/json", "{\"message\": \"OK\"}");
// }

void handle_stepmotor() {
  int angle = server.arg("angle").toInt();
  int direction = server.arg("direction").toInt();
  if (direction == 1) step_degree = -angle;
  else step_degree = angle;
  Serial.println("direction: " + String(direction) + ", angle: " + String(angle));
  server.send(200, "application/json", "{\"message\": \"OK\"}");
}

void loop() {
  server.handleClient();
}