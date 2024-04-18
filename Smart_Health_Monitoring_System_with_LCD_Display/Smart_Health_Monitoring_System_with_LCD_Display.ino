/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code initializes a LiquidCrystal display and prints a message on it.
  It then reads analog input from pin A0, which is expected to be 
  connected to an alcohol sensor. Based on the sensor reading, it controls
  an LED indicating ignition status and activates a buzzer if the alcohol
  level is above a certain threshold, indicating a potential drunk 
  driving situation.

  Last updated: [18-04-2024]
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#include <dht.h>
#define dht_dpin A0 
int i, j;
dht DHT;
int sensorPin = A1; // Heart rate

// Pulse Monitor Test Script
double alpha = 0.75;
double change = 0.0;
double minval = 0.0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Patient Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Made by: ");
  delay(4000);
  lcd.clear();
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.setCursor(8, 0);
  lcd.print("P:");
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.setCursor(7, 1);
  lcd.print("HR:");
  pinMode(6, OUTPUT); // Buzzer
  digitalWrite(6, LOW);
  delay(300); // Let system settle
  analogReference(DEFAULT);
  delay(700); // Wait rest of 1000ms recommended delay before
}

void loop() {
  static double oldValue = 0;
  int rawValue = analogRead(sensorPin);
  int value1 = (alpha * oldValue + (1 - alpha) * rawValue) / 3.75;

  lcd.setCursor(12, 1);
  lcd.print(value1);
  lcd.print(" ");
  oldValue = value1;
  DHT.read11(dht_dpin);

  i = DHT.humidity;
  j = DHT.temperature;

  Serial.print(i);
  Serial.print(" ");
  Serial.println(j);

  lcd.setCursor(3, 0);
  lcd.print(i);
  lcd.print(" ");
  lcd.setCursor(3, 1);
  lcd.print(j);
  lcd.print(" ");

  if (i > 60 || j > 40) {
    digitalWrite(6, HIGH); // Buzzer alarm
    delay(500);
    digitalWrite(6, LOW);
  }

  if (analogRead(A2) > 390 || analogRead(A2) < 340) {
    lcd.setCursor(11, 0);
    lcd.print("NO ");
    digitalWrite(6, HIGH); // Buzzer alarm
    delay(2000);
    digitalWrite(6, LOW);
  }

  if (analogRead(A2) >= 340 && analogRead(A2) <= 390) {
    lcd.setCursor(11, 0);
    lcd.print("OK ");
  }
}
