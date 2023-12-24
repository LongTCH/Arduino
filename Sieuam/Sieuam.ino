
// C++ code
const int trigPin = 3;
const int echoPin = 5;
const int BellPin = 11;
long duration;
int distance;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(BellPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = duration * 0.034/2;
  if(distance >= 10 && distance <= 20) {
    for(int x = 0; x < 180; x++) {
      int val = 2000 + 1000 * sin(x * (3.1412/180));
      tone(BellPin, val);
    }
  } else {
    noTone(BellPin);
  }
  Serial.print("Distance Measured=");
  Serial.print(distance);
  Serial.println("cm");
  delay(50);
}