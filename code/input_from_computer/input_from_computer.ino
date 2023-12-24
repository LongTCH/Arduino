int ledpin = 13;
void setup(){
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
}
void loop(){
    if (Serial.available()>0){
        String setupled = Serial.readString();
      switch(setupled){
        case "on":
            digitalWrite(ledpin, HIGH); break;
         case "off":
            digitalWrite(ledpin, LOW); break;
      }
    }
}
