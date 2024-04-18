/*
 Transmitter data pin to Arduino pin 11
 Author: Vikrant_Gupta
 Email: vikrantgupta95@gmail.com
 LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
 GitHub: https://github.com/vikrantgupta95

 Description:
 This code serves as a transmitter for a sensor-based system. It uses an ultrasonic sensor to measure distance, infrared sensors to detect obstacles and water on the floor, and switches to trigger different actions. It communicates wirelessly using the VirtualWire library.

 Last updated: 18-04-2024
*/

#include <VirtualWire.h>

int sense = A0;

const int trigPin = 2;
const int echoPin = 4;

void setup() {
  analogReference(DEFAULT);
  Serial.begin(9600);

  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec

  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
}

void loop() {
  vw_set_tx_pin(11);

  if (analogRead(sense) > 500) {
    Serial.println("IR Detected");
    digitalWrite(6, HIGH);
    delay(500);
    digitalWrite(6, LOW);
    delay(50);
    digitalWrite(6, HIGH);
    delay(500);
    digitalWrite(6, LOW);
  }

  if (digitalRead(7) == 0) {
    send("one");
    delay(100);
    Serial.println("Switch 1");
  }

  if (digitalRead(8) == 0) {
    send("p");
    delay(100);
    Serial.println("Switch 2");
  }

  if (digitalRead(9) == 0) {
    send("three");
    delay(100);
    Serial.println("Switch 3");
  }

  if (digitalRead(12) == 0) {
    send("four");
    delay(100);
    Serial.println("Switch 4");
  }

  if (digitalRead(A1) == 0 || digitalRead(A2) == 0) {
    Serial.println("Water on floor");
    digitalWrite(6, HIGH);
    delay(3000);
    digitalWrite(6, LOW);
  }

  long duration, inches, cm;

  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
  if (cm < 100) {
    Serial.println("Obstruction found");
    digitalWrite(6, HIGH);
    delay(2000);
    digitalWrite(6, LOW);
  }
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void send(char *message) {
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}
