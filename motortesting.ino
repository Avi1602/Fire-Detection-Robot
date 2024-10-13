// Include the necessary libraries
#include <AFMotor.h>

AF_DCMotor motor(2);

void setup() {


}

void loop() {
  motor.setSpeed(200);
  motor.run(FORWARD);
  delay(2000);
  motor.run(RELEASE);
  delay(1000);
  motor.run(BACKWARD);
  delay(2000);
  motor.run(RELEASE); 
  delay(1000);  
}
