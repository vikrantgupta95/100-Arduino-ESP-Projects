/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code controls a servo motor to open and close a door based on 
  RFID tag readings. It uses a SoftwareSerial library to communicate
  with an RFID reader and a Servo library to control the servo motor. 
  Additionally, it displays the door status on an LCD screen.

  Last updated: 18-04-2024
*/

int a;

void setup() {
  // Initialize input pins for RFID reader signals
  pinMode(2, INPUT);
  digitalWrite(2, LOW);
  pinMode(3, INPUT);
  digitalWrite(3, LOW);
  pinMode(4, INPUT);
  digitalWrite(4, LOW);
  pinMode(5, INPUT);
  digitalWrite(5, LOW);
  pinMode(6, INPUT);
  digitalWrite(6, LOW);
  
  // Initialize output pins for controlling the servo motor
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
}

void loop() {
  // Main code to run repeatedly

  // Check RFID reader signals and control servo motor accordingly
  if (digitalRead(2) == 1) {
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
  }
  if (digitalRead(3) == 1) {
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
  }
  if (digitalRead(4) == 1) {
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }
  if (digitalRead(5) == 1) {
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
  }
  if (digitalRead(6) == 1) {
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }
}


