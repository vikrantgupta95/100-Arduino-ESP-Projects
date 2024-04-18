/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95/

  Copyright: [(C) Vikrant Gupta]

  Description: This Arduino code implements a Bluetooth-controlled robot using a servo motor. It includes 
  communication with a Bluetooth module via SoftwareSerial and control of two servos based on received commands. 
  The setup function initializes serial communication, Bluetooth communication, and servo motor attachments. 
  The loop function continuously reads commands from the Bluetooth module and controls the servos accordingly.

  Last updated: [Date of Last Update]
*/

#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial blue(4, 5);
Servo myservo1;
Servo myservo2;
int button = 12;
char bt;
int i;

void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  Serial.begin(9600);
  Serial.println("test");
  blue.begin(9600);
  myservo1.attach(9);
  myservo2.attach(8);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (digitalRead(12) == 0) {
    digitalWrite(6, HIGH);
    digitalWrite(A0, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);

    for (int i = 0; i < 10; i++) {
      myservo1.write(180);
      delay(100);
      myservo1.write(90);
      delay(100);
      myservo2.write(180);
      delay(100);
      myservo2.write(90);
      delay(100);
    }
    i = 0;
    digitalWrite(6, LOW);
    digitalWrite(A0, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    delay(2000);
    digitalWrite(6, HIGH);
    digitalWrite(A0, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    delay(5000);
    digitalWrite(6, HIGH);
    digitalWrite(A0, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);

    for (int i = 0; i < 10; i++) {
      myservo1.write(180);
      delay(100);
      myservo1.write(90);
      delay(100);
      myservo2.write(180);
      delay(100);
      myservo2.write(90);
      delay(100);
    }

    i = 0;
    digitalWrite(6, LOW);
    digitalWrite(A0, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    delay(2000);
    digitalWrite(6, HIGH);
    digitalWrite(A0, LOW);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    delay(5000);
    digitalWrite(6, HIGH);
    digitalWrite(A0, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
  }

  while (digitalRead(12) == 1) {
    if (blue.available() > 0) {
      bt = blue.read();
      Serial.print(bt);
      if (bt == 'B') {
        digitalWrite(6, HIGH);
        digitalWrite(A0, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(2, LOW);
      }
      if (bt == 'R') {
        digitalWrite(6, LOW);
        digitalWrite(A0, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
      }
      if (bt == 'L') {
        digitalWrite(6, LOW);
        digitalWrite(A0, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, HIGH);
      }
      if (bt == 'F') {
        digitalWrite(6, LOW);
        digitalWrite(A0, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(2, HIGH);
      }
      if (bt == 'S') {
        digitalWrite(6, LOW);
        digitalWrite(A0, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
      }
    }
    if (bt == 'r') {
      i = 0;
      digitalWrite(6, LOW);
      digitalWrite(A0, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
      for (i = 0; i <= 10; i++) {
