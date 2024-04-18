/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code reads analog data from a sensor connected to pin A0 and controls 
  four output pins based on the sensor readings. It sets different combinations
  of the output pins based on the analog sensor value to demonstrate different conditions.

  Last updated: 18-04-2024
*/

int acc = A0;

void setup() {
  Serial.begin(9600);  
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
}

void loop() {
  int a = analogRead(A0);
  Serial.println(a);
  
  if(a < 335) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
  
  if(a > 345) {
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
  }
  
  if(a > 335 && a < 345) {
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
  }
}
