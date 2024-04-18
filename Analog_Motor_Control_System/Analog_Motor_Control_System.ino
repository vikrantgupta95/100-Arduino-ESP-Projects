/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code controls two motors based on analog input from two axes. It reads analog values from two analog pins 
  (A1 and A2) connected to a joystick or similar input device. Depending on the analog readings, it controls the 
  direction of the motors to achieve desired movement.

  Last updated: 18-04-2024
*/

// Define analog pins for x and y axes
int x_axis = A1;
int y_axis = A2;

void setup() {
  Serial.begin(9600);

  // Initialize motor control pins
  pinMode(5, OUTPUT); // Side motor
  pinMode(4, OUTPUT);
  digitalWrite(5, LOW); // Side motor
  digitalWrite(4, LOW);

  pinMode(3, OUTPUT); // Side motor
  pinMode(2, OUTPUT);
  digitalWrite(3, LOW); // Side motor
  digitalWrite(2, LOW);
}

void loop() {
  // Read analog values from the x and y axes
  x_axis = analogRead(A1);
  y_axis = analogRead(A2);
  
  // Print analog values to serial monitor
  Serial.print(x_axis);
  Serial.print(" ");
  Serial.println(y_axis);

  delay(100);

  // Control motor direction based on analog readings
  if (x_axis < 320) {
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
  } else if (x_axis > 380) {
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
  } else if (y_axis > 400) {
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);
  } else if (y_axis < 300) {
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
  } else if (x_axis > 320 && x_axis < 368) {
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
  }
}
