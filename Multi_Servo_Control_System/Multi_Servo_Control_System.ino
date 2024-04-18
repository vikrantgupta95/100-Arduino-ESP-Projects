/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code controls multiple servo motors based on serial input. Servo positions are adjusted 
  sequentially based on the input character received from the serial monitor. It allows rotating 
  the servo motors in different directions.

  Last updated: [Date]
*/

#include <Servo.h> 

char inputCharacter;
 
Servo servo1;  // create servo object to control a servo 
Servo servo2;  // create servo object to control a servo 
Servo servo3;  // create servo object to control a servo 
Servo servo4;  // create servo object to control a servo 
Servo servo5;  // create servo object to control a servo 

int position1 = 0;  // variable to store the servo position
int position2 = 0;  // variable to store the servo position
int position3 = 0;  // variable to store the servo position
int position4 = 0;  // variable to store the servo position
int position5 = 0;  // variable to store the servo position
 
void setup() {
  servo1.attach(11);  // attaches the servo on pin 11 to the servo object
  servo2.attach(10);  // attaches the servo on pin 10 to the servo object
  servo3.attach(9);   // attaches the servo on pin 9 to the servo object
  servo4.attach(6);   // attaches the servo on pin 6 to the servo object
  servo5.attach(5);   // attaches the servo on pin 5 to the servo object 

  Serial.begin(9600);
} 

void loop() {
  if (Serial.available() > 0) {
    inputCharacter = Serial.read();
  }

  if (inputCharacter == 'a') {
    // Rotate servo1
    for (position1 = 0; position1 <= 180; position1 += 1) {
      servo1.write(position1);
      delay(15);
    }
    for (position1 = 180; position1 >= 0; position1 -= 1) {
      servo1.write(position1);
      delay(15);
    }

    // Rotate servo2
    for (position2 = 0; position2 <= 150; position2 += 1) {
      servo2.write(position2);
      delay(15);
    }
    delay(1000);

    // Rotate servo3
    for (position3 = 180; position3 >= 0; position3 -= 1) {
      servo3.write(position3);
      delay(15);
    }
    delay(1000);

    // Rotate servo4
    for (position4 = 0; position4 <= 100; position4 += 1) {
      servo4.write(position4);
      delay(15);
    }

    // Rotate servo5
    for (position5 = 0; position5 <= 180; position5 += 1) {
      servo5.write(position5);
      delay(15);
    }
    delay(1000);

    // Reset servo2
    for (position2 = 150; position2 >= 0; position2 -= 1) {
      servo2.write(position2);
      delay(15);
    }
    delay(1000);
  } 
  else if (inputCharacter == 's') {
    // Rotate servo3
    for (position3 = 0; position3 >= 100; position3 -= 1) {
      servo3.write(position3);
      delay(15);
    }
    delay(1000);

    // Rotate servo4
    for (position4 = 60; position4 >= 0; position4 -= 1) {
      servo4.write(position4);
      delay(15);
    }
    delay(1000);

    // Rotate servo5
    for (position5 = 180; position5 >= 0; position5 -= 1) {
      servo5.write(position5);
      delay(15);
    }
  } 
}
