// Initializes leds
int redLed = 12;
int greenLed = 11;

int minDistance = 15; // Minimum distance for action - in centimeters
int delayBeforeActivation = 9; // Delay for activation - in seconds
int timeBetweenActivation = 5; // Time between activations on Unstoppable Mode - in seconds

// Initializes the first Ultrasonic Sensor
int ultrasonicEcho1 = 6;
int ultrasonicTrigger1 = 5;

// Initializes the second Ultrasonic Sensor
int ultrasonicEcho2 = 9;
int ultrasonicTrigger2 = 8;

void setup() {
  Serial.begin(9600);

  // Sets the green and red leds
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  // Sets echo and trigger for the first Ultrassonic Sensor
  pinMode(ultrasonicTrigger1, OUTPUT);
  pinMode(ultrasonicEcho1, INPUT);

  // Sets echo and trigger for the second Ultrassonic Sensor
  pinMode(ultrasonicTrigger2, OUTPUT);
  pinMode(ultrasonicEcho2, INPUT);
}

void ultrasonicSensor(int trigger, int echo, int led, int minDistance, int delayBeforeActivation, int toiletNumber){
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
  // off, starts the action.
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

void ultrasonicSensorUnstoppable(int led1, int led2, int delayBeforeActivation, int timeBetweenActivation){
    Serial.println("Unstoppable mode actived, let's start counting:");
    for(int i=0; i<delayBeforeActivation; i++){
      Serial.println(i);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      delay(500);
    }
  
    Serial.println("Flushing!");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(5000);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    Serial.println("Finished!\n"); 
    delay(1000*timeBetweenActivation); 
}

void loop() {
  ultrasonicSensor(ultrasonicTrigger1, ultrasonicEcho1, greenLed, minDistance, delayBeforeActivation, 1);
  ultrasonicSensor(ultrasonicTrigger2, ultrasonicEcho2, redLed, minDistance, delayBeforeActivation, 2);
  //ultrassonicSensorUnstoppable(redLed, greenLed, delayBeforeActivation, timeBetweenActivations);
}
