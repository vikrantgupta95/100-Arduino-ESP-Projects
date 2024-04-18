/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95/
  Copyright: [@ Vikrant Gupta]


  Description: This Arduino code implements an IoT home security system using PIR motion sensors, a gas sensor, 
  and a servo motor controlled via a GSM module. The system detects motion using PIR sensors and triggers an alarm 
  or notification. It also monitors gas levels and activates an exhaust fan in case of a gas leak. The system can 
  be remotely activated or deactivated using a mobile phone connected to the GSM module.
  
  Last updated: 26-03-2024
*/

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial SIM900(3, 4);  // RX, TX for GSM module
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
Servo myservo;

int pos = 0;                       // Initial position for servo motor
const int pirSensorPin = 2;        // PIR sensor pin
const int pirActivatorPin = A1;    // PIR activator pin
const int servoActivatorPin = A2;  // Servo activator pin
const int gasSensorPin = A0;       // Gas sensor pin
const int exhaustPin = 5;          // Exhaust fan control pin

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("IOT Home Security");
  lcd.setCursor(0, 1);
  lcd.print("Made by: Suraj, Vipin, Ubais, Vasudev, Sophia");
  lcd.clear();
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("PIR:");
  lcd.setCursor(0, 1);
  lcd.print("Gas: ");
  Serial.begin(9600);

  pinMode(pirSensorPin, INPUT);
  pinMode(pirActivatorPin, INPUT);
  pinMode(servoActivatorPin, INPUT);
  pinMode(exhaustPin, OUTPUT);
  digitalWrite(exhaustPin, LOW);  // Initially turn off exhaust fan
  pinMode(gasSensorPin, INPUT);

  myservo.attach(6);   // Servo motor attached to pin 6
  myservo.write(pos);  // Set initial position for servo motor
  delay(500);
  SIM900.begin(9600);
}

void loop() {
  if (digitalRead(pirActivatorPin) == 1) {  // PIR activated
    Serial.println("PIR activated");
    lcd.setCursor(5, 0);
    lcd.print("Activated  ");

    if (digitalRead(pirSensorPin) == 1) {  // PIR active
      Serial.println("PIR active");
      Serial.println("Calling");
      SIM900.begin(9600);
      SIM900.println("ATD + +919911331389;");  // Call predefined number
      delay(100);
      SIM900.println();
      delay(30000);           // Wait for 30 seconds...
      SIM900.println("ATH");  // Hang up
    }
  } else {
    Serial.println("PIR deactivated");
    lcd.setCursor(5, 0);
    lcd.print("Deactivated");
  }

  if (digitalRead(servoActivatorPin) == 0) {  // Servo deactivated
    Serial.println("Servo deactivated");
    pos = 0;
    myservo.write(pos);
    delay(300);
  } else {
    Serial.println("Servo activated");
    pos = 180;
    myservo.write(pos);
    delay(300);
  }

  lcd.setCursor(6, 1);
  lcd.print(analogRead(gasSensorPin));  // Display gas sensor reading on LCD

  if (analogRead(gasSensorPin) >= 500) {  // Gas trigger
    Serial.println("Gas trigger");
    Serial.println("Calling");
    digitalWrite(exhaustPin, HIGH);  // Activate exhaust fan
    SIM900.begin(9600);
    SIM900.println("ATD + +919911331389;");  // Call predefined number
    delay(100);
    SIM900.println();
    delay(30000);           // Wait for 30 seconds...
    SIM900.println("ATH");  // Hang up
  } else {
    digitalWrite(exhaustPin, LOW);  // Turn off exhaust fan
    Serial.println("Gas no trigger");
  }
}
