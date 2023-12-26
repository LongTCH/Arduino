#include "DHT.h"
#define DHTPin 4
#define DHTType DHT11
int ALARM = 13;
float sinVal;
int toneVal;

DHT HT(DHTPin, DHTType);
float humidity;
float temperatureC;
float temperatureF;

void setup(){
  Serial.begin(9600);
  HT.begin();
  pinMode(ALARM, OUTPUT);
  delay(1000);
}

void loop(){
  delay(2000);
  humidity = HT.readHumidity();
  temperatureC = HT.readTemperature();
  temperatureF = HT.readTemperature(true);
  Serial.print("Humidity : ");
  Serial.print(humidity);
  Serial.print(", Temperature : ");
  Serial.print(temperatureC);
  Serial.print("oC ~");
  Serial.print(temperatureF);
  Serial.println("oF");
  if (humidity > 85 && temperatureC > 33){

    for (int x = 0; x < 180; x++) {
      //Convert sin function to radian
      sinVal = (sin(x * (3.1412 / 180)));
      // Use sin function to generate frequency of sound
      toneVal = 2000 + (int(sinVal * 1000));
      // Configure the buzzer pin 4
      tone(ALARM, toneVal);
      delay(20);
    }
    noTone(ALARM);
  }


}
