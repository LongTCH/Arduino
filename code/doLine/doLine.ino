int line = 4;
int led = 13;
int value = 0;

//digital
void setup(){
  pinMode(led, OUTPUT);
  pinMode(line, INPUT);
}

void loop(){
  value = digitalRead(line);
  if (value == 0)
    digitalWrite(led, LOW);
   else
    digitalWrite(led, HIGH);
    // line den : 1, ko co mat phan xa
    // line trang : 0, co mat phan xa
}
