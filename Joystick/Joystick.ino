int JoyStick_X = A0;
int JoyStick_Y = A1;
int button = 5;
int ledUp = 2;
int ledRight = 4;
int ledLeft = 3;
int ledDown = 6;

void setup() {
  pinMode(JoyStick_X, INPUT);
  pinMode(JoyStick_Y, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(ledUp, OUTPUT);
  pinMode(ledDown, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int x, y, z;
  x = analogRead(JoyStick_X);
  y = analogRead(JoyStick_Y);
  z = digitalRead(button);

  if (y > 700) {
    digitalWrite(ledLeft, HIGH);
  } else if (y < 500) {
    digitalWrite(ledRight, HIGH);
  } 

  if (x > 700) {
    digitalWrite(ledUp, HIGH);
  } else if (x < 500) {
    digitalWrite(ledDown, HIGH);
  } 

  if (z == 0)
  {
    digitalWrite(ledLeft, LOW);
    digitalWrite(ledRight, LOW);
    digitalWrite(ledUp, LOW);
    digitalWrite(ledDown, LOW);
  }

  Serial.print(x, DEC);
  Serial.print(", ");
  Serial.print(y, DEC);
  Serial.print(", ");
  Serial.println(z, DEC);

  delay(200);
}