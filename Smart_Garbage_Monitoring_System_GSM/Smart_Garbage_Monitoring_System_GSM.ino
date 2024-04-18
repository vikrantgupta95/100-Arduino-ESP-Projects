/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code utilizes ultrasonic sensors connected to Arduino to measure the distance to nearby objects. 
  It displays the distance readings on a 16x2 LCD screen and sends SMS notifications using a SIM900 GSM module 
  when the distance to the objects (assumed to be dustbins) falls below a certain threshold, indicating that the 
  dustbins are full. The code also includes information about the author and how to contact them.
*/

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Define the pins for ultrasonic sensors
#define trigPin 2
#define echoPin 3
#define trigPin2 4
#define echoPin2 5
#define trigPin3 6
#define echoPin3 7

// Initialize the LiquidCrystal and SoftwareSerial libraries
LiquidCrystal lcd(A0, 8, 9, 10, 11, 12);
SoftwareSerial SIM900(A1, A2);

// Global variables
int timesTosend = 1;
int count = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize pins for ultrasonic sensors
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  
  // Initialize the LCD display
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("VIT UNIVERSITY");
  lcd.setCursor(0, 1);
  lcd.print("VELLORE .CHENNAI");
  delay(5000);
  lcd.clear();
  lcd.print("Guided By:- ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mr. ");
  lcd.setCursor(0, 1);
  lcd.print("");
  delay(2000);
  lcd.clear();
  lcd.print("Made By:- ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ayush Maan");
  lcd.setCursor(0, 1);
  lcd.print("Wadhwa ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("D1");
  lcd.setCursor(6, 0);
  lcd.print("D2");
  lcd.setCursor(12, 0);
  lcd.print("D3");
  
  // Initialize the SIM900 GSM module
  SIM900.begin(9600);
  delay(100);
}

void loop() {
  // Variables to store distance readings
  long duration, distance;
  long duration2, distance2;
  long duration3, distance3;
  
  // Measure distance for each ultrasonic sensor
  measureDistance(trigPin, echoPin, &duration, &distance);
  measureDistance(trigPin2, echoPin2, &duration2, &distance2);
  measureDistance(trigPin3, echoPin3, &duration3, &distance3);

  // Display distance readings on LCD
  displayDistance(distance, distance2, distance3);
  
  // Check if any dustbin is full and send SMS notifications
  checkAndSendSMS(distance, distance2, distance3);
}

// Function to measure distance using ultrasonic sensor
void measureDistance(int trigPin, int echoPin, long* duration, long* distance) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  *duration = pulseIn(echoPin, HIGH);
  *distance = (*duration / 2) / 29.1;
}

// Function to display distance readings on LCD
void displayDistance(long distance, long distance2, long distance3) {
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print("    ");
  delay(100);
  lcd.setCursor(6, 1);
  lcd.print(distance2);
  lcd.print("    ");
  delay(100);
  lcd.setCursor(12, 1);
  lcd.print(distance3);
  lcd.print("    ");
  delay(100);
}

// Function to check if any dustbin is full and send SMS notifications
void checkAndSendSMS(long distance, long distance2, long distance3) {
  if (distance < 4) {
    sendSMS("Dustbin 1 Full. Location: IET Alwar");
  }
  if (distance2 < 4) {
    sendSMS("Dustbin 2 Full. Location: IET Alwar");
  }
  if (distance3 < 4) {
    sendSMS("Dustbin 3 Full. Location: IET Alwar");
  }
}

// Function to send SMS
void sendSMS(String message) {
  count = 0;
  SIM900.begin(9600);
  SIM900.println("AT+CMGF=1"); // Set GSM to text mode
  delay(200);
  while (count < timesTosend) {
    delay(1500);
    SIM900.print("AT+CMGS=\"");
    SIM900.print("7838941868"); // Replace with your phone number
    SIM900.println("\"");
    while (SIM900.read() != '>');
    {
      SIM900.println(message);
      delay(500);
      SIM900.write(0x1A);  // Send ctrl+z to end the message
      SIM900.write(0x0D);  // Carriage Return in Hex
      SIM900.write(0x0A);  // Line feed in Hex
      delay(5000);
    }
    count++;
  }
}
