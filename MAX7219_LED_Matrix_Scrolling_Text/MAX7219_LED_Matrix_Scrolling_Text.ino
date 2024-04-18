/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code defines a set of characters stored in PROGMEM for use with 
  a MAX7219 LED matrix display. It also includes functions to display 
  scrolling text on the LED matrix. The code initializes the MAX7219 
  module and communicates with it via the MaxMatrix library.

  Last updated: 18-04-2024
*/

#include "MaxMatrix.h"
#include "avr/pgmspace.h"

PROGMEM const unsigned char CH[] = {
  // Define character bitmaps here
};

int data = 8;    // DIN pin of MAX7219 module
int load = 9;    // CS pin of MAX7219 module
int clock = 10;  // CLK pin of MAX7219 module
String r;
int maxInUse = 6;  //how many MAX7219 are connected
int count = 0;
MaxMatrix m(data, load, clock, maxInUse); // define Library

byte buffer[10];
int i = 0;
char string1[30];  // Scrolling Text
char string2[] = "   ";

void setup() {
  m.init(); // Initialize MAX7219 module
  m.setIntensity(5); // LED Intensity 0-15
  Serial.begin(9600);
}

void loop() {
  byte c;
  delay(100);
  m.shiftLeft(false, true);

  if (Serial.available() > 0) {
    r = Serial.readString();
    i = 0;
    while (r[i] != '\0') {
      string1[i] = r[i];
      i++;
    }
    Serial.println(string1);

    printStringWithShift(string1, 100);  // Send scrolling Text
    printStringWithShift(string2, 100);
  }
  printStringWithShift(string1, 100);  // Send scrolling Text
  printStringWithShift(string2, 100);
}

// Put extracted character on Display
void printCharWithShift(char c, int shift_speed) {
  if (c < 32) return;
  c -= 32;
  memcpy_P(buffer, CH + 7 * c, 7);
  m.writeSprite(maxInUse * 8, 0, buffer);
  m.setColumn(maxInUse * 8 + buffer[0], 0);

  for (int i = 0; i < buffer[0] + 1; i++) {
    delay(shift_speed);
    m.shiftLeft(false, false);
  }
}

// Extract characters from Scrolling text
void printStringWithShift(char* s, int shift_speed) {
  while (*s != 0) {
    printCharWithShift(*s, shift_speed);
    s++;
  }
}
