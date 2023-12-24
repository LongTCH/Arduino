//IC L298N
int ena = 11;
int in1 = 10;
int in2 = 9;

//Joy Stick
int xPin = A0;
int yPin = A1;
int button = 5;


//LED
int ledPin = 13;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
}
int speeds[3] = {150, 200, 255};
int index = 0;
int x, y, z, z_prev;
void loop() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(300);
  
  // z_prev = z;
  // x = analogRead(xPin);
  // y = analogRead(yPin);
  // z = digitalRead(button);
  // Serial.print("x = ");
  // Serial.print(x);
  // Serial.print("y = ");
  // Serial.print(y);
  // Serial.print("z = ");
  // Serial.print(z);
  // Serial.print(";speed = ");
  // Serial.print(speeds[index]);
  // Serial.print("\n");
  // if(y > 700){
  //   analogWrite(in1, speeds[index]);
  //   digitalWrite(in2, LOW);
  // }
  // else if(y < 300){
  //   digitalWrite(in1, LOW);
  //   analogWrite(in2, speeds[index]);
  // }
  // else{
  //   digitalWrite(in1, LOW);
  //   digitalWrite(in2, LOW);
  // }

  // if(z == 0 && z_prev == 1){
  //   index = (index + 1) % 3;
  // }
}
