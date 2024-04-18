/*
 Transmitter data pin to Arduino pin 11
 Author: Vikrant_Gupta
 Email: vikrantgupta95@gmail.com
 LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
 GitHub: https://github.com/vikrantgupta95

Description: This code controls a robotic arm using servo motors based on input 
received from various sources, including IR sensors and Bluetooth communication 
From BrainWave Sensor.The robotic arm consists of a base, shoulder, wrist, and finger servos, each 
controlled independently. The arm's movements are programmed to perform 
predefined actions when triggered by specific input signals.
*/

#include <Servo.h>

Servo base;   // for base
Servo servo2; // for shoulder
Servo servo3; // for wrist
Servo finger; // for finger

int pos = 0;  // variable to store the servo position

void setup() {
  pinMode(2, INPUT);   // IR sensor connection for input
  base.attach(9);      // attaches the servo on pin 9 to the servo object
  servo2.attach(10);   // attaches the servo on pin 10 to the servo object
  servo3.attach(11);   // attaches the servo on pin 11 to the servo object
  finger.attach(6);    // attaches the servo on pin 6 to the servo object
  Serial.begin(9600);
  delay(1000);
  servo3.write(20);
  delay(1000);
  servo2.write(5);
  delay(1000);
  base.write(130);
  delay(1000);
  finger.write(0);
}

char str[2], i;

void baseMovement() {
  for (pos = 130; pos >= 20; pos -= 1) { // for motion of base function created over Bluetooth
    base.write(pos);
    delay(15);
  }
}

void shoulderMovement() {
  for (pos = 20; pos <= 90; pos += 1) { // for motion of shoulder function created over Bluetooth
    servo3.write(pos);
    delay(15);
  }
}

void wristMovement() {
  delay(1000);
  for (pos = 5; pos <= 90; pos += 1) { // for motion of wrist function created over Bluetooth
    servo2.write(pos);
    delay(15);
  }
}

void fingersMovement() {
  for (pos = 5; pos <= 90; pos += 1) { // for motion of finger function created over Bluetooth
    servo2.write(pos);
    delay(15);
  }
}

void loop() {
  int x = digitalRead(2);
  if (x == 1) {
    // Perform predefined actions when triggered by IR sensor input
    baseMovement();
    delay(1000);
    shoulderMovement();
    delay(1000);
    finger.write(30);
    delay(1000);
    wristMovement();
    delay(1000);
    finger.write(0);
    delay(1000);
    servo2.write(90);
    delay(1000);
    servo3.write(90);
    delay(1000);
    base.write(20);
    delay(1000);
    shoulderMovement();
    delay(1000);
    wristMovement();
    delay(1000);
    finger.write(30);
    delay(1000);
    servo2.write(5);
    delay(1000);
    servo3.write(20);
    delay(1000);
    finger.write(0);
    delay(1000);
  }
  
  if (x == 0) {
    delay(1000);
  }

  while (Serial.available()) {
    char ch = Serial.read();
    str[i++] = ch;

    if (str[i - 1] == '1') {
      Serial.println("base");
      baseMovement();
      i = 0;
    } else if (str[i - 1] == '2') {
      Serial.println("shoulder");
      shoulderMovement();
      i = 0;
    } else if (str[i - 1] == '3') {
      Serial.println("wrist");
      wristMovement();
      i = 0;
    } else if (str[i - 1] == '4') {
      Serial.println("fingers");
      fingersMovement();
      i = 0;
    }
  }
}