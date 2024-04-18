/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This Arduino sketch simulates a traffic light control system with countdown timers. It uses interrupts 
  to count the number of vehicles passing by. The system goes through STOP, READY, and GO phases, controlling 
  traffic lights and displaying countdown timers on an LCD.

  Name: TrafficLightController
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // LCD object

int car; // Variable to count vehicles
int timer; // Timer variable

// Function to increment vehicle count
void vehiclenumber() {
  car++;
}

void setup() {
  attachInterrupt(0, vehiclenumber, FALLING); // Attach interrupt to count vehicles
  
  lcd.begin(16, 2); // Initialize LCD
  Serial.begin(9600); // Initialize Serial
  
  lcd.setCursor(0, 0);
  lcd.print("Timer:");
  
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Vehicles:");
  
  pinMode(3, OUTPUT); // Pin 3 for traffic light
  digitalWrite(3, LOW); // Initialize traffic light to LOW
  
  pinMode(4, OUTPUT); // Pin 4 for traffic light
  digitalWrite(4, LOW); // Initialize traffic light to LOW
  
  pinMode(5, OUTPUT); // Pin 5 for traffic light
  digitalWrite(5, LOW); // Initialize traffic light to LOW
  
  pinMode(6, OUTPUT); // Pin 6 for traffic light
  digitalWrite(6, LOW); // Initialize traffic light to LOW
  
  pinMode(A0, OUTPUT); // Pin A0 for control
  digitalWrite(A0, LOW); // Initialize pin A0 to LOW
}

void loop() {
  delay(1000);
  detachInterrupt(0);
  Serial.print("car=");
  Serial.println(car);
  lcd.setCursor(11, 1);
  lcd.print(car);
  attachInterrupt(0, vehiclenumber, FALLING);
  delay(1000);
  
  digitalWrite(A0, HIGH);
  timer = 15;
  lcd.setCursor(12, 0);
  lcd.print("STOP ");
  lcd.setCursor(0, 0);
  lcd.print("Timer:");
  
  // Countdown timer for STOP phase
  for (timer = 15; timer >= 0; timer -= 1) {
    lcd.setCursor(8, 0);
    delay(1000);
    lcd.print(timer);
    lcd.print("  ");
    lcd.setCursor(11, 1);
    lcd.print(car);
  }
  
  digitalWrite(A0, LOW);
  digitalWrite(3, HIGH);
  
  timer = 5;
  lcd.setCursor(12, 0);
  lcd.print("READY");
  lcd.setCursor(0, 0);
  lcd.print("Timer:");
  
  // Countdown timer for READY phase
  for (timer = 5; timer >= 0; timer -= 1) {
    lcd.setCursor(8, 0);
    delay(1000);
    lcd.print(timer);
    lcd.print("  ");
    lcd.setCursor(11, 1);
    lcd.print(car);
  }

  delay(2000);

  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);

  timer = 20;
  lcd.setCursor(12, 0);
  lcd.print("GO   ");
  lcd.setCursor(0, 0);
  lcd.print("Timer:");
  
  // Countdown timer for GO phase
  for (timer = 20; timer >= 0; timer -= 1) {
    lcd.setCursor(8, 0);
    delay(1000);
    lcd.print(timer);
    lcd.print(" ");
    lcd.setCursor(11, 1);
    lcd.print(car);
  }

  digitalWrite(4, LOW);
  digitalWrite(A0, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}
