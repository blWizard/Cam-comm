// Reciever TEST of camera´s info.
# include <tuple>

// int width;
// float offset;
// int area;
// std::tuple<int, float, int> data;

// String input;
// float final_data;
// float offset;

// const int centering_ball_speed = 150;
// const int centered_ball_speed = 50;
// const int no_ball_speed = 100;
// const int no_message_speed = 70;

// void equilibrate_ball(float offset) {
//   if (offset == -1000.00) { // If theres "no ball"
//     move_left(no_ball_speed);
//   }
//   else if (offset < 0.00 and offset != -10000.00) { // Double check condition so we do not confuse 'left' messages with 'I did not receive any data' (-10.000) info.
//     move_left(centering_ball_speed);
//   }
//   else if (offset > 0.00) {
//     move_right(centering_ball_speed);
//   }
//   else if (offset == 0.00) {
//     move_left(centered_ball_speed);
//   }
// }

// float receive_offset_data() {
//   if (Serial1.available() >= 1) {
//     input = Serial1.readStringUntil('\n');
//     offset = input.toFloat();
//     return offset;
//   }
//   return -10000.00; // This means there was a problem with the communication, and so, no message was sent, even if the camera have not seen the ball
// }

std::tuple<int, float, int> receive_data() {
  float offset = 0.00;
  int width, area = 0;
  if (Serial1.available() > 0) {
    input = Serial1.readStringUntil('\n');

    int first_comma = input.indexOf(',');
    int second_comma = input.indexOf(',', first_comma + 1);

    if (first_comma > 0 && second_comma > 0) {
      width = input.substring(0, first_comma).toInt();
      offset = input.substring(first_comma + 1, second_comma).toFloat();
      area = input.substring(second_comma + 1).toInt();

      // data = make_tuple(width, offset, area);
      return std::make_tuple(width, offset, area);
    }
  }
}


// void a() {
//   // put your setup code here, to run once:
//   Serial.begin(115200);
//   Serial1.begin(115200);
//   motors_setup();
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   offset = receive_offset_data();
//   equilibrate_ball(offset);
// }
