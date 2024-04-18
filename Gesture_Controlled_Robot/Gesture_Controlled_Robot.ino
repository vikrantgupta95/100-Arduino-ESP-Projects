/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Description: This code implements a gesture-controlled robot using an ADXL3 
  accelerometer. The robot's movement is controlled based on the readings from 
  the accelerometer, with specific conditions defined for each direction 
  (forward, backward, left, right, and stop). The code also includes information
   about the author and any relevant copyright details.
*/

// declare pins
int lm1 = 2;
int lm2 = 3;
int rm1 = 4;
int rm2 = 5;
int xpin = A0; // x-axis of the accelerometer
int ypin = A1; // y-axis

void setup() {
  Serial.begin(9600);
  // define whether pins are used as input or output
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  // enable pins of motor driver ic
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
}

void loop() {
  if (400 > analogRead(xpin) && analogRead(xpin) > 330 && 400 > analogRead(ypin) && analogRead(ypin) > 330) // condition to stop the bot..
  {
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, LOW);
  }

  if (analogRead(xpin) < 330 && 400 > analogRead(ypin) && analogRead(ypin) > 330) // forward..
  {
    digitalWrite(lm1, HIGH);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, HIGH);
    digitalWrite(rm2, LOW);
  }

  if (analogRead(xpin) > 400 && 400 > analogRead(ypin) && analogRead(ypin) > 330) // backward...
  {
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, HIGH);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, HIGH);
  }

  if (400 > analogRead(xpin) && analogRead(xpin) > 330 && analogRead(ypin) < 330) // sharp left...
  {
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, HIGH);
    digitalWrite(rm1, HIGH);
    digitalWrite(rm2, LOW);
  }

  if (400 > analogRead(xpin) && analogRead(xpin) > 330 && 400 < analogRead(ypin)) // sharp right
  {
    digitalWrite(lm1, HIGH);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, HIGH);
  }

  // testing phase to check adlx module
  //  Serial.print(analogRead(xpin));
  //  // print a tab between values:
  //  Serial.print("\t");
  //  Serial.print(analogRead(ypin));
  //  // print a tab between values:
  //  Serial.println("\t");
  //  delay(100);
}