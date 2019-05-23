int minDistance = 25; // Minimum distance for action - in centimeters
int delayBeforeActivation = 10; // Delay for activation - in seconds
int flushDuration = 5; // Flush action duration - in seconds

// Initializes leds
int redLedPin = 12;
int redLedState = LOW;
int greenLedPin = 11;
int greenLedState = LOW;

// Initializes the first PIR Sensor
int pir1 = 6;

// Initializes the second PIR Sensor
int pir2 = 5;

// Initializes the first Ultrasonic Sensor
int ultrasonicEcho1 = 8;
int ultrasonicTrigger1 = 7;

// Initializes the second Ultrasonic Sensor
int ultrasonicEcho2 = 10;
int ultrasonicTrigger2 = 9;

// Initializes time variables used in order to make async delay
long previousTime1 = 0;
long previousTime2 = 0;
long previousTime3 = 0;
long previousTime4 = 0;
int ultrasonicCounter1 = 0;
int ultrasonicCounter2 = 0;
int ultrasonicState1 = 0;
int ultrasonicState2 = 0;

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
  pinMode(ultrasonicEcho2, INPUT);

  // Sets echo and trigger for the first PIR Sensor
  pinMode(pir1, INPUT);

  // Sets echo and trigger for the second PIR Sensor
  pinMode(pir2, INPUT);
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

void ultrasonicNormalMode(){

  int distanceUltrasonic1 = ultrasonicSensor(ultrasonicTrigger1, ultrasonicEcho1);
  int distanceUltrasonic2 = ultrasonicSensor(ultrasonicTrigger2, ultrasonicEcho2);
  unsigned long currentTime = millis();

  // If counter reaches expected time,
  // makes the expected action.
  if(ultrasonicCounter1 == delayBeforeActivation){
    digitalWrite(greenLedPin, HIGH);
    if (currentTime - previousTime1 > 1000*flushDuration) { 
      ultrasonicCounter1 = 0;
      digitalWrite(greenLedPin, LOW);
    }
  }
  else if(distanceUltrasonic1 < minDistance){
    // Counting before making an action.
    if (currentTime - previousTime1 > 500) { 
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

  // If counter reaches expected time,
  // makes the expected action.
  if(ultrasonicCounter2 == delayBeforeActivation){
    digitalWrite(redLedPin, HIGH);
    if (currentTime - previousTime2 > 1000*flushDuration) { 
      ultrasonicCounter2 = 0;
      digitalWrite(redLedPin, LOW);
    }
  }
  else if(distanceUltrasonic2 < minDistance){
    // Counting before making an action.
    if (currentTime - previousTime2 > 500) { 
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
  
}

void ultrasonicInvertedMode(){

  int distanceUltrasonic1 = ultrasonicSensor(ultrasonicTrigger1, ultrasonicEcho1);
  int distanceUltrasonic2 = ultrasonicSensor(ultrasonicTrigger2, ultrasonicEcho2);
  unsigned long currentTime = millis();

  // If counter reaches expected time,
  // makes the expected action.
  if(ultrasonicCounter1 >= delayBeforeActivation  && distanceUltrasonic1 > minDistance){
      previousTime3 = currentTime;
      ultrasonicState1 = 1;
  }
  if(ultrasonicCounter1 >= delayBeforeActivation && ultrasonicState1){
    digitalWrite(greenLedPin, HIGH);
    if (currentTime - previousTime1 > 1000*flushDuration) { 
      ultrasonicCounter1 = 0;
      ultrasonicState1 = 0;
      digitalWrite(greenLedPin, LOW);
    }
  }
  else if(distanceUltrasonic1 < minDistance){
    // Counting before making an action.
    if(currentTime - previousTime1 > 500) { 
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

  // If counter reaches expected time,
  // makes the expected action.
  if(ultrasonicCounter2 >= delayBeforeActivation && distanceUltrasonic2 > minDistance){
      previousTime4 = currentTime;
      ultrasonicState2 = 1;
  }
  if(ultrasonicCounter2 >= delayBeforeActivation && ultrasonicState2){
    digitalWrite(redLedPin, HIGH);
    if (currentTime - previousTime2 > 1000*flushDuration) { 
      ultrasonicCounter2 = 0;
      ultrasonicState2 = 0;
      digitalWrite(redLedPin, LOW);
    }
  }
  else if(distanceUltrasonic2 < minDistance){
    // Counting before making an action.
    if (currentTime - previousTime2 > 500) { 
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
  
}

void unstoppableMode(){

  unsigned long currentTime = millis();
   
  if(ultrasonicCounter1 == delayBeforeActivation){
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, HIGH);
    if (currentTime - previousTime1 > 1000*flushDuration) { 
      ultrasonicCounter1 = 0;
      digitalWrite(greenLedPin, LOW);
      digitalWrite(redLedPin, LOW);
    }
  }
  else if (currentTime - previousTime1 > 500) { 
    previousTime1 = currentTime;
    if (greenLedState == LOW && redLedState == LOW) {
      greenLedState = HIGH;
      redLedState = HIGH;
    } else {
      greenLedState = LOW;
      redLedState = LOW;
    }
    digitalWrite(greenLedPin, greenLedState);
    digitalWrite(redLedPin, redLedState);
    ultrasonicCounter1++;
  }
    
}

void pirNormalMode (){

  int pirSensor1 = digitalRead(pir1);
  int pirSensor2 = digitalRead(pir2);
   
  if(pirSensor1){
    digitalWrite(greenLedPin, HIGH);
  }
  else{
    digitalWrite(greenLedPin, LOW);
  }
  
  if(pirSensor2){
    digitalWrite(redLedPin, HIGH);
  }
  else{
    digitalWrite(redLedPin, LOW);
  }
 
}

void loop()
{ 
  //ultrasonicNormalMode();
  ultrasonicInvertedMode();
  //pirNormalMode();
  //unstoppableMode(); 
}
