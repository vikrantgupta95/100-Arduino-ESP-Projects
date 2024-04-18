/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95/
  Copyright: [@ Vikrant Gupta]

  Description: This Arduino code implements a prepaid energy meter system using a GSM module and a 
  liquid crystal display (LCD). It continuously monitors energy usage and updates the balance accordingly. 
  When the balance reaches a critical level, it sends an SMS notification to a predefined number.

  Last updated: 26-03-2024
*/

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
SoftwareSerial gsm(3, 2);

int balance = 0;
String str;
String msg;
int sem = 0;
int count = 0;
int count1 = 0;
int timesTosend = 1;

void setup() {
  Serial.begin(9600);
  Serial.println("Prepaid energy meter");

  Serial.begin(9600);
  gsm.begin(9600);
  gsm.println("AT+CMGF=1");
  delay(500);
  gsm.println("AT+CNMI=2,2,0,0,0");
  delay(2000);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Energy Meter");
  lcd.setCursor(0, 1);
  lcd.print("Made by:");
  pinMode(4, INPUT);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Akarsh, Amit");
  lcd.setCursor(0, 1);
  lcd.print("Hemant");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Count: ");
  lcd.setCursor(0, 1);
  lcd.print("Balance: ");
  delay(2000);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
}

void loop() {
  if (gsm.available() > 0) {
    str = gsm.readString();
    Serial.print(str);
    msg = str.substring(51);
    Serial.print(msg);
    if (msg[0] >= '0' && msg[0] <= '9') {
      balance = (msg[0] - 48) * 100;
      Serial.print("balance:");
      Serial.println(balance);
      lcd.setCursor(10, 1);
      lcd.print(balance);
    }
  }

  if ((digitalRead(4) == 1) && (sem == 0)) {
    sem = 1;
    count++;
    Serial.print("count:");
    Serial.println(count);
    lcd.setCursor(8, 0);
    lcd.print(count);
    lcd.print("  ");
  }

  if ((digitalRead(4) == 0) && (sem == 1)) {
    sem = 0;
  }

  if (balance == 0) {
    digitalWrite(5, LOW);  // Relay
  }

  if (balance > 0) {
    digitalWrite(5, HIGH);  // Relay
  }

  if (count == 5 && balance > 0) {
    count = 0;
    balance = balance - 20;
    Serial.println(balance);
    lcd.setCursor(8, 0);
    lcd.print(count);
    lcd.print("   ");
    lcd.setCursor(10, 1);
    lcd.print(balance);
    lcd.print("   ");
    if (balance == 20) {
      Serial.println("low balance");
      count1 = 0;
      gsm.println("AT+CMGF=1");  // Set GSM to text mode
      delay(200);
      while (count1 < timesTosend) {
        delay(1500);
        gsm.print("AT+CMGS=\"");
        gsm.print("9654323594");
        gsm.println("\"");
        while (gsm.read() != '>')
          ;
        {
          gsm.println("low balance, recharge soon");
          delay(500);
          gsm.write(0x1A);  // Sends ctrl+z end of message
          gsm.write(0x0D);  // Carriage Return in Hex
          gsm.write(0x0A);  // Line feed in Hex
          delay(5000);
        }
        count1++;
      }
    }
    if (balance == 0) {
      Serial.println("no balance");
      gsm.println("AT+CMGF=1");  // Set GSM to text mode
      delay(200);
      count1 = 0;
      while (count1 < timesTosend) {
        delay(1500);
        gsm.print("AT+CMGS=\"");
        gsm.print("9654323594");
        gsm.println("\"");
        while (gsm.read() != '>')
          ;
        {
          gsm.println("no balance, recharge now");
          delay(500);
          gsm.write(0x1A);  // Sends ctrl+z end of message
          gsm.write(0x0D);  // Carriage Return in Hex
          gsm.write(0x0A);  // Line feed in Hex
          delay(5000);
        }
        count1++;
      }
    }
  }
}
