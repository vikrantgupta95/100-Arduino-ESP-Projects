/*

Author: Vikrant_Gupta
Email: vikrantgupta95@gmail.com
LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
GitHub: https://github.com/vikrantgupta95

Description: This code receives messages via VirtualWire and controls a motor based on the received commands.
               It also sends SMS notifications using AT commands.
  
Last Updated: [18-04-2024] 

*/

#include <LiquidCrystal.h>
#include <VirtualWire.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
int timesToSend = 1; // Number of times to send SMS notification
int count1 = 0;
int count = 0;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.println("AT+CMGF=1"); // set Serial to text mode
  delay(200);
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Smart Field");
  delay(2000);
  vw_set_rx_pin(6);
  vw_setup(2000); // Bits per sec
  vw_rx_start(); // Start the receiver
}

void loop() {
  if (vw_get_message(message, &messageLength)) { // Non-blocking
    Serial.print("Received: ");
    for (int i = 0; i < messageLength; i++) {
      Serial.write(message[i]);
    }
    Serial.println();
    if (message[0] == 'y') {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Smart Field");
      lcd.setCursor(0, 1);
      lcd.print("Motor Off");
      Serial.println("AT+CMGF=1"); // set Serial to text mode
      delay(200);
      delay(500);
      while (count < timesToSend) {
        delay(1500);
        Serial.print("AT+CMGS=\"");
        Serial.print("9997346944");
        Serial.println("\"");
        while (Serial.read() != '>');
        {
          Serial.println("Motor pump is off");
          delay(1000);
          Serial.write(0x1A); // sends ctrl+z end of message
          Serial.write(0x0D); // Carriage Return in Hex
          Serial.write(0x0A); // Line feed in Hex
          delay(5000);
        }
        count++;
      }
    }

    if (message[0] == 'n') {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Smart Field");
      lcd.setCursor(0, 1);
      lcd.print("Motor On  ");
      Serial.begin(9600);
      Serial.println("AT+CMGF=1"); // set Serial to text mode
      delay(200);
      delay(500);
      while (count1 < timesToSend) {
        delay(1500);
        Serial.print("AT+CMGS=\"");
        Serial.print("9997346944");
        Serial.println("\"");
        while (Serial.read() != '>');
        {
          Serial.println("Motor on");
          delay(1000);
          Serial.write(0x1A); // sends ctrl+z end of message
          Serial.write(0x0D); // Carriage Return in Hex
          Serial.write(0x0A); // Line feed in Hex
          delay(5000);
        }
        count1++;
      }
    }

    if (message[0] == 'r' || message[0] == 'h') {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Smart Field");
      lcd.setCursor(0, 1);
      lcd.print("Motor Off");
    }

    if (message[0] == 'l') {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Smart Field");
      lcd.setCursor(0, 1);
      lcd.print("Motor On");
    }
  }
}