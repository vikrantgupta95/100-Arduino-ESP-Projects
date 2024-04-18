/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95/

  Copyright (c) 2024 Vikrant Gupta

  Description: This Arduino code is designed to control a set of actuators based on the temperature 
  readings from a sensor connected to pin A1. The code initializes serial communication at 9600 baud 
  rate and sets up the digital pins 2, 3, 4, 6, and analog pin A0 for output. The program continuously 
  reads the analog value from the sensor and converts it to temperature in degrees Celsius, printing the
  result to the serial monitor. If the temperature exceeds 50 degrees Celsius, it triggers a series of 
  actions to control various actuators. Once the temperature falls below 50 degrees Celsius, the actuators
  return to their initial state.



  Last updated: 2024-03-25
*/

int sensepin = A1;  // Define analog pin for temperature sensor

void setup() {
  Serial.begin(9600);     // Initialize serial communication
  pinMode(6, OUTPUT);     // Set pin 6 as output
  digitalWrite(6, LOW);   // Set pin 6 to LOW initially
  pinMode(A0, OUTPUT);    // Set A0 pin as output
  digitalWrite(A0, LOW);  // Set A0 pin to LOW initially
  pinMode(3, OUTPUT);     // Set pin 3 as output
  digitalWrite(3, LOW);   // Set pin 3 to LOW initially
  pinMode(2, OUTPUT);     // Set pin 2 as output
  digitalWrite(2, LOW);   // Set pin 2 to LOW initially
  pinMode(4, OUTPUT);     // Set pin 4 as output
  digitalWrite(4, LOW);   // Set pin 4 to LOW initially
}

void loop() {
  int temp1 = analogRead(sensepin);  // Read temperature from sensor
  Serial.println(temp1 * 0.49);      // Convert and print temperature in degrees Celsius

  // Control actions based on temperature threshold
  if ((temp1 * 0.49) > 50) {
    // Activate actuators
    digitalWrite(6, LOW);
    digitalWrite(A0, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);
    delay(5000);  // Wait for 5 seconds
    digitalWrite(6, LOW);
    digitalWrite(A0, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);

    digitalWrite(4, HIGH);
    delay(10000);  // Wait for 10 seconds
    digitalWrite(4, LOW);

    digitalWrite(A0, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    delay(5000);  // Wait for 5 seconds
    digitalWrite(6, LOW);
    digitalWrite(A0, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
  }

  // Reset actuators if temperature falls below threshold
  if ((temp1 * 0.49) < 50) {
    digitalWrite(6, LOW);
    digitalWrite(A0, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
  }
}