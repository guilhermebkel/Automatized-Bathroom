int ledVermelho = 12;
int minDistance = 15;

// Initializes the first Ultrassonic Sensor
int ultrassonicEcho1 = 6;
int ultrassonicTrigger1 = 5;
long duration;
int distance;

void setup() {
  //pinMode(LED_BULTIN, OUTPUT);
  Serial.begin(9600);
  pinMode(ledVermelho, OUTPUT);

  // Sets echo and trigger for the first Ultrassonic Sensor
  pinMode(ultrassonicTrigger1, OUTPUT);
  pinMode(ultrassonicEcho1, INPUT);
}

void ultrassonicSensor(int trigger, int echo, int led, int minDistance){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration*0.034/2;
  Serial.println(distance);

  // Turns on led if sensor reads less than the minimum distance
  if(distance < minDistance){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }
}

void loop() {
  ultrassonicSensor(ultrassonicTrigger1, ultrassonicEcho1, ledVermelho, minDistance);
}
