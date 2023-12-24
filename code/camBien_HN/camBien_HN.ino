int pinAlarm = 4;
int pinLed = 13;
int outHN = 7;
float sinVal;
int toneVal;

void setup(){
  pinMode(pinLed, OUTPUT);
  pinMode(pinAlarm, OUTPUT);
  pinMode(outHN, INPUT);
  Serial.begin(9600);
}

void loop(){
  int value = digitalRead(outHN);
  if (value == HIGH){
    digitalWrite(pinLed, HIGH);
    Serial.print("dang di chuyen!");
    Serial.print("\n");
    for (int x = 0; x < 180; x++) {
      //Convert sin function to radian
      sinVal = (sin(x * (3.1412 / 180)));
      // Use sin function to generate frequency of sound
      toneVal = 2000 + (int(sinVal * 1000));
      // Configure the buzzer pin 4
      tone(pinAlarm, toneVal);
      delay(2);
    }
    noTone(pinAlarm);
  }
  else{
    digitalWrite(pinLed, LOW);
    Serial.print("khong co gi di chuyen!");
    Serial.print("\n");
  }
}
