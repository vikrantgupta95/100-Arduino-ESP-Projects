/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95/
  Copyright: [@ Vikrant Gupta]

  Description: This Arduino code controls a robot with multiple motor configurations. It receives commands
  from the serial monitor and executes corresponding actions such as moving forward, backward, left, right,
  stopping, or activating a cleaning function.

  Last updated: 26-03-2024
*/

#define m11 12    // Rear motor
#define m12 11
#define m21 10    // Front motor
#define m22 9
#define m31 8     // Cleaner motor
#define m32 7
char str[2], i;

/**
 * Function to move the robot forward
 */
void forward() {
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}

/**
 * Function to move the robot backward
 */
void backward() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}

/**
 * Function to turn the robot left
 */
void left() {
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}

/**
 * Function to turn the robot right
 */
void right() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}

/**
 * Function to stop the robot
 */
void Stop() {
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}

/**
 * Function to activate the cleaner mechanism
 */
void Cleaner() {
  digitalWrite(m31, HIGH);
  digitalWrite(m32, LOW);
  delay(1000);
  digitalWrite(m31, LOW);
  digitalWrite(m32, HIGH);
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(m31, OUTPUT);
  pinMode(m32, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    char ch = Serial.read();
    str[i++] = ch;

    if (str[i - 1] == '1') {
      Serial.println("Forward");
      forward();
      i = 0;
    }

    else if (str[i - 1] == '2') {
      Serial.println("Left");
      left();
      i = 0;
    }

    else if (str[i - 1] == '3') {
      Serial.println("Right");
      right();
      i = 0;
    }

    else if (str[i - 1] == '4') {
      Serial.println("Backward");
      backward();
      i = 0;
    }

    else if (str[i - 1] == '5') {
      Serial.println("Stop");
      Stop();
      i = 0;
    }
    else if (str[i - 1] == '6') {
      Serial.println("Cleaner");
      Cleaner();
      i = 0;
    }
    delay(100);
  }
}
