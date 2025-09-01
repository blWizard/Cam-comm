// Reciever of camera´s info.

String input;
float final_data;

void equilibrate_ball() {
  float offset = receive_offset_data();
  // Serial.println("Recibí data!!");
  while (offset != -1000.00) {
    Serial.print("Offset dentro del while: ");
    Serial.println(offset);
    if (offset < 0) {
      // Mover a la izquierda
      Serial.println("Moviendome hacia izquierda!!!");
      move_left(122);

    }
    else if (offset > 0) {
      // Mover a la derecha
      Serial.println("Moviendome hacia la derecha!!!");
      move_right(122);

    }
    // else 9
    offset = receive_offset_data();
  }
  Serial.println("No recibí datos");
}

float receive_offset_data(){
  if (Serial1.available() >= 1) {
    input = Serial1.readStringUntil('\n');
    float offset = input.toFloat();
    return offset;
  }
  return -1000.00;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  motors_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  equilibrate_ball();
}
