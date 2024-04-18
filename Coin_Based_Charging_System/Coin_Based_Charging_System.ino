/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code simulates a coin-based charging system. When a coin is inserted, the charging process starts,
  and after 1 minute, the charging completes. Then, it waits for the next coin to initiate the charging process again.

  Last updated: [Date]
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

long stime = 0;
int sem = 0;
int c = 0;

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(3, INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.println("Coin Based Charging");
  lcd.setCursor(0, 0);
  lcd.print(" Insert Coin!   ");
}

void loop() {
  if (digitalRead(3) == 0 && sem == 0) {
    Serial.println("Coin found");
    if (sem == 0) {
      sem = 1;
      stime = millis() / 1000;
    }
    lcd.setCursor(0, 0);
    lcd.print("Charging :1min");
    digitalWrite(2, HIGH);
    c = 1;
  }
  if (c == 1 && (millis() / 1000 >= stime + 60)) {
    Serial.println("Charging complete, waiting for new coin");
    digitalWrite(2, LOW);
    c = 0;
    sem = 0;
  }
  if (digitalRead(3) == 1 && c == 0) {
    lcd.setCursor(0, 0);
    lcd.print(" Insert Coin!   ");
    digitalWrite(2, LOW);
  }
}
