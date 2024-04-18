/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code initializes a LiquidCrystal display and displays a message on it. It then reads analog input from 
  pin A0, which is expected to be connected to an alcohol sensor. Based on the sensor reading, it controls 
  an LED indicating ignition status and activates a buzzer if the alcohol level is above a certain threshold, 
  indicating a potential drunk driving situation.

  Last updated: [Date]
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);  // Initialize LiquidCrystal display

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  lcd.begin(16, 2);    // Initialize LCD with 16x2 dimensions
  
  // Display initial messages
  lcd.setCursor(0, 0);
  lcd.print("No_drunk_drive");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aaditya_sharma");
  lcd.setCursor(0, 1);
  lcd.print("Gaurav_chamoli");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alcohol:");
  delay(2000);
  
  // Set pin modes
  pinMode(4, OUTPUT); // Ignition LED
  pinMode(3, OUTPUT); // Buzzer
  
  // Initialize default states
  digitalWrite(4, HIGH); // Ignition LED ON (indicating ignition)
  digitalWrite(3, LOW);  // Buzzer OFF (no alarm)
}

void loop() {
  // Read analog input from alcohol sensor
  int alcoholLevel = analogRead(A0);
  Serial.println(alcoholLevel);
  
  // Display alcohol level on LCD
  lcd.setCursor(10, 0);
  lcd.print(alcoholLevel);
  
  // Check alcohol level and control ignition and buzzer accordingly
  if (alcoholLevel > 500) {
    lcd.setCursor(0, 1);
    lcd.print("Ignition Off");
    digitalWrite(4, LOW);  // Turn off ignition LED
    digitalWrite(3, HIGH); // Activate buzzer
    delay(1000);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Ignition On ");
    digitalWrite(4, HIGH); // Turn on ignition LED
    digitalWrite(3, LOW);  // Turn off buzzer
    delay(1000);
  }
}
