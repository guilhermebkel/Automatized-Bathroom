// Initializes led
int redLed = 12;
int greenLed = 11;

int minDistance = 15; // Minimum distance for action in centimeters
int delayBeforeActivation = 9; // Delay for activation in seconds

// Initializes the first Ultrassonic Sensor
int ultrassonicEcho1 = 6;
int ultrassonicTrigger1 = 5;

// Initializes the second Ultrassonic Sensor
int ultrassonicEcho2 = 9;
int ultrassonicTrigger2 = 8;

void setup() {
  Serial.begin(9600);

  // Sets the green and red leds
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  // Sets echo and trigger for the first Ultrassonic Sensor
  pinMode(ultrassonicTrigger1, OUTPUT);
  pinMode(ultrassonicEcho1, INPUT);

  // Sets echo and trigger for the second Ultrassonic Sensor
  pinMode(ultrassonicTrigger2, OUTPUT);
  pinMode(ultrassonicEcho2, INPUT);
}

void ultrassonicSensor(int trigger, int echo, int led, int minDistance, int delayBeforeActivation, int toiletNumber){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigger, LOW);

  long duration = pulseIn(echo, HIGH);
  int distance = duration*0.034/2;
  //Serial.println(distance);

  // Turns on led if sensor reads less than the minimum distance
  /*if(distance < minDistance){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }*/

  // If sensor reads less than the minimum distance, 
  // it triggers a simple time counter and after it goes
  // off, start the action.
  if(distance < minDistance){
    
    char state[100];
    sprintf(state, "Someone has got to the Toilet[%d], let's start counting:", toiletNumber);
    Serial.println(state);
    
    for(int i=0; i<delayBeforeActivation; i++){
      Serial.println(i);
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      delay(500);
    }
  
    Serial.println("Flushing!");
    digitalWrite(led, HIGH);
    delay(5000);
    digitalWrite(led, LOW);
    Serial.println("Finished!\n");
  }
}

void loop() {
  ultrassonicSensor(ultrassonicTrigger1, ultrassonicEcho1, greenLed, minDistance, delayBeforeActivation, 1);
  ultrassonicSensor(ultrassonicTrigger2, ultrassonicEcho2, redLed, minDistance, delayBeforeActivation, 2);
}
