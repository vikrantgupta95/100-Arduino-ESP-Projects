/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code controls a servo motor to open and close a door based on 
  RFID tag readings. It uses a SoftwareSerial library to communicate 
  with an RFID reader and a Servo library to control the servo motor. 
  Additionally, it displays the door status on an LCD screen.

  Last updated: 18-04-2024
*/
#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal.h>

// Define RFID reader and servo motor pins
SoftwareSerial rfid(5, 6);
Servo myservo;

// Define LCD pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

String r; // Variable to store RFID tag
int a = 0; // Variable to track door status (0 = closed, 1 = open)

void setup() {
  // Initialize servo motor and LCD
  myservo.attach(A0);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Door status");
  delay(3000);
  Serial.begin(9600); // Initialize serial communication for debugging
  rfid.begin(9600);   // Initialize RFID reader
  
}

void loop() {
  // Main code loop
  r = rfid.readString(); // Read RFID tag
  
  // Print RFID tag to serial monitor
  Serial.println(r);

  delay(1000); // Delay to prevent reading too frequently

  // Check RFID tag and door status to determine action
  if (r == "3F0071B57883" && a == 0) { 
    // Open the door
    r = "";  
    myservo.write(150);              
    delay(100);
    lcd.setCursor(0, 1);
    lcd.print("Door Open  ");  
    delay(500);
    a = 1;
  }

  delay(1000);

  if (r == "3F0071B57883" && a == 1) {
    // Close the door
    r = "";
    myservo.write(60);              
    delay(100);
    lcd.setCursor(0, 1);
    lcd.print("Door Closed");  
    delay(500);
    a = 0;
  }

  delay(1000);

  if (r == "360087772DEB" && a == 0) { 
    // Open the door
    r = "";  
    myservo.write(150);              
    delay(100);
    lcd.setCursor(0, 1);
    lcd.print("Door Open  ");  
    delay(500);
    a = 1;
  }

  delay(1000);

  if (r == "360087772DEB" && a == 1) {
    // Close the door
    r = "";
    myservo.write(60);              
    delay(100);
    lcd.setCursor(0, 1);
    lcd.print("Door Closed");  
    delay(500);
    a = 0;
  }
}
