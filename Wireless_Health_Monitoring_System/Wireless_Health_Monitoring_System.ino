/*
Author: Vikrant_Gupta
Email: vikrantgupta95@gmail.com
LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
GitHub: https://github.com/vikrantgupta95

Description:
This code receives data wirelessly using the VirtualWire library and 
displays it on a LiquidCrystal display. It interprets incoming messages
to update the display with information such as position, pulse rate, 
temperature, and GSR (Galvanic Skin Response) level. Additionally, 
it controls an output pin to indicate abnormal conditions or emergency 
calls.

Last updated: 18-04-2024
*/

#include <VirtualWire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

void setup() {
  vw_set_rx_pin(6);
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("POSITION:");
  lcd.setCursor(0, 1);
  lcd.print("PULSE RATE:");
  lcd.setCursor(0, 2);
  lcd.print("TEMPERATURE in C:");
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);

  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
  vw_rx_start();  // Start the receiver
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("POSITION:");
  lcd.setCursor(0, 1);
  lcd.print("PULSE RATE:");

  if (vw_get_message(message, &messageLength)) // Non-blocking
  {

    if (message[0] == 'N') {
      lcd.setCursor(11, 0);
      lcd.print("abnormal");
      digitalWrite(5, HIGH);
    }
    if (message[0] == 'l') {
      lcd.setCursor(0, 3);
      lcd.print("GSR : LOW       ");
      digitalWrite(5, LOW);
    }
    if (message[0] == 'h' && message[1] == 'i') {
      lcd.setCursor(0, 3);
      lcd.print("GSR : HIGH      ");
      digitalWrite(5, HIGH);
    }
    if (message[0] == 'm') {
      lcd.setCursor(0, 3);
      lcd.print("GSR : Medium  ");
    }

    if (message[0] == 'o') {
      lcd.setCursor(11, 0);
      Serial.println("normal");
      lcd.print("normal   ");
      digitalWrite(5, LOW);
    }

    if (message[0] == 'h' && message[1] == 'e') {
      vw_wait_rx();
      if (vw_get_message(message, &messageLength)) {
        lcd.setCursor(12, 1);
        for (int i = 0; i < messageLength; i++) {
          lcd.write(message[i]);
        }
        if (message[0] >= '9') {
          digitalWrite(5, HIGH);
        }
      }
    }
    if (message[0] == 't') {
      vw_wait_rx();
      if (vw_get_message(message, &messageLength)) {
        lcd.setCursor(17, 2);
        for (int i = 0; i < messageLength; i++) {
          lcd.write(message[i]);
        }
        if (message[0] >= '4' && message[1] > '1') {
          digitalWrite(5, HIGH);
        }
      }
    }

    if (message[0] == 'e') {
      digitalWrite(5, HIGH);
      lcd.setCursor(0, 3);
      lcd.print("Emergency call  ");
      delay(5000);
      lcd.print("             ");
    }
  }
}
