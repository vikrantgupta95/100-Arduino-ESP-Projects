/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This Arduino sketch controls a block sorting system using color sensors. It detects red, blue, and green blocks 
  and sorts them accordingly using conveyer motors, lifters, grippers, and side motors. The system utilizes pulseIn 
  function to read frequencies from color sensors and performs actions based on the detected color.

  Name: ColorBlockSorter
*/


int OutPut = 6;  // naming pin 6 of Uno as output

unsigned int frequencyr = 0;
unsigned int frequencyg = 0;
unsigned int frequencyb = 0;
int s = 0;

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(7, 8, 9, 10, 11, 13);  // RS, EN, D4, D5, D6, D7

int cr = 0;
int cb = 0;
int cg = 0;

void setup() {
  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);  // PINS 2, 3, 4, 5 as OUTPUT
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);  // PIN 6 as input

  pinMode(A0, OUTPUT);  // conveyer motor
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);  // lifter
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);  // gripper
  pinMode(A5, OUTPUT);
  pinMode(12, OUTPUT);  // side motor

  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(12, LOW);

  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);  // setting frequency selection to 20%
  Serial.println("Block Sorting System");
}

void loop() {
  // conveyer motor on
  if (s == 0) {
    digitalWrite(A0, HIGH);
    delay(1000);
    digitalWrite(A0, LOW);  //conveyer motor on
  }
  // now sense it
  Serial.print("R =");
  lcd.print("R=");  // printing name

  digitalWrite(4, LOW);
  digitalWrite(5, LOW);  // setting for RED color sensor

  frequencyr = pulseIn(OutPut, LOW);  // reading frequency
  Serial.print(frequencyr);
  Serial.print(" ");
  lcd.print(frequencyr);  // printing RED color frequency

  lcd.print("  ");

  lcd.setCursor(7, 0);  // moving cursor to position 7

  delay(500);

  Serial.print("B =");

  lcd.print("B=");  // printing name

  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);  // setting for BLUE color sensor

  frequencyb = pulseIn(OutPut, LOW);  // reading frequency
  Serial.print(frequencyb);
  Serial.print(" ");
  lcd.print(frequencyb);  // printing BLUE color frequency

  lcd.print("  ");

  lcd.setCursor(0, 1);

  delay(500);

  Serial.print("G =");

  lcd.print("G=");  // printing name

  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);  // setting for GREEN color sensor

  frequencyg = pulseIn(OutPut, LOW);  // reading frequency
  Serial.print(frequencyg);
  Serial.println(" ");
  lcd.print(frequencyg);  // printing GREEN color frequency

  lcd.print("    ");

  lcd.setCursor(0, 0);

  delay(500);
  // sensing ends
  if (frequencyr < 100 && frequencyb > 100 && frequencyg > 70 && s == 0) {
    s = 1;
    Serial.println("Red Color Detected");
    cr++;
    Serial.print("Count Red = ");
    Serial.println(cr);
  }
  if (frequencyr > 70 && frequencyb < 100 && frequencyg > 70 && s == 0) {
    s = 2;
    Serial.println("Blue Color Detected");
    cb++;
    Serial.print("Count Blue = ");
    Serial.println(cb);
  }
  if (frequencyr < 250 && frequencyb < 150 && frequencyb > 100 && frequencyg < 200 && s == 0) {
    s = 3;
    Serial.println("Green Color Detected");
    cg++;
    Serial.print("Count Green = ");
    Serial.println(cg);
  }
  if (frequencyr < 150 && frequencyb < 100 && frequencyg < 70 && s == 0) {
    s = 4;
    Serial.println("Unidentified Color Detected");
    cg++;
    Serial.print("Count Unidentified = ");
    Serial.println(cg);
  }
  if (s == 1) {
    Serial.println("Processing red block");
    s = 0;
    digitalWrite(A0, HIGH);
    delay(800);
    digitalWrite(A0, LOW);

    digitalWrite(A3, HIGH);
    digitalWrite(A4, LOW);
    gripper open
      delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);  //gripper stop

    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);  // lifter down
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // stop

    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // gripper close
    delay(1200);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);

    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);  // lifter up
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // stop

    delay(1000);
    digitalWrite(A5, HIGH);
    digitalWrite(12, LOW);  // side motor
    delay(500);
    digitalWrite(A5, LOW);
    digitalWrite(12, LOW);  // stop

    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // gripper open
    delay(1100);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);  // gripper stop

    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // gripper close
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);

    digitalWrite(A5, LOW);
    digitalWrite(12, HIGH);  // side motor
    delay(470);
    digitalWrite(A5, LOW);
    digitalWrite(12, LOW);  // stop
  }

  if (s == 2) {
    Serial.println("Processing blue block");
    s = 0;
    digitalWrite(A0, HIGH);
    delay(800);
    digitalWrite(A0, LOW);

    digitalWrite(A3, HIGH);
    digitalWrite(A4, LOW);  // gripper open
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);  // gripper stop

    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);  // lifter down
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // stop

    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // gripper close
    delay(1200);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);

    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);  // lifter up
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // stop

    digitalWrite(A5, HIGH);
    digitalWrite(12, LOW);  // side motor
    delay(800);
    digitalWrite(A5, LOW);
    digitalWrite(12, LOW);  // stop

    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // gripper open
    delay(1100);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);  // gripper stop

    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // gripper close
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);

    digitalWrite(A5, LOW);
    digitalWrite(12, HIGH);  // side motor
    delay(750);
    digitalWrite(A5, LOW);
    digitalWrite(12, LOW);  // stop
  }

  if (s == 3) {
    Serial.println("Processing green block");
    s = 0;
    digitalWrite(A0, HIGH);
    delay(800);
    digitalWrite(A0, LOW);

    digitalWrite(A3, HIGH);
    digitalWrite(A4, LOW);  // gripper open
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);  // gripper stop

    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);  // lifter down
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // stop

    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // gripper close
    delay(1100);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);

    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);  // lifter up
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // stop

    digitalWrite(A5, HIGH);
    digitalWrite(12, LOW);  // side motor
    delay(1200);
    digitalWrite(A5, LOW);
    digitalWrite(12, LOW);  // stop

    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // gripper open
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);  // gripper stop

    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // gripper close
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);

    digitalWrite(A5, LOW);
    digitalWrite(12, HIGH);  // side motor
    delay(1000);
    digitalWrite(A5, LOW);
    digitalWrite(12, LOW);  // stop
  }

  if (s == 4) {
    Serial.println("Processing Unidentified block");
    s = 0;
    digitalWrite(A0, HIGH);
    delay(800);
    digitalWrite(A0, LOW);

    digitalWrite(A3, HIGH);
    digitalWrite(A4, LOW);  // gripper open
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);  // gripper stop

    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);  // lifter down
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // stop

    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // gripper close
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);

    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);  // lifter up
    delay(300);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);  // stop

    digitalWrite(A5, LOW);
    digitalWrite(12, HIGH);  // side motor
    delay(800);
    digitalWrite(A5, LOW);
    digitalWrite(12, LOW);  // stop

    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // gripper open
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);  // gripper stop

    digitalWrite(A3, LOW);
    digitalWrite(A4, HIGH);  // gripper close
    delay(1000);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);

    digitalWrite(A5, HIGH);
    digitalWrite(12, LOW);  // side motor
    delay(800);
    digitalWrite(A5, LOW);
    digitalWrite(12, LOW);  // stop
  }
}
