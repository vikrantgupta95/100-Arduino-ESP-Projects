/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Copyright (c) 2024 Vikrant Gupta

  Description:
  
  This code is designed for a GPS vehicle tracking system with vibration sensing capability. 
  It utilizes the TinyGPS++ library to parse GPS data and SoftwareSerial to communicate with 
  the GPS device. Additionally, it utilizes a vibration sensor to detect triggers and sends 
  SMS notifications using a SIM900 GSM module in case of an accident or vibration event. 
  The system continuously monitors GPS location and triggers SMS alerts when a vibration event
  is detected, providing real-time tracking and accident monitoring capabilities.

  Last updated: 2024-03-25
*/

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 5, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

char inchar; // Will hold the incoming character from the GSM shield
SoftwareSerial SIM900(7, 8);
int timesTosend = 1;
int count = 0;
int numring = 0;
int comring = 3;
int onoff = 0; // 0 = off, 1 = on
int sense = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("GPS Vehicle Tracking System");
  Serial.println();
  
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  
  SIM900.begin(9600);
  ss.begin(GPSBaud);
  
  delay(100);
  pinMode(A1, INPUT);
  digitalWrite(A1, HIGH);
  analogReference(DEFAULT);
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  if (digitalRead(A1) == 0)
  {
    Serial.println("Vibration sensor Trigger");
  }
  
  Serial.println(digitalRead(A1));
  
  while (ss.available() > 0)
  {
    if (gps.encode(ss.read()))
    {
      displayInfo();
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    //while(true);
  }
}

void displayInfo()
{
  Serial.print(analogRead(A1));
  Serial.print(F("Location: "));
  
  if (gps.location.isValid())
  {
    if (digitalRead(A1) == 0)
    {
      digitalWrite(2, HIGH);
      delay(20000);
      digitalWrite(2, LOW);
      
      SIM900.begin(9600);
      SIM900.println("AT+CMGF=1"); //set GSM to text mode
      delay(200);
      
      while (count < timesTosend)
      {
        delay(1500);
        SIM900.print("AT+CMGS=\"");
        SIM900.print("9911331389");
        SIM900.println("\"");
        
        while (SIM900.read() != '>');
        {
          SIM900.println("Name of college");
          SIM900.println("Accident Monitoring System ");
          SIM900.println("Accident location:");
          SIM900.println("Lat -");
          SIM900.println(gps.location.lat());  //SMS body
          delay(500);
          SIM900.println();
          SIM900.println("Lng -");
          SIM900.println(gps.location.lng());  //SMS body
          delay(500);
          SIM900.write(0x1A);  // sends ctrl+z end of message
          SIM900.write(0x0D);  // Carriage Return in Hex
          SIM900.write(0x0A);  // Line feed in Hex
          delay(5000);
        }
        count++;
      } 
    }
    
    ss.begin(GPSBaud);
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.println(gps.location.lng(), 6);
  }
  else
  {
    Serial.println(F("INVALID"));
  }
}
