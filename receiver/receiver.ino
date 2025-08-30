// Reciever of camera´s info.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available() > 1) {
    int input = Serial1.read();
    Serial.println("Input: ");
    Serial.println(input);
  }
  else {
    Serial.println("No recibí info!");
  }
}
