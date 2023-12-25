// pin 16-33
#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"
#include <DHT.h>
#include <ESP32Servo.h>

const char* ssid = "ESP32 - ...";
const char* password = "12345678";

// IPAddress local_ip(192,168,1,1);
// IPAddress gateway(192,168,1,1);
// IPAddress subnet(255,255,255,0);
WebServer server(80);

#define LED 15

// #define DHT_PIN 2
// #define DHT_TYPE DHT11

#define LINE_PIN 18

#define SERVO_PIN 4
#define IN1 33
#define IN2 32

// DHT dht(DHT_PIN, DHT_TYPE);
// Servo servo;

int servo_angle = 0;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcAttachPin(IN1, 0);
  ledcAttachPin(IN2, 1);
  // ledcAttachPin(IN2, 0);
  // if(!SPIFFS.begin(true)){
  //   Serial.println("An Error has occurred while mounting SPIFFS");
  //   return;
  // }

  // WiFi.softAP(ssid, password);
  // IPAddress IP = WiFi.softAPIP();
  // WiFi.softAPConfig(local_ip, gateway, subnet);

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

  // Routes
  server.on("/", handle_index);
  server.on("/led", handle_led);
  // server.on("/dht", handle_dht);
  // server.on("/servo", handle_servo);
  server.on("/line", handle_line);
  server.on("/dc", handle_dc);
  pinMode(LED, OUTPUT);

  // servo.attach(SERVO_PIN);
  server.enableCORS();
  server.begin();

  // xTaskCreate(servoSpin, "servoSpin", 1024, NULL, 1, NULL);
}

// void servoSpin(void* args) {
//   while(1) {
//     servo.write(servo_angle);
//     delay(1000);
//     servo.write(0);
//     delay(1000);
//   }
// }

String get_html(const char* path) {
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

void handle_led() {
  if (server.hasArg("status")) {
    String status = server.arg("status");
    if (status == "on") {
      digitalWrite(LED, HIGH);
    } else if (status == "off") {
      digitalWrite(LED, LOW);
    }
    server.send(200, "application/json", "{\"message\": \"OK\"}");
  } else {
    server.send(400, "application/json", "{\"error\": \"Missing argument: status\"}");
  }
}

void handle_line() {
  int val = digitalRead(LINE_PIN);
  server.send(200, "text/plain", String(val));
}
// void handle_dht() {
//   float temperature = dht.readTemperature();
//   float humidity = dht.readHumidity();
//   Serial.print("Temp: ");
//   Serial.println(temperature);
//   Serial.print("Humid: ");
//   Serial.println(humidity);

//   if(isnan(temperature) || isnan(humidity)) {
//     server.send(500, "application/json", "{\"error\": \"Error occured when reading DHT\"}");
//   } else {
//     String response = "{\"temperature\": " + String(std::to_string(temperature).c_str()) + ", \"humidity\":" + String(std::to_string(humidity).c_str()) + "}";
//     server.send(200, "application/json", response);
//   }
//   // TO-DO
// }

void handle_dc() {
  if (server.hasArg("direction")) {
    int direction = server.arg("direction").toInt();
    if (direction == 1) {
      ledcWrite(0, LOW);
      for (int i = 0; i <= 255; i++) {
        ledcWrite(1, i);
        delay(10);
      }
    } else {
      for (int i = 0; i <= 255; i++) {
        ledcWrite(1, i);
        delay(10);
      }
      ledcWrite(1, LOW);
    }
    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "ERROR");
  }
}

// void handle_servo() {
//   if(server.hasArg("angle")) {
//     int angle = server.arg("angle").toInt();
//     servo_angle = angle;
//     servo.write(angle);
//     Serial.println(angle);
//     server.send(200, "application/json", "{\"message\": \"OK\"}");
//   } else {
//     server.send(400, "application/json", "{\"error\": \"Missing argument: angle\"}");
//   }
// }

void loop() {
  server.handleClient();
}