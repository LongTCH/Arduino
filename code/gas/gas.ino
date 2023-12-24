int gasPin = 0;
int ledPin = 13;
int alarmPin = 12;
int val;
float sinVal;
int toneVal;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(alarmPin, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  val = analogRead(gasPin);
  Serial.print("Value: ");
  Serial.print(val);
  Serial.print("\n");

  if (val > 200){
    digitalWrite(ledPin, HIGH);
    for (int x = 0; x < 180; x++) {
      //Convert sin function to radian
      sinVal = (sin(x * (3.1412 / 180)));
      // Use sin function to generate frequency of sound
      toneVal = 2000 + (int(sinVal * 1000));
      tone(alarmPin, toneVal);
      delay(2);
    }
    noTone(alarmPin);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
  
  delay(100);
}
