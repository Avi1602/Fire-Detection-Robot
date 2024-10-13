#define SENSOR_PIN_1 11
#define SENSOR_PIN_2 7
#define SENSOR_PIN_3 8
#define RELAY_PIN 4

#define BUZZER_PIN 3
#define SPRINKLER_START_DELAY 5000  // 5 seconds 
#define SPRINKLER_ON_TIME 3000      // 3 seconds Sprinkler on time
#define SERVO_PIN 9
 
#include <Servo.h>


unsigned long previousTime = millis();
Servo servoMotor; 

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SENSOR_PIN_1, INPUT);
  pinMode(SENSOR_PIN_2, INPUT);
  pinMode(SENSOR_PIN_3, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  servoMotor.attach(SERVO_PIN); // Attach servo motor to pin 9
}

void loop() {
  // Check if any of the flame sensors detect fire
  if (isFireDetected(SENSOR_PIN_1)) {
    moveServoToPosition(1);
    activateFireSiren();
    activateSprinkler();
  }
  else if (isFireDetected(SENSOR_PIN_2)) {
    moveServoToPosition(2);
    activateFireSiren();
    activateSprinkler();
  }
  else if (isFireDetected(SENSOR_PIN_3)) {
    moveServoToPosition(3);
    activateFireSiren();
    activateSprinkler();
  }
  else {
    // No fire detected, turn off fire siren and sprinkler
    deactivateFireSiren();
    deactivateSprinkler();
  }
}

bool isFireDetected(int pin) {
  int sensorValue = digitalRead(pin);
  return sensorValue == LOW; // Fire detected when sensor value is LOW
}

void activateFireSiren() {
  // Generate fire siren sound
  for (int i = 100; i < 2000; i += 10) {
    tone(BUZZER_PIN, i);
    delay(5);
  }
  for (int i = 2000; i > 100; i -= 10) {
    tone(BUZZER_PIN, i);
    delay(5);
  }
}

void deactivateFireSiren() {
  // Turn off fire siren
  noTone(BUZZER_PIN);
}

void activateSprinkler() {
  if (millis() - previousTime > SPRINKLER_START_DELAY) {
    digitalWrite(RELAY_PIN, LOW); // Turn on sprinkler
    delay(SPRINKLER_ON_TIME);
    digitalWrite(RELAY_PIN, HIGH); // Turn off sprinkler
    previousTime = millis();
  }
}

void deactivateSprinkler() {
  digitalWrite(RELAY_PIN, HIGH); // Turn off sprinkler
}

void moveServoToPosition(int sensorNumber) {
  // Move the servo motor based on which sensor detects fire
  switch (sensorNumber) {
    case 1:
      servoMotor.write(0); // Move servo to position for sensor 1
      break;
    case 2:
      servoMotor.write(90); // Move servo to position for sensor 2
      break;
    case 3:
      servoMotor.write(180); // Move servo to position for sensor 3
      break;
  }
}
