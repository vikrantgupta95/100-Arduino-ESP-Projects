/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

Description:
  This code implements a visitor counter system using GPS and GSM modules. 
  It utilizes ultrasonic sensors to detect the entry and exit of visitors and increments or decrements 
  the count accordingly. Additionally, it integrates a GPS module to track the location of the device. 
  When a visitor enters, the system sends an SMS notification containing the current location (latitude and longitude) 
  to a predefined phone number using a GSM module. The code also includes details about the author and how to contact them.
*/

#include <LiquidCrystal.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// LCD setup
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Define input and output pins
#define in A3
#define out A4

// Initialize count variables
int count = 0;
int count1 = 0;

// GPS setup
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

char inchar; // Will hold the incoming character from the GSM shield
SoftwareSerial SIM900(4, 5);
int timesTosend = 1;
int sense = 0;

void IN() {
  if (digitalRead(out) == 1) {
    count++;
  }
  lcd.clear();
  lcd.print("Count:");
  lcd.setCursor(0, 1);
  lcd.print(count);
  delay(1000);
}

void OUT() {
  if (digitalRead(in) == 1) {
    count--;
  }
  lcd.clear();
  lcd.print("Count:");
  lcd.setCursor(0, 1);
  lcd.print(count);
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  Serial.println("GPS Vehicle Tracking System");
  Serial.println();
  SIM900.begin(9600);
  ss.begin(GPSBaud);
  delay(100);
  lcd.begin(16, 2);
  lcd.print("Visitor Counter");
  delay(2000);
  pinMode(A0, INPUT); //wire
  digitalWrite(A0, LOW);
  pinMode(A1, OUTPUT); //buzzer
  pinMode(A2, INPUT); //pir
  pinMode(in, INPUT); // in sensor
  pinMode(out, INPUT); // out sensor
  lcd.clear();
  lcd.print("Count:");
  lcd.setCursor(0, 1);
  lcd.print(count);
}

void loop() {
  if (digitalRead(in)) IN();
  if (digitalRead(out)) OUT();

  if (digitalRead(A2) == 0) { // PIR
    digitalWrite(A1, HIGH);
    delay(1000);
    digitalWrite(A1, LOW);
  }
  if (digitalRead(A0) == 0) {
    Serial.println("trigger");
    sense = 1;
  }
  if (digitalRead(A0) == 1) {
    Serial.println("No trigger");
    sense = 0;
    count1 = 0;
  }
  while (ss.available() > 0)
    if (gps.encode(ss.read())) {
      displayInfo();
      if (analogRead(A0) == 0) {
        sense = 1;
      }
      if (analogRead(A0) == 1) {
        sense = 0;
        count1 = 0;
      }
      if (digitalRead(A2) == 0) { // PIR
        digitalWrite(A1, HIGH);
        delay(1000);
        digitalWrite(A1, LOW);
      }
      if (digitalRead(in)) IN();
      if (digitalRead(out)) OUT();
    }

  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("No GPS detected: check wiring."));
  }
}

void displayInfo() {
  Serial.print(analogRead(A0));
  Serial.print(F("Location: "));
  if (gps.location.isValid()) {
    if (digitalRead(A2) == 0) { // PIR
      digitalWrite(A1, HIGH);
      delay(1000);
      digitalWrite(A1, LOW);
    }
    if (digitalRead(in)) IN();
    if (digitalRead(out)) OUT();
    if (sense == 1 || digitalRead(A0) == 0) {
      digitalWrite(A1, HIGH);
      SIM900.begin(9600);
      if (digitalRead(A2) == 0) { // PIR
        digitalWrite(A1, HIGH);
        delay(1000);
        digitalWrite(A1, LOW);
      }
      if (digitalRead(in)) IN();
      if (digitalRead(out)) OUT();
      SIM900.println("AT+CMGF=1"); // set GSM to text mode
      delay(200);
      while (count1 < timesTosend) {
        delay(1500);
        SIM900.print("AT+CMGS=\"");
        SIM900.print("9911331389");
        SIM900.println("\"");
        while (SIM900.read() != '>');
        {
          SIM900.println("Location:");
          SIM900.println("Lat -");
          SIM900.println(gps.location.lat()); // SMS body
          delay(500);
          SIM900.println();
          SIM900.println("Lng -");
          SIM900.println(gps.location.lng()); // SMS body
          delay(500);
          SIM900.write(0x1A); // sends ctrl+z end of message
          SIM900.write(0x0D); // Carriage Return in Hex
          SIM900.write(0x0A); // Line feed in Hex
          delay(5000);
        }
        count1++;
        digitalWrite(A1, LOW);
      }
    }
    ss.begin(GPSBaud);
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.println(gps.location.lng(), 6);
  } else {
    Serial.println(F("INVALID"));
  }
}
