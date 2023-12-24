int led = 13;
int light = A0;
int val = 0;

void setup(){
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  val = analogRead(light);
  Serial.println(val);
  // val giam khi co anh sang chieu vao
  if (val < 400){
    digitalWrite(led, LOW);
  }
  else {
    digitalWrite(led, HIGH);
  }
  delay(500);
}
