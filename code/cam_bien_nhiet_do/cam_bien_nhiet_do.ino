int ALARM = 13;    //define Buzzer digital pin 4
int LM35 = 0;       // connect LM35 to the analog input pin O
float tmprVal = 0;  // define value
float sinVal;
int toneVal;
unsigned long tepTimer = 0;

void setup(void) {
  Serial.begin(9600);      // configure baud rate 9600
  pinMode(ALARM, OUTPUT);  // configure pin Of buzzer
}
void loop(void) {
  int val = analogRead(LM35);
  tmprVal = (float)val * (5.0 / 10.24);  //Convert the voltage value to temperature value
  if (tmprVal > 30) {               // If temperature > 30, the buzzer starts to make sound.
    for (int x = 0; x < 180; x++) {
      //Convert sin function to radian
      sinVal = (sin(x * (3.1412 / 180)));
      // Use sin function to generate frequency of sound
      toneVal = 200 + (int(sinVal * 1000));
      // Configure the buzzer pin 4
      tone(ALARM, toneVal);
      delay(20);
    }
  } else {          // If the temperature 30, turn off the buzzer
    noTone(ALARM);  // Turn Off the buzzer
//    delay(1000);
  }
  if (millis() - tepTimer > 50) {  // Every 500 ms, serial port Output S temperature value
    tepTimer = millis();
    Serial.print("temperature: ");
    Serial.print(tmprVal);
    Serial.println("C");
  }
}
