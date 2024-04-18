/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code utilizes a DS1307 RTC module connected via I2C to display and 
  control date and time. It initializes the RTC and checks if it is running.
  If not, it sets the RTC to the current date and time. The code also 
  includes a function to display the date and time on an LCD screen.
  Additionally, it toggles an output pin based on the time of day, 
  turning it HIGH during night time (19:00) and LOW during day time (06:00).

  Last updated: 18-04-2024
*/

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
RTC_DS1307 rtc;

void setup () {
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
  DateTime now = rtc.now();
  
  lcd.setCursor(0, 0);
  lcd.print(now.year());
  lcd.print('/');
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.day());
  
  lcd.setCursor(0, 1);
  lcd.print(now.hour());
  lcd.print(':');
  lcd.print(now.minute());
  lcd.print(':');
  lcd.print(now.second(), DEC); 
  
  if(now.hour() == 19 && now.minute() == 0) //night time
  {
    digitalWrite(2, HIGH);
  }
  if(now.hour() == 6 && now.minute() == 0)  //day time
  {
    digitalWrite(2, LOW);
  }      
}
