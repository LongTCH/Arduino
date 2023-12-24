const int triPin = 5;
const int echoPin = 3;
const int pinLed = 13;
int ALARM = 4; 
// float sinVal = 4;
int toneVal;
long duration; // khoang thoi gian
float distance; // khoang cach

void setup(){
  Serial.begin(9600);
  pinMode(triPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pinLed, OUTPUT);
  delay(1000);
}

void loop(){
  digitalWrite(triPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2.0;
  Serial.print("khoang cach = ");
  Serial.print(distance);
  Serial.print("cm\n");
  
  if (distance < 20 && distance > 10){
    digitalWrite(pinLed, HIGH);
    for (int x = 0; x < 180; x++) {
      float sinVal = (sin(x * (3.1412 / 180)));
      toneVal = 2000 + (int(sinVal * 1000));
      tone(ALARM, toneVal);
      delay(2);
    }
  }else{ 
      digitalWrite(pinLed, LOW);
      noTone(ALARM);
    }
     delay(20);
}
