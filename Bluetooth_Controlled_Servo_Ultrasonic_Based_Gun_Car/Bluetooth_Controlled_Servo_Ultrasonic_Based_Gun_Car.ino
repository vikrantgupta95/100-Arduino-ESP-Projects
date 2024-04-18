/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code controls multiple servos and ultrasonic sensor readings based on Bluetooth commands received.
  The servos are controlled to rotate based on the received commands, and the ultrasonic sensor readings are
  displayed on the serial monitor.

  Last updated: [Date]
*/

#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;
Servo myservo1;

SoftwareSerial blue(4, 5); 
char bt;

void setup() {
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  
  Serial.begin(9600);
  Serial.println("Ultrasonic Radar");
  
  blue.begin(9600);
  myservo.attach(9);
  myservo1.attach(10);
}

void loop() {
  long duration, inches, cm;
  bt = blue.read();
  
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
  
  if (inches < 10) {
    digitalWrite(A1, HIGH);
    delay(200);
    digitalWrite(A1, LOW);
    myservo.write(90);
    delay(100);
    myservo.write(160);
    delay(200);
    myservo.write(90);
    delay(100);
  }
  
  bt = blue.read();
  
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
  
  if (bt == 'M' && pos <= 170) {
    pos = pos + 10;
    myservo1.write(pos); 
    delay(50); 
  }
  if (bt == 'N' && pos >= 0) {
    pos = pos - 10;
    myservo1.write(pos); 
    delay(50); 
  }
  
  if (bt == 'T') {
    myservo.write(155); 
    delay(500); 
    myservo.write(90);
  }
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
