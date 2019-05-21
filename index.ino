// Initializes led
int redLed = 12;
int greenLed = 11;

// Minimum distance for action in centimeters
int minDistance = 15;

// Initializes the first Ultrassonic Sensor
int ultrassonicEcho1 = 6;
int ultrassonicTrigger1 = 5;

// Initializes the second Ultrassonic Sensor
int ultrassonicEcho2 = 9;
int ultrassonicTrigger2 = 8;

void setup() {
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

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

  long duration = pulseIn(echo, HIGH);
  int distance = duration*0.034/2;
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
  ultrassonicSensor(ultrassonicTrigger1, ultrassonicEcho1, greenLed, minDistance);
  ultrassonicSensor(ultrassonicTrigger2, ultrassonicEcho2, redLed, minDistance);
}
