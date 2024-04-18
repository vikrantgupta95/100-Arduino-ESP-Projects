/*
 Author: Vikrant_Gupta
 Email: vikrantgupta95@gmail.com
 LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
 GitHub: https://github.com/vikrantgupta95

 Description:
 This code serves as a transmitter for a serving robot system. It sends orders wirelessly using the VirtualWire 
 library to a receiving unit. The orders are displayed on an LCD screen and sent via Bluetooth to a remote device.

 Last updated: 18-04-2024
*/

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <VirtualWire.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 6);
SoftwareSerial blue(4, 5); // RX, TX

String bt;
String f;

void setup() {
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("Order:");
  Serial.begin(9600);
  lcd.setCursor(0, 1);
  lcd.print("Table:");
  lcd.setCursor(0, 2);
  lcd.print("Food:");
  Serial.println("Serving Robot System");

  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);
  pinMode(A1, INPUT);
  digitalWrite(A1, HIGH);
  pinMode(A2, INPUT);
  digitalWrite(A2, HIGH);
  pinMode(A3, INPUT);
  digitalWrite(A3, HIGH);
  pinMode(A4, INPUT);
  digitalWrite(A4, HIGH);

  // Set the data rate for the SoftwareSerial port
  blue.begin(9600);
  blue.println("Place your order:");
  blue.println("Item Code  Item");
  blue.println("F1        Tea");
  blue.println("F2        Coffee");
  blue.println("F3        Pastry");
  blue.println("F4        Patty");
}

void loop() {
  if (blue.available()) {
    if (digitalRead(A3) == 0) {
      send("A");
    }
    if (digitalRead(A2) == 0) {
      send("B");
    }
    if (digitalRead(A1) == 0) {
      send("C");
    }
    if (digitalRead(3) == 0) {
      send("D");
    }
    if (digitalRead(2) == 0) {
      delay(1000);
      blue.println("Place your order:");
      blue.println("Item Code  Item");
      blue.println("F1        Tea");
      blue.println("F2        Coffee");
      blue.println("F3        Pastry");
      blue.println("F4        Patty");
    }
    if (digitalRead(A4) == 0) {
      delay(1000);
      blue.println("Thank You! Order placed, kindly wait and disconnect device ");
      lcd.setCursor(7, 0);
      lcd.print("              ");
      lcd.setCursor(7, 1);
      lcd.print("              ");
      lcd.setCursor(7, 2);
      lcd.print("              ");
    }

    bt = blue.readString();
    lcd.setCursor(7, 0);
    lcd.print(bt);
    Serial.println(bt);
    lcd.setCursor(7, 1);
    lcd.write(bt[0]);
    lcd.write(bt[1]);
    lcd.setCursor(7, 2);
    f = bt.substring(2);
    lcd.print(f);
  }

  if (digitalRead(2) == 0) {
    delay(1000);
    blue.println("Place your order:");
    blue.println("Item Code  Item");
    blue.println("F1        Tea");
    blue.println("F2        Coffee");
    blue.println("F3        Pastry");
    blue.println("F4        Patty");
  }
  if (digitalRead(A4) == 0) {
    delay(1000);
    blue.println("Thank You! Order placed, kindly wait and disconnect device ");
    lcd.setCursor(7, 0);
    lcd.print("              ");
    lcd.setCursor(7, 1);
    lcd.print("              ");
    lcd.setCursor(7, 2);
    lcd.print("              ");
  }

  if (digitalRead(A3) == 0) {
    send("A");
  }
  if (digitalRead(A2) == 0) {
    send("B");
  }
  if (digitalRead(A1) == 0) {
    send("C");
  }
  if (digitalRead(3) == 0) {
    send("D");
  }
}

void send(char *message) {
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}
