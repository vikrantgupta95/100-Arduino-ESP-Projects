/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95/

  Description: This Arduino code utilizes a DHT sensor to measure temperature and humidity. It also 
  controls a servo motor and a DC motor based on the temperature readings. Additionally, it displays
  temperature and humidity readings on a 16x2 LCD display. The code initializes the DHT sensor, 
  LCD display, and servo motor. It continuously reads temperature and humidity, calculates the heat 
  index, and adjusts the servo motor and DC motor based on predefined temperature thresholds.

  Last updated: [Date of Last Update]
*/

#include "DHT.h"
#include <LiquidCrystal.h>
#include <Servo.h>

#define DHTPIN 11  // Pin connected to the DHT sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11  // DHT 11
// #define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);
Servo myservo;
Servo myservo2;
int motorPin = 3;

LiquidCrystal lcd(13, 12, 16, 17, 18, 19);  // Pins for LCD display

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  lcd.clear();
  lcd.print("DHT11 - Super");
  dht.begin();
  myservo.attach(9);
  myservo2.attach(8);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Read temperature and humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  float hi = dht.computeHeatIndex(f, h);

  // Print temperature and humidity readings
  Serial.print("Humidity: ");
  lcd.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(h);
  lcd.print(" h");
  lcd.print(t);
  lcd.print(" *C");
  lcd.setCursor(1, 1);
  lcd.print(f);
  lcd.print(" *F");

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");
  myservo.write(90);

  // Control servo and DC motor based on temperature
  if (t > 30) {
    myservo.write(10);
    digitalWrite(motorPin, HIGH);
  }

  if (t < 29) {
    myservo.write(140);
    digitalWrite(motorPin, LOW);
  }

  if (t < 27) {
    myservo.write(180);
  }
}
