#include <Servo.h>
#define B_PIN 2

bool isRun = false;

// int SERVO_MIN = 544;
// int SERVO_MAX = 2400;
int SERVO_MIN = 0;
int SERVO_MAX = 180;
int servo1_left_up_startPos = SERVO_MIN;
int servo1_left_up_endPos = SERVO_MAX;
int servo2_right_up_startPos = SERVO_MAX;
int servo2_right_up_endPos = SERVO_MIN;

Servo servo1_left_up;
Servo servo2_right_up;
Servo servo3_left_down;
Servo servo4_right_down;
Servo servo5_ext_right;
Servo servo6_ext_left;

void setup() {
  Serial.begin(115200);

  //pinMode(B_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(B_PIN), buttonChanged, RISING);

  servo1_left_up.attach(6); // attaches the servo on pin 1 to the servo object
  servo2_right_up.attach(7);  
  // servo3_left_down.attach(4);
  // servo4_right_down.attach(5);
  // servo5_ext_right.attach(6);
  // servo6_ext_left.attach(7);
}

void loop() {

  servo1_left_up.write(servo1_left_up_startPos);
  servo2_right_up.write(servo2_right_up_startPos);

  while (!isRun) {
    delay(15);
  }

  reset();

  Serial.println("Folding BEGIN");

  // Fold top left side
  Serial.println("Folding Top Left");
  opServo(servo1_left_up, servo1_left_up_endPos);
  opServo(servo1_left_up, servo1_left_up_startPos);

  // Fold top right side
  Serial.println("Folding Top Right");
  opServo(servo2_right_up, servo2_right_up_endPos);
  opServo(servo2_right_up, servo2_right_up_startPos);
  
  // // Fold bottom left side
  // opServo(servo3_left_down, 180);
  // opServo(servo3_left_down, 0);

  // // Fold bottom right side
  // opServo(servo4_right_down, 180);
  // opServo(servo4_right_down, 0);

  isRun = false;
}

void reset() {
  opServo(servo1_left_up, servo1_left_up_startPos);
  opServo(servo2_right_up, servo2_right_up_startPos);
  // opServo(servo3_left_down, 0);
  // opServo(servo4_right_down, 0);
  // opServo(servo5_ext_right, 0);
  // opServo(servo6_ext_left, 0);
}

void opServo(Servo servo, int targetPos) {
  if (targetPos > 180 || targetPos < 0) {
    return;
  }

  int currPos = servo.read();
  Serial.println(currPos);
  while (currPos != targetPos) {
    if (isRun) {
      currPos += currPos < targetPos ? 1 : -1;
      servo.write(currPos);
    }
    delay(15);
  }
}

void buttonChanged() {  
  detachInterrupt(digitalPinToInterrupt(B_PIN));
  isRun = true;
  delay(100);
  attachInterrupt(digitalPinToInterrupt(B_PIN), buttonChanged, RISING);
}