#include <Servo.h>

Servo servo1_left_up;
Servo servo2_right_up;
Servo servo3_left_down;
Servo servo4_right_down;
Servo servo5_ext_right;
Servo servo6_ext_left;

void setup() {
  servo1_left_up.attach(1); // attaches the servo on pin 1 to the servo object
  servo2_right_up.attach(2);  
  servo3_left_down.attach(3);
  servo4_right_down.attach(4);
  servo5_ext_right.attach(5);
  servo6_ext_left.attach(6);
}

void loop() {
  reset();

  // Fold top left side
  opServo(servo1_left_up, 180);
  opServo(servo1_left_up, 0);

  // Fold top right side
  opServo(servo2_right_up, 180);
  opServo(servo2_right_up, 0);
  
  // Fold bottom left side
  opServo(servo3_left_down, 180);
  opServo(servo3_left_down, 0);

  // Fold bottom right side
  opServo(servo4_right_down, 180);
  opServo(servo4_right_down, 0);
}

void reset() {
  opServo(servo1_left_up, 0);
  opServo(servo2_right_up, 0);
  opServo(servo3_left_down, 0);
  opServo(servo4_right_down, 0);
  opServo(servo5_ext_right, 0);
  opServo(servo6_ext_left, 0);
}

void opServo(Servo servo, int targetPos) {
  if (targetPos > 180 || targetPos < 0) {
    return;
  }

  int currPos = servo.read();
  if (currPos > targetPos) {
    for (int pos = currPos; pos > targetPos; pos--) {
          servo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
    }
  } else {
    for (int pos = currPos; pos < targetPos; pos++) {
          servo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
    }    
  }
}