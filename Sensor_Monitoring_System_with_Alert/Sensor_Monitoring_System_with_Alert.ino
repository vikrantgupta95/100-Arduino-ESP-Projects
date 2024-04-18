/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code reads data from various sensors including DHT11, MQ7, MQ135, and MQ5, and displays the sensor 
  readings on a 20x4 LiquidCrystal display. If any of the sensor readings exceed predefined thresholds, 
  it activates an LED and a buzzer as an alert. The LCD also displays humidity and temperature readings 
  from the DHT11 sensor.

  Last updated: [Date]
*/

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <stdlib.h>
#include <dht.h>

#define dht_dpin A0 
int mq135;
int mq7;
int mq5;
int i, j;
dht DHT;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("IOT_Sensors");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Vasu_Bajpai");
  lcd.setCursor(0, 1);
  lcd.print("Ayush_Pandey");
  delay(3000);
  lcd.clear();

  analogReference(DEFAULT);
  Serial.begin(9600);
  
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW); // Buzzer
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW); // LED
}

void loop() {
  DHT.read11(dht_dpin);
  i = DHT.humidity;
  j = DHT.temperature;

  mq7 = analogRead(A1);   // MQ7
  mq135 = analogRead(A2); // MQ135
  mq5 = analogRead(A3);   // MQ5

  if (i >= 80 || j >= 40 || mq7 >= 700 || mq135 >= 700 || mq5 >= 700) {
    digitalWrite(3, HIGH); // LED
    digitalWrite(4, HIGH); // Buzzer
    delay(1000);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }

  lcd.setCursor(0, 0);
  lcd.print("MQ7: ");
  lcd.print(mq7);
  lcd.setCursor(0, 1);
  lcd.print("MQ5: ");
  lcd.print(mq5);
  delay(2000);
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("MQ135: ");
  lcd.print(mq135);
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(i);
  lcd.print(" ");
  lcd.setCursor(9, 1);
  lcd.print("T:");
  lcd.print(j);
  lcd.print(" ");
  delay(2000);
  lcd.clear();
}
