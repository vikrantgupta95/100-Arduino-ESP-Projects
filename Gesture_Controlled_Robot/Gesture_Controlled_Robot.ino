/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95/

  Copyright: (c) Vikrant Gupta

  Description: This Arduino code implements a gesture-controlled robot using the ADXL3 accelerometer. 
  It defines pins for the left and right motors, as well as for the x and y axes of the accelerometer. 
  The setup function initializes serial communication and sets the motor driver pins as outputs. 
  The loop function continuously reads the accelerometer values and controls the robot's movement 
  based on predefined conditions for forward, backward, sharp left, and sharp right movements.

  Last updated: [26-03-2024]
*/

// declare pins
int lm1 = 2;
int lm2 = 3;
int rm1 = 4;
int rm2 = 5;
int xpin = A0;                  // x-axis of the accelerometer
int ypin = A1;                  // y-axis

void setup() 
{
  // put your setup code here, to run once:
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

void loop() 
{
  // put your main code here, to run repeatedly:
  if (400 > analogRead(xpin) && analogRead(xpin) > 330 && 400 > analogRead(ypin) && analogRead(ypin) > 330) // condition to stop the bot..
  {
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, LOW);
  }

  if (analogRead(xpin) < 330 && 400 > analogRead(ypin) && analogRead(ypin) > 330)  // forward..
  {
    digitalWrite(lm1, HIGH);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, HIGH);
    digitalWrite(rm2, LOW);
  }

  if (analogRead(xpin) > 400 && 400 > analogRead(ypin) && analogRead(ypin) > 330)  // backward...
  {
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, HIGH);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, HIGH);
  }

  if (400 > analogRead(xpin) && analogRead(xpin) > 330 && analogRead(ypin) < 330)  // sharp left...
  {
    digitalWrite(lm1, LOW);
    digitalWrite(lm2, HIGH);
    digitalWrite(rm1, HIGH);
    digitalWrite(rm2, LOW);
  }

  if (400 > analogRead(xpin) && analogRead(xpin) > 330 && 400 < analogRead(ypin))  // sharp right
  {
    digitalWrite(lm1, HIGH);
    digitalWrite(lm2, LOW);
    digitalWrite(rm1, LOW);
    digitalWrite(rm2, HIGH);
  }
}
