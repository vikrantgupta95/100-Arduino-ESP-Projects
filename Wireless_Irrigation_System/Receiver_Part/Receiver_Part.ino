/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95/
  Copyright: [@ Vikrant Gupta]

  Description: This Arduino sketch receives messages wirelessly using VirtualWire library. 
  Depending on the received message, it controls a motor and sends SMS notifications.
*/

#include <LiquidCrystal.h>
#include <VirtualWire.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);   // LCD pins
byte message[VW_MAX_MESSAGE_LEN];         // Buffer to store incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN;  // Size of the message
int timesTosend = 1;                      // Number of times to send SMS
int count1 = 0;                           // Counter for 'n' message
int count = 0;                            // Counter for 'y' message

void setup() {
  lcd.begin(16, 2);    // Initialize LCD
  Serial.begin(9600);  // Initialize Serial communication

  // Setup VirtualWire
  vw_set_rx_pin(6);  // Set the receive pin
  vw_setup(2000);    // Set bits per second
  vw_rx_start();     // Start the receiver
}

void loop() {
  if (vw_get_message(message, &messageLength)) {  // Check for incoming message
    Serial.print("Received: ");
    for (int i = 0; i < messageLength; i++) {
      Serial.write(message[i]);
    }
    Serial.println();

    // Check the received message and take appropriate actions
    if (message[0] == 'y') {  // If received 'y', turn motor off
      lcd.setCursor(0, 1);
      lcd.print("Motor Off");
      Serial.begin(9600);
      Serial.println("AT+CMGF=1");  // Set Serial to text mode
      delay(200);
      delay(500);

      // Send SMS notification
      while (count < timesTosend) {
        delay(1500);
        Serial.print("AT+CMGS=\"");
        Serial.print("9911331389");  // Destination phone number
        Serial.println("\"");
        while (Serial.read() != '>')
          ;
        {
          Serial.println("Motor pump is off");
          // SMS body
          delay(1000);
          // SMS body
          Serial.write(0x1A);  // Send ctrl+z to end message
          Serial.write(0x0D);  // Carriage Return in Hex
          Serial.write(0x0A);  // Line feed in Hex
          delay(5000);         // Wait
        }
        count++;
      }
    }

    if (message[0] == 'n') {  // If received 'n', turn motor on
      lcd.setCursor(0, 1);
      lcd.print("Motor On  ");
      Serial.begin(9600);
      Serial.println("AT+CMGF=1");  // Set Serial to text mode
      delay(200);
      delay(500);

      // Send SMS notification
      while (count1 < timesTosend) {
        delay(1500);
        Serial.print("AT+CMGS=\"");
        Serial.print("9911331389");  // Destination phone number
        Serial.println("\"");
        while (Serial.read() != '>')
          ;
        {
          Serial.println("Motor on");
          // SMS body
          delay(1000);
          // SMS body
          Serial.write(0x1A);  // Send ctrl+z to end message
          Serial.write(0x0D);  // Carriage Return in Hex
          Serial.write(0x0A);  // Line feed in Hex
          delay(5000);         // Wait
        }
        count1++;
      }
    }

    if (message[0] == 'r') {  // If received 'r', display "Motor Off" on LCD
      lcd.setCursor(0, 1);
      lcd.print("Motor Off");
    }
  }
}

#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#include <VirtualWire.h>
byte message[VW_MAX_MESSAGE_LEN];         // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN;  // the size of the message
int timesTosend = 1;
int count1 = 0;
int count = 0;
void setup() {
  lcd.begin(16, 2);

  Serial.begin(9600);
  Serial.println("AT+CMGF=1");  //set Serial to text mode
  delay(200);
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Smart Field");
  delay(2000);
  vw_set_rx_pin(6);

  // Initialize the IO and ISR
  vw_setup(2000);  // Bits per sec
  vw_rx_start();   // Start the receiver
}
void loop() {
  if (vw_get_message(message, &messageLength))  // Non-blocking
  {
    Serial.print("Received: ");
    for (int i = 0; i < messageLength; i++) {
      Serial.write(message[i]);
    }
    Serial.println();
    if (message[0] == 'y') {
      lcd.setCursor(0, 1);
      lcd.print("Motor Off");
      Serial.begin(9600);
      Serial.println("AT+CMGF=1");  //set Serial to text mode
      delay(200);
      delay(500);
      while (count < timesTosend) {
        delay(1500);
        Serial.print("AT+CMGS=\"");
        Serial.print("9911331389");
        Serial.println("\"");
        while (Serial.read() != '>')
          ;
        {
          Serial.println("motor pump is off");

          //SMS body
          delay(1000);
          //SMS body

          Serial.write(0x1A);  // sends ctrl+z end of message
          Serial.write(0x0D);  // Carriage Return in Hex
          Serial.write(0x0A);  // Line feed in Hex

          //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
          delay(5000);
        }
        count++;
      }
    }

    if (message[0] == 'n') {
      lcd.setCursor(0, 1);
      lcd.print("Motor On  ");
      Serial.begin(9600);
      Serial.println("AT+CMGF=1");  //set Serial to text mode
      delay(200);
      delay(500);

      while (count1 < timesTosend) {
        delay(1500);
        Serial.print("AT+CMGS=\"");
        Serial.print("9911331389");
        Serial.println("\"");
        while (Serial.read() != '>')
          ;
        {
          Serial.println("Motor on");

          //SMS body
          delay(1000);
          //SMS body

          Serial.write(0x1A);  // sends ctrl+z end of message
          Serial.write(0x0D);  // Carriage Return in Hex
          Serial.write(0x0A);  // Line feed in Hex

          //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
          delay(5000);
        }
        count1++;
      }
    }

    if (message[0] == 'r') {
      lcd.setCursor(0, 1);
      lcd.print("Motor Off");
    }
  }
}
