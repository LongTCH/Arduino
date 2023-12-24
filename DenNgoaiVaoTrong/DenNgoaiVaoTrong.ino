

int led[5] = {3,5,6,9,10};

void setup() {
  for (int i = 0; i < 5; i++)
    pinMode(led[i], OUTPUT);
}

void loop() {
  for(int i = 0; i < 5; i++){
    digitalWrite(led[4- i], LOW);
    delay(500);
  }
  for(int i = 0; i < 5; i++){
    digitalWrite(led[i], HIGH);
    delay(500);
  }
  
}
