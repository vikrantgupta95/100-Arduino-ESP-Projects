/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code utilizes a DS1307 RTC module connected via I2C to read 
  date and time information. It initializes a LiquidCrystal display
  and displays the current date and time on it. Additionally, it 
  controls a relay and a buzzer based on predefined time conditions
  switching between day and night modes.

  Last updated: 2024-04-18
*/

#include <Wire.h>
#include "RTClib.h"
#if defined(ARDUINO_ARCH_SAMD)
   #define Serial SerialUSB
#endif

#include <LiquidCrystal.h>

int s = 0;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
RTC_DS1307 rtc;

void setup() {
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);  // Relay
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);  // Buzzer
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();
  lcd.setCursor(0, 0);
  lcd.print(now.year());
  lcd.print('/');
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.day());
  lcd.setCursor(0, 1);
  lcd.print(now.hour(21));
  lcd.print(':');
  lcd.print(now.minute(0));
  lcd.print(':');
  lcd.print(now.second(0), DEC);

  if (now.hour() == 21 && now.minute() == 0) { // Night time
    digitalWrite(6, HIGH);
    digitalWrite(3, LOW);
  }
  
  if (now.hour() == 6 && now.minute() == 0) { // Day time
    digitalWrite(6, LOW);
    if (s == 0) {
      s = 1;
      digitalWrite(3, HIGH);
      delay(1000);
    }
  }      
}
