// Initializes leds
int redLedPin = 12;
int redLedState = LOW;
int greenLedPin = 11;
int greenLedState = LOW;

int minDistance = 25; // Minimum distance for action - in centimeters
int delayBeforeActivation = 9; // Delay for activation - in seconds
int timeBetweenActivation = 5; // Time between activations on Unstoppable Mode - in seconds

// Initializes the first Ultrasonic Sensor
int ultrasonicEcho1 = 6;
int ultrasonicTrigger1 = 5;

// Initializes the second Ultrasonic Sensor
int ultrasonicEcho2 = 9;
int ultrasonicTrigger2 = 8;

// Initializes time variables used in order to make async delay
long previousTime1 = 0;
long previousTime2 = 0;
int ultrasonicCounter1 = 0;
int ultrasonicCounter2 = 0;

void setup() {
  Serial.begin(9600);

  // Sets the green and red leds
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  // Sets echo and trigger for the first Ultrassonic Sensor
  pinMode(ultrasonicTrigger1, OUTPUT);
  pinMode(ultrasonicEcho1, INPUT);

  // Sets echo and trigger for the second Ultrassonic Sensor
  pinMode(ultrasonicTrigger2, OUTPUT);
}

int ultrasonicSensor(int trigger, int echo){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigger, LOW);

  long duration = pulseIn(echo, HIGH);
  int distance = duration*0.034/2;

  return distance;
}

void loop()
{
  unsigned long currentTime = millis();
  
  int distanceUltrasonic1 = ultrasonicSensor(ultrasonicTrigger1, ultrasonicEcho1);
  int distanceUltrasonic2 = ultrasonicSensor(ultrasonicTrigger2, ultrasonicEcho2);
  
  if(distanceUltrasonic1 < minDistance){
    // If counter reaches expected time,
    // makes the expected action.
    if(ultrasonicCounter1 == delayBeforeActivation){
      digitalWrite(greenLedPin, HIGH);
      if (currentTime - previousTime1 > 5000) { 
        ultrasonicCounter1 = 0;
        digitalWrite(greenLedPin, LOW);
      }
    }
    // Counting before making an action.
    else if (currentTime - previousTime1 > 500) { 
      previousTime1 = currentTime;
      if (greenLedState == LOW) {
        greenLedState = HIGH;
      } else {
        greenLedState = LOW;
      }
      digitalWrite(greenLedPin, greenLedState);
      ultrasonicCounter1++;
    }
  }
  else{
    // If sensor stop reading the required signal,
    // resets to initial state.
    digitalWrite(greenLedPin, LOW);
    ultrasonicCounter1 = 0;
  }

  if(distanceUltrasonic2 < minDistance){
    // If counter reaches expected time,
    // makes the expected action.
    if(ultrasonicCounter2 == delayBeforeActivation){
      digitalWrite(redLedPin, HIGH);
      if (currentTime - previousTime2 > 5000) { 
        ultrasonicCounter2 = 0;
        digitalWrite(redLedPin, LOW);
      }
    }
    // Counting before making an action.
    else if (currentTime - previousTime2 > 500) { 
      previousTime2 = currentTime;
      if (redLedState == LOW) {
        redLedState = HIGH;
      } else {
        redLedState = LOW;
      }
      digitalWrite(redLedPin, redLedState);
      ultrasonicCounter2++;
    }
  }
  else{
    // If sensor stop reading the required signal,
    // resets to initial state.
    digitalWrite(redLedPin, LOW);
    ultrasonicCounter2 = 0;
  }

  //ultrasonicSensorUnstoppable(redLed, greenLed, delayBeforeActivation, timeBetweenActivation);
  
}
