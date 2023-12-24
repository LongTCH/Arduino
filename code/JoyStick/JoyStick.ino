int JoyStick_x = 0;
int JoyStick_y = 1;
int JoyStick_z = 3;

int rightLed = 4;
int leftLed = 5;
int upLed = 6;
int downLed = 7;

void setup(){
  pinMode(JoyStick_z, INPUT_PULLUP);
  pinMode(rightLed, OUTPUT);
  pinMode(leftLed, OUTPUT);
  pinMode(upLed, OUTPUT);
  pinMode(downLed, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  int x, y, z;
  x = analogRead(JoyStick_x);
  y = analogRead(JoyStick_y);
  z = digitalRead(JoyStick_z);

  Serial.print("x = ");
  Serial.print(x);
  Serial.print("\n");
  Serial.print("y = ");
  Serial.print(y);
  Serial.print("\n");
  Serial.print("z = ");
  Serial.print(z);
  Serial.print("\n\n");

  if (z == 0){
    digitalWrite(rightLed, LOW);
    digitalWrite(leftLed, LOW);
    digitalWrite(upLed, LOW);
    digitalWrite(downLed, LOW);
  }
  else {
    if(x>=550){digitalWrite(rightLed, HIGH);}
    if(y>=550){digitalWrite(downLed, HIGH);}
    if(x<=450){digitalWrite(leftLed, HIGH);}
    if(y<=450){digitalWrite(upLed, HIGH);}
  }
  delay(50);
}
