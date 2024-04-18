/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95/
  Copyright: [@ Vikrant Gupta]

  Description: This Arduino sketch controls multiple servos and DC motors based on input commands 
  received over serial communication via Bluetooth.

  Last updated: 26-03-2024
*/


#define m11 12  // Pin for rear motor
#define m12 11  // Pin for rear motor
#define m21 10  // Pin for front motor
#define m22 8   // Pin for front motor

#include <Servo.h>

Servo myservo1;  // Servo object for GUN
Servo myservo2;  // Servo object for TRIG
Servo myservo3;  // Servo object for Camera

int pos1 = 0;  // Variable to store servo position for GUN
int pos2 = 0;  // Variable to store servo position for TRIG
int pos3 = 0;  // Variable to store servo position for Camera

char str[2], i;  // Array to store incoming characters

void forward() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}

void backward() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}

void left() {
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  delay(100);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}

void right() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  delay(100);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}

void Stop() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}

void gunservo() {
  for (pos1 = 0; pos1 <= 120; pos1 += 1) {
    myservo1.write(pos1);
    delay(15);
  }
  for (pos1 = 180; pos1 >= 0; pos1 -= 1) {
    myservo1.write(pos1);
    delay(15);
  }
}

void trigservo() {
  for (pos2 = 0; pos2 <= 35; pos2 += 1) {
    myservo2.write(pos1);
    delay(10);
  }
  for (pos2 = 180; pos2 >= 0; pos2 -= 1) {
    myservo2.write(pos2);
    delay(15);
  }
}

void camservo() {
  for (pos3 = 0; pos3 <= 160; pos3 += 1) {
    myservo3.write(pos3);
    delay(10);
  }
  for (pos3 = 180; pos3 >= 0; pos3 -= 1) {
    myservo3.write(pos3);
    delay(15);
  }
}

void setup() {
  myservo1.attach(9);  // Servo pin for GUN
  myservo2.attach(6);  // Servo pin for TRIG
  myservo3.attach(5);  // Servo pin for Camera

  Serial.begin(9600);    // Initialize serial communication
  pinMode(m11, OUTPUT);  // Set motor pins as output
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(3, INPUT);  // Input pin

  // Initialize motors
  Stop();
}

void loop() {
  while (Serial.available()) {
    char ch = Serial.read();
    str[i++] = ch;

    // Execute commands based on received input
    if (str[i - 1] == '1') {
      forward();
      i = 0;
    } else if (str[i - 1] == '2') {
      left();
      i = 0;
    } else if (str[i - 1] == '3') {
      right();
      i = 0;
    } else if (str[i - 1] == '4') {
      backward();
      i = 0;
    } else if (str[i - 1] == '5') {
      Stop();
      i = 0;
    } else if (str[i - 1] == '6') {
      trigservo();
      i = 0;
    } else if (str[i - 1] == '7') {
      gunservo();
      i = 0;
    } else if (str[i - 1] == '8') {
      camservo();
      i = 0;
    }
    delay(100);
  }

  int x = digitalRead(3);  // Read input from pin 3
}