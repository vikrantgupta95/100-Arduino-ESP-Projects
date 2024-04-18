/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code reads the state of a switch connected to pin 2 and controls a motor using an H-bridge motor driver.
  When the switch is pressed, the motor is activated in one direction for a brief period of time, then stops,
  and finally rotates in the opposite direction for a brief period of time.

  Last updated: [Date]
*/

int switchPin;  // Variable to store the pin connected to the switch

void setup() {
  pinMode(2, INPUT);  // The pin connected to the switch is declared as INPUT
  pinMode(3, OUTPUT); // Pin M1.1 of the motor shield declared as OUTPUT
  pinMode(4, OUTPUT); // Pin M1.2 of the motor shield declared as OUTPUT
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  switchPin = digitalRead(2);  // Reads the state of the switch

  if (switchPin == HIGH) {     // Check if the switch is pressed
    digitalWrite(3, HIGH);     // Starts the motor (clockwise or anti-clockwise)
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    delay(100);
    digitalWrite(3, LOW);      // Stops the motor
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    delay(5000);
    digitalWrite(3, LOW);      // Starts the motor (clockwise or anti-clockwise)
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    delay(100);
  } else {
    digitalWrite(3, LOW);      // Stops the motor
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
}
