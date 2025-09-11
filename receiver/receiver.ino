// Reciever of camera´s info.

struct Ball{
  float offset;
  int width;
  int area;
};

Ball ball;

int min_ball_area = 350;
int max_ball_area = 1000;

String input;
float final_data;
float offset;
int ball_area;

const int approaching_speed = 80;

int centering_ball_speed = 0;

const int centered_ball_speed = 0;
const int no_ball_speed = 0;
const int no_message_speed = 0;

int image_width = 320;

const int min_speed = 55;
const int max_speed = 255;

int calculate_speed(float offset) {
  int pixel_speed = (max_speed - min_speed) / (image_width * 0.5);
  int final_speed = offset * pixel_speed;
  if (final_speed < 0) {
    final_speed = final_speed * -1;
    }
  if (final_speed > max_speed) {
    final_speed = max_speed;
    }
  return final_speed;
  }

void equilibrate_ball(float offset) {
  if (offset == -1000.00) { // If theres "no ball"
    Serial.println("No ball");
    move_left(no_ball_speed);
  }
  else if (offset < 0.00 and offset != -10000.00) { // Double check condition so we do not confuse 'left' messages with 'I did not receive any data' (-10.000) info.
//    Serial.println("Moving left");
    Serial.println(offset);
    centering_ball_speed = calculate_speed(offset);
    move_left(centering_ball_speed);
  }
  else if (offset > 0.00) {
//    Serial.println("Moving right");
    Serial.println(offset);
    centering_ball_speed = calculate_speed(offset);
    move_right(centering_ball_speed);
  }
  else if (offset == 0.00) {
    move_left(centered_ball_speed);
  }
}

void approach_ball(int ball_area){
  if (ball_area > 0){
    if (ball_area < min_ball_area) {
      move_forward(approaching_speed);
    }
    else if (ball_area > max_ball_area) {
      move_backward(approaching_speed);
    }
  }
  else if (ball_area == 0) {
    stop_motors();
  }
}

float receive_offset_data() {
  if (Serial1.available() >= 1) {
    input = Serial1.readStringUntil('\n');
    offset = input.toFloat();
    return offset;
  }
  return -10000.00; // This means there was a problem with the communication, and so, no message was sent, even if the camera have not seen the ball
}

Ball receive_ball_data() {
  if (Serial1.available() > 0) {
    input = Serial1.readStringUntil('\n');
    // Serial.println(input);
    int first_comma = input.indexOf(',');
    int second_comma = input.indexOf(',', first_comma + 1);
    float offset = input.substring(0, first_comma).toFloat(); // Takes string data from index 0 to the index of the first comma
    int width = input.substring(first_comma + 1, second_comma).toInt();
    int area = input.substring(second_comma + 1).toInt();
    asign_ball_data(offset, width, area);
    return ball;
   }
  asign_ball_data(-10000.00, -1, -1);
  return ball;
  }

void asign_ball_data(float offset, int width, int area){
  ball.offset = offset;
  ball.width = width;
  ball.area = area;
  }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  motors_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
//  offset = receive_offset_data();
//  equilibrate_ball(offset);
  ball = receive_ball_data();
//  image_width = ball.width;
//  offset = ball.offset;
//  equilibrate_ball(offset);
  ball_area = ball.area;
  approach_ball(ball_area);
}
