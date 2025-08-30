// Reciever of camera´s info.

String input;
float final_data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available() >= 1) {
    input = Serial1.readStringUntil('\n');
    // final_data = input.toFloat();
    offset = input.toFloat();
    // char* decoded_data = (char*)input; 
    // int input = Serial1.readBytesUntil('\n');
    // String message = String(decoded_input);
    
    Serial.print("Offset: ");
    Serial.println(final_data);
  }
  // else {
  //   // Serial.println("No recibí info!");
  // }
}
