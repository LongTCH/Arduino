const int cambien = A0; // Cảm biến nối chân số A0 Arduino
const int giatriLedPin = 8; // Chân nối với đèn LED
const int buzzerPin = 9; // Chân nối với buzzer
float sinVal;
int toneVal;
long duration;
float distance;

int giatri;

void setup() {
  Serial.begin(9600);
  pinMode(giatriLedPin, OUTPUT);
  pinMode(cambien, INPUT);
}

void loop() {
  giatri = analogRead(cambien); // Đọc giá trị analog từ cảm biến và gán vào biến giatri

  if (giatri > 150) { // Nếu giá trị cảm biến gas lớn hơn 600
    // Đèn LED sáng
    digitalWrite(giatriLedPin, HIGH); 
    // Buzzer phát ra tiếng cảnh báo
    for(int x=0; x<180; x++){
    sinVal = sin(x*(3.2423/180));
    toneVal = 200 + (int(sinVal *1000));
    tone(buzzerPin, toneVal);
    }
  } else {
    digitalWrite(giatriLedPin, LOW); // Đèn LED tắt
    noTone(buzzerPin); // Tắt buzzer
  }

  Serial.print("Value: ");
  Serial.println(giatri);
  delay(200);
}