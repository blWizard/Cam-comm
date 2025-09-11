int EN1 = 6; // OK
int forward_motor1 = 8;
int backward_motor1 = 7;

int EN2 = 5; // OK
int forward_motor2 = 2;
int backward_motor2 = 4;

int EN3 = 10; // OK
int forward_motor3 = A0;
int backward_motor3 = A1;

int EN4 = 9; // OK
int forward_motor4 = 12;
int backward_motor4 = 11;

void motors_setup() {
  // put your setup code here, to run once:

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);

  pinMode(forward_motor1, OUTPUT);
  pinMode(forward_motor2, OUTPUT);
  pinMode(forward_motor3, OUTPUT);
  pinMode(forward_motor4, OUTPUT);

  pinMode(backward_motor1, OUTPUT);
  pinMode(backward_motor2, OUTPUT);
  pinMode(backward_motor3, OUTPUT);
  pinMode(backward_motor4, OUTPUT);

  digitalWrite(forward_motor1, LOW);
  digitalWrite(forward_motor2, LOW);
  digitalWrite(forward_motor3, LOW);
  digitalWrite(forward_motor4, LOW);

  digitalWrite(backward_motor1, LOW);
  digitalWrite(backward_motor2, LOW);
  digitalWrite(backward_motor3, LOW);
  digitalWrite(backward_motor4, LOW);

}

void move_fw_mt1(int speed) {
  digitalWrite(forward_motor1, HIGH);
  digitalWrite(backward_motor1, LOW);
  analogWrite(EN1, speed);
}

void move_fw_mt2(int speed) {
  digitalWrite(forward_motor2, HIGH);
  digitalWrite(backward_motor2, LOW);
  analogWrite(EN2, speed);
}

void move_fw_mt3(int speed) {
  digitalWrite(forward_motor3, HIGH);
  digitalWrite(backward_motor3, LOW);
  analogWrite(EN3, speed);
}

void move_fw_mt4(int speed) {
  digitalWrite(forward_motor4, HIGH);
  digitalWrite(backward_motor4, LOW);
  analogWrite(EN4, speed);
}

void move_bw_mt1(int speed) {
  digitalWrite(backward_motor1, HIGH);
  digitalWrite(forward_motor1, LOW);
  analogWrite(EN1, speed);
}

void move_bw_mt2(int speed) {
  digitalWrite(backward_motor2, HIGH);
  digitalWrite(forward_motor2, LOW);
  analogWrite(EN2, speed);
}

void move_bw_mt3(int speed) {
  digitalWrite(backward_motor3, HIGH);
  digitalWrite(forward_motor3, LOW);
  analogWrite(EN3, speed);
}

void move_bw_mt4(int speed) {
  digitalWrite(backward_motor4, HIGH);
  digitalWrite(forward_motor4, LOW);
  analogWrite(EN4, speed);
}

void stop_mt1() {
  // move_motor_forward(1, 0);
  // move_motor_backwards(1, 0);
  move_fw_mt1(0);
  move_bw_mt1(0);
}

void stop_mt2() {
  move_fw_mt2(0);
  move_bw_mt2(0);
}

void stop_mt3() {
  move_fw_mt3(0);
  move_bw_mt3(0);
}

void stop_mt4() {
  move_fw_mt4(0);
  move_bw_mt4(0);
}

void stop_motors() {
  stop_mt1();
  stop_mt2();
  stop_mt3();
  stop_mt4();
}

void move_forward(int speed) {
  move_fw_mt1(speed);
  move_fw_mt2(speed);
  move_fw_mt3(speed);
  move_fw_mt4(speed);
}

void move_backward(int speed) {
  move_bw_mt1(speed);
  move_bw_mt2(speed);
  move_bw_mt3(speed);
  move_bw_mt4(speed);
}

void move_left(int speed) {
  Serial.println("Moving left");
  move_fw_mt1(speed);
  move_bw_mt2(speed);
  move_fw_mt3(speed);
  move_bw_mt4(speed);
}

void move_right(int speed) {
  Serial.println("Moving right");
  move_bw_mt1(speed);
  move_fw_mt2(speed);
  move_bw_mt3(speed);
  move_fw_mt4(speed);
}
