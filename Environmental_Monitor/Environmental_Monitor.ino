/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This Arduino sketch monitors various environmental parameters such as temperature, humidity, heart rate, and GPS location. 
  It utilizes a DHT sensor, a flex sensor, and a GPS module to gather data. Additionally, it includes functionality to send 
  SMS alerts in case of abnormal readings or emergencies. The GSM module is used to send SMS messages containing the sensor 
  readings and GPS location.

  Name: EnvironmentalMonitor
*/

#include <LiquidCrystal.h>
#include <dht.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);  // LCD object
dht DHT;                                 // DHT sensor object

#define dht_dpin A3
#define sensorPin A0
#define RXPin 3
#define TXPin 4
#define GPSBaud 9600

SoftwareSerial SIM900(5, 6);      // SoftwareSerial object for GSM module
SoftwareSerial ss(RXPin, TXPin);  // SoftwareSerial object for GPS module

int i, j;             // Variables for temperature and humidity
int timesTosend = 1;  // Number of times to send SMS
int count = 0;        // Counter variable
int count1 = 0;       // Counter variable
int count2 = 0;       // Counter variable
int count3 = 0;       // Counter variable
int count4 = 0;       // Counter variable
int count5 = 0;       // Counter variable

void setup() {
  lcd.begin(16, 2);    // Initialize LCD
  Serial.begin(9600);  // Initialize Serial

  lcd.begin(16, 2);  // Initialize LCD
  lcd.setCursor(0, 0);
  lcd.print("Soldier Monitor");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.setCursor(7, 0);
  lcd.print("HR:");

  delay(300);  // Let system settle

  analogReference(DEFAULT);
  delay(700);  // Wait rest of 1000ms recommended delay before

  SIM900.begin(9600);  // Initialize GSM module
  pinMode(A4, INPUT);
  digitalWrite(A4, HIGH);
  ss.begin(GPSBaud);  // Initialize GPS module
  delay(700);
}

void loop() {
  while (ss.available() > 0)
    if (gps.encode(ss.read())) {
      if (digitalRead(A4) == 0) {
        Serial.println("button trigger");
        SIM900.begin(9600);
        count = 0;
        SIM900.println("AT+CMGF=1");  // Set GSM to text mode
        delay(200);
        while (count < timesTosend) {
          delay(1500);
          SIM900.print("AT+CMGS=\"");
          SIM900.print("8126176146");
          SIM900.println("\"");
          while (SIM900.read() != '>')
            ;
          {
            SIM900.println("Emergency help location:");
            SIM900.println("Lat -");
            SIM900.println(gps.location.lat());  // SMS body
            delay(500);
            SIM900.println();
            SIM900.println("Lng -");
            SIM900.println(gps.location.lng());  // SMS body
            delay(500);
            SIM900.write(0x1A);  // sends ctrl+z end of message
            SIM900.write(0x0D);  // Carriage Return in Hex
            SIM900.write(0x0A);  // Line feed in Hex
            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count++;
        }
        ss.begin(GPSBaud);
      }
      if (ss.available() > 0)
        if (gps.encode(ss.read())) {
          displayInfo();
        }

      static double oldValue = 0;
      static double oldChange = 0;
      int rawValue = analogRead(sensorPin);
      int value1 = (alpha * oldValue + (1 - alpha) * rawValue) / 3.75;
      Serial.println(value1);
      oldValue = value1;
      lcd.setCursor(11, 0);
      lcd.print(value1);
      if (value1 >= 80) {
        SIM900.begin(9600);
        count = 0;
        SIM900.println("AT+CMGF=1");  // Set GSM to text mode
        delay(200);
        while (count < timesTosend) {
          delay(1500);
          SIM900.print("AT+CMGS=\"");
          SIM900.print("8126176146");
          SIM900.println("\"");
          while (SIM900.read() != '>')
            ;
          {
            SIM900.print("Heart Rate:");
            SIM900.println(value1);
            SIM900.println("Heart trigger location:");
            SIM900.println("Lat -");
            SIM900.println(gps.location.lat());  // SMS body
            delay(500);
            SIM900.println();
            SIM900.println("Lng -");
            SIM900.println(gps.location.lng());  // SMS body
            delay(500);
            SIM900.write(0x1A);  // sends ctrl+z end of message
            SIM900.write(0x0D);  // Carriage Return in Hex
            SIM900.write(0x0A);  // Line feed in Hex
            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count++;
        }
        ss.begin(GPSBaud);
      }
      DHT.read11(dht_dpin);
      if (analogRead(A2) > 900) {
        Serial.print(" flex trigger send msg");
        lcd.setCursor(8, 1);
        lcd.print("Flex Tr. ");
        SIM900.begin(9600);
        count = 0;
        SIM900.println("AT+CMGF=1");  // Set GSM to text mode
        delay(200);
        while (count < timesTosend) {
          delay(1500);
          SIM900.print("AT+CMGS=\"");
          SIM900.print("8126176146");
          SIM900.println("\"");
          while (SIM900.read() != '>')
            ;
          {
            SIM900.println("Dead Soldier, Flex trigger location:");
            SIM900.println("Lat -");
            SIM900.println(gps.location.lat());  // SMS body
            delay(500);
            SIM900.println();
            SIM900.println("Lng -");
            SIM900.println(gps.location.lng());  // SMS body
            delay(500);
            SIM900.write(0x1A);  // sends ctrl+z end of message
            SIM900.write(0x0D);  // Carriage Return in Hex
            SIM900.write(0x0A);  // Line feed in Hex
            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count++;
        }
        ss.begin(GPSBaud);
      }
      if (analogRead(A2) < 900) {
        lcd.setCursor(8, 1);
        lcd.print("          ");
      }
      i = DHT.humidity;
      j = DHT.temperature;
      Serial.print(" ");
      Serial.print(i);
      Serial.print(" ");
      Serial.println(j);

      if (i < 120) {
        lcd.setCursor(3, 0);
        lcd.print(i);
        lcd.print(" ");
      }
      if (j > 15) {
        lcd.setCursor(3, 1);
        lcd.print(j);
        lcd.print(" ");
      }
      if (i > 65 && i < 100) {
        SIM900.begin(9600);
        count = 0;
        SIM900.println("AT+CMGF=1");  // Set GSM to text mode
        delay(200);
        while (count < timesTosend) {
          delay(1500);
          SIM900.print("AT+CMGS=\"");
          SIM900.print("8126176146");
          SIM900.println("\"");
          while (SIM900.read() != '>')
            ;
          {
            SIM900.print("Humidity:");
            SIM900.println(i);
            SIM900.println("Humidity trigger location:");
            SIM900.println("Lat -");
            SIM900.println(gps.location.lat());  // SMS body
            delay(500);
            SIM900.println();
            SIM900.println("Lng -");
            SIM900.println(gps.location.lng());  // SMS body
            delay(500);
            SIM900.write(0x1A);  // sends ctrl+z end of message
            SIM900.write(0x0D);  // Carriage Return in Hex
            SIM900.write(0x0A);  // Line feed in Hex
            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count++;
        }
        ss.begin(GPSBaud);
      }
      if (j > 35 && j > 13) {
        SIM900.begin(9600);
        count = 0;
        SIM900.println("AT+CMGF=1");  // Set GSM to text mode
        delay(200);
        while (count < timesTosend) {
          delay(1500);
          SIM900.print("AT+CMGS=\"");
          SIM900.print("8126176146");
          SIM900.println("\"");
          while (SIM900.read() != '>')
            ;
          {
            SIM900.print("Temperature:");
            SIM900.println(j);
            SIM900.println("Temperature trigger location:");
            SIM900.println("Lat -");
            SIM900.println(gps.location.lat());  // SMS body
            delay(500);
            SIM900.println();
            SIM900.println("Lng -");
            SIM900.println(gps.location.lng());  // SMS body
            delay(500);
            SIM900.write(0x1A);  // sends ctrl+z end of message
            SIM900.write(0x0D);  // Carriage Return in Hex
            SIM900.write(0x0A);  // Line feed in Hex
            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count++;
        }
        ss.begin(GPSBaud);
      }
      displayInfo();
    }
}

void displayInfo() {
  Serial.print(F("Location: "));
  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.println(gps.location.lng(), 6);
  } else {
    Serial.println(F("INVALID"));
  }
}
