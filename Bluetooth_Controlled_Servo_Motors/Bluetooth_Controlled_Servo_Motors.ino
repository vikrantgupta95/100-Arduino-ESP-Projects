/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code controls multiple servos based on commands received from an Android app via Bluetooth.
  It reads the Bluetooth input and rotates the servos according to the received values.

  Last updated: [Date]
*/

#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo4;
Servo myservo5;

int bluetoothTx = A0; // Bluetooth TX connected to pin A0
int bluetoothRx = A1; // Bluetooth RX connected to pin A1

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {
  myservo1.attach(9); // Attach servo signal wire to pin 9
  myservo2.attach(10);
  myservo4.attach(11);
  myservo5.attach(6);

  // Setup USB serial connection to computer
  Serial.begin(9600);

  // Setup Bluetooth serial connection to Android
  bluetooth.begin(9600);
}

void loop() {
  // Read from Bluetooth and write to USB serial
  if (bluetooth.available() > 0) { // Receive number from Bluetooth
    int servopos1 = bluetooth.read(); // Save the received number
    Serial.println(servopos1); // Serial print the received number
    myservo1.write(servopos1); // Rotate the servo to the received angle

    delay(1000);

    int servopos2 = bluetooth.read();
    Serial.println(servopos2);
    myservo2.write(servopos2);

    delay(1000);

    int servopos4 = bluetooth.read();
    Serial.println(servopos4);
    myservo4.write(servopos4);

    delay(1000);

    int servopos5 = bluetooth.read();
    Serial.println(servopos5);
    myservo5.write(servopos5);
  }
}
