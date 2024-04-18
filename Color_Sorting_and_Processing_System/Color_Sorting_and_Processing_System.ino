/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code controls a block sorting system using color sensors and servo motors. It detects blocks of different colors (red, blue, green)
  and processes them accordingly, including lifting, gripping, and sorting.

  Last updated: [Date]
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);  // RS, EN, D4, D5, D6, D7

int OutPut = 6;  // Naming pin 10 of Arduino Uno as output
unsigned int frequencyr = 0;
unsigned int frequencyg = 0;
unsigned int frequencyb = 0;
int s = 0;
int cr = 0;
int cb = 0;
int cg = 0;

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);  // Pins 2, 3, 4, 5 as OUTPUT
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);    // Pin 10 as input
  pinMode(A0, OUTPUT);  // Conveyer motor
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);  // Lifter
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);  // Gripper
  pinMode(A5, OUTPUT);
  pinMode(13, OUTPUT);  // Side motor

  // Initialize sensor pins
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(13, LOW);

  // Initialize frequency selection to 20%
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  Serial.println("Block Sorting System");
}

void loop() {
  // Conveyer motor on
  if (s == 0) {
    digitalWrite(A0, HIGH);
    delay(500);
    digitalWrite(A0, LOW);  // Conveyer motor on
  }

  // Now sense it
  Serial.print("R =");
  lcd.print("R=");  // Printing name
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);               // Setting for RED color sensor
  frequencyr = pulseIn(OutPut, LOW);  // Reading frequency
  Serial.print(frequencyr);
  Serial.print(" ");
  lcd.print(frequencyr);  // Printing RED color frequency
  lcd.print("  ");
  lcd.setCursor(7, 0);  // Moving cursor to position 7
  delay(500);
  Serial.print("B =");
  lcd.print("B=");  // Printing name
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);              // Setting for BLUE color sensor
  frequencyb = pulseIn(OutPut, LOW);  // Reading frequency
  Serial.print(frequencyb);
  Serial.print(" ");
  lcd.print(frequencyb);  // Printing BLUE color frequency
  lcd.print("  ");
  lcd.setCursor(0, 1);
  delay(500);
  Serial.print("G =");
  lcd.print("G=");  // Printing name
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);              // Setting for GREEN color sensor
  frequencyg = pulseIn(OutPut, LOW);  // Reading frequency
  Serial.print(frequencyg);
  Serial.println(" ");
  lcd.print(frequencyg);  // Printing GREEN color frequency
  lcd.print("    ");
  lcd.setCursor(0, 0);
  delay(500);

  // Sensing ends
  if (frequencyr < 100 && frequencyb > 100 && frequencyg > 70 && s == 0) {
    s = 1;
    Serial.println("Red Color Detected");
    cr++;
    Serial.print("Count Red = ");
    Serial.println(cr);
  }
  if (frequencyr > 70 && frequencyb < 120 && frequencyg > 70 && s == 0) {
    s = 2;
    Serial.println("Blue Color Detected");
    cb++;
    Serial.print("Count Blue = ");
    Serial.println(cb);
  }
  if (frequencyr > 70 && frequencyb > 100 && frequencyg < 90 && s == 0) {
    s = 3;
    Serial.println("Green Color Detected");
    cg++;
    Serial.print("Count Green = ");
    Serial.println(cg);
  }
  if (s == 1) {
    Serial.println("Processing red block");
    s = 0;
    digitalWrite(A0, HIGH);
    delay(1500);
    digitalWrite(A0, LOW);
    digitalWrite(A3,
                 HIGH);  // Gripper stop
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);  // Lifter down
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // Stop
    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // Gripper close
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);  // Lifter up
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // Stop
    digitalWrite(A5, HIGH);
    digitalWrite(13, LOW);  // Side motor
    delay(500);
    digitalWrite(A5, LOW);
    digitalWrite(13, LOW);  // Stop
    digitalWrite(A3, HIGH);
    digitalWrite(A4, LOW);  // Gripper open
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);  // Gripper stop
    digitalWrite(A5, LOW);
    digitalWrite(13, HIGH);  // Side motor
    delay(500);
    digitalWrite(A5, LOW);
    digitalWrite(13, LOW);  // Stop
  }

  if (s == 2) {
    Serial.println("Processing blue block");
    s = 0;
    digitalWrite(A0, HIGH);
    delay(1500);
    digitalWrite(A0, LOW);
    digitalWrite(A3, HIGH);  // Gripper stop
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);  // Lifter down
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // Stop
    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // Gripper close
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);  // Lifter up
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // Stop
    digitalWrite(A5, HIGH);
    digitalWrite(13, LOW);  // Side motor
    delay(800);
    digitalWrite(A5, LOW);
    digitalWrite(13, LOW);  // Stop
    digitalWrite(A3, HIGH);
    digitalWrite(A4, LOW);  // Gripper open
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);  // Gripper stop
    digitalWrite(A5, LOW);
    digitalWrite(13, HIGH);  // Side motor
    delay(800);
    digitalWrite(A5, LOW);
    digitalWrite(13, LOW);  // Stop
  }

  if (s == 3) {
    Serial.println("Processing green block");
    s = 0;
    digitalWrite(A0, HIGH);
    delay(1500);
    digitalWrite(A0, LOW);
    digitalWrite(A3, HIGH);  // Gripper stop
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);  // Lifter down
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // Stop
    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // Gripper close
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);  // Lifter up
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // Stop
    digitalWrite(A5, HIGH);
    digitalWrite(13, LOW);  // Side motor
    delay(1200);
    digitalWrite(A5, LOW);
    digitalWrite(13, LOW);  // Stop
    digitalWrite(A3, HIGH);
    digitalWrite(A4, LOW);  // Gripper open
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);  // Gripper stop
    digitalWrite(A5, LOW);
    digitalWrite(13, HIGH);  // Side motor
    delay(1200);
    digitalWrite(A5, LOW);
    digitalWrite(13, LOW);  // Stop
  }
}
