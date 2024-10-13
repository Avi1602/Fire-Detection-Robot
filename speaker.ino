#define SENSOR_PIN_1 2
#define SENSOR_PIN_2 7
#define SENSOR_PIN_3 8
#define RELAY_PIN 4
#define SPEAKER_PIN 3
#define SPRINKLER_START_DELAY 5000  // 5 seconds 
#define SPRINKLER_ON_TIME 3000       // 3 seconds Sprinkler on time

unsigned long previousTime = millis();

void setup() 
{
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SENSOR_PIN_1, INPUT);
  pinMode(SENSOR_PIN_2, INPUT);
  pinMode(SENSOR_PIN_3, INPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() 
{
  // Check if any of the flame sensors detect fire
  if (isFireDetected(SENSOR_PIN_1) || isFireDetected(SENSOR_PIN_2) || isFireDetected(SENSOR_PIN_3)) {
    // If there is fire, play fire siren and activate sprinkler
    playFireSiren();

    if (millis() - previousTime > SPRINKLER_START_DELAY) {
      digitalWrite(RELAY_PIN, LOW);  // Turn on sprinkler after delay
      delay(SPRINKLER_ON_TIME);       // Keep sprinkler on for some time
    }
  } else {
    // If no fire is detected, turn off fire siren and deactivate sprinkler
    noTone(SPEAKER_PIN);  // Turn off fire siren
    digitalWrite(RELAY_PIN, HIGH);  // Turn off sprinkler
    previousTime = millis();  // Reset timer
  }
}

bool isFireDetected(int pin) {
  // Read the sensor value
  int sensorValue = digitalRead(pin);
  
  // Flame sensors output LOW when fire is detected
  if (sensorValue == LOW) {
    return true;  // Fire detected
  } else {
    return false;  // No fire detected
  }
}

void playFireSiren() {
  // Play the fire detection siren sound
  for (int i = 100; i < 2000; i += 10) {
    tone(SPEAKER_PIN, i);
    delay(5); // Adjust this delay to change the speed of the siren
  }
  for (int i = 2000; i > 100; i -= 10) {
    tone(SPEAKER_PIN, i);
    delay(5); // Adjust this delay to change the speed of the siren
  }
}
