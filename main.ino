#include <Servo.h>
#define B_PIN 1

bool isRun = false;

Servo servo1_left_up;
Servo servo2_right_up;
Servo servo3_left_down;
Servo servo4_right_down;
Servo servo5_ext_right;
Servo servo6_ext_left;

void setup() {
  Serial.begin(115200);

  pinMode(B_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(B_PIN), buttonChanged, RISING);

  servo1_left_up.attach(2); // attaches the servo on pin 1 to the servo object
  servo2_right_up.attach(3);  
  servo3_left_down.attach(4);
  servo4_right_down.attach(5);
  servo5_ext_right.attach(6);
  servo6_ext_left.attach(7);
}

void loop() {
  while (!isRun) {
    delay(15);
  }

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
  while (currPos != targetPos) {
    if (isRun) {
      currPos += currPos < targetPos ? 1 : -1;
      servo.write(currPos);
    }
    delay(50);
  }
}

void buttonChanged() {
  isRun != isRun;
  delay(15);
}