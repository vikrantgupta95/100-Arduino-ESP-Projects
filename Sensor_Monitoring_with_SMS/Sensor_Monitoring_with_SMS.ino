/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This Arduino sketch monitors sensor inputs and sends SMS alerts based on predefined conditions. It reads data from a DHT11 sensor to measure humidity and temperature, and it also monitors the state of digital pins. If the sensor values or digital inputs meet certain criteria, it sends SMS alerts using AT commands via serial communication.

  Name: Sensor Monitoring with SMS
*/

int timesTosend = 1;
int count1 = 0;
int count = 0;
int a = 0;

#include <dht.h>
#define dht_dpin A0
int i, j;
dht DHT;

void setup() {

  Serial.begin(9600);
  Serial.println("AT+CMGF=1"); //set Serial to text mode
  delay(200);
  delay(500);
  analogReference(DEFAULT);
  delay(700);

  pinMode(A1, INPUT);
  digitalWrite(A1, LOW);

  pinMode(2, INPUT);
  digitalWrite(2, LOW);

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
}

void loop() {

  Serial.println(digitalRead(A1));
  delay(20);
  while (digitalRead(A1) == 1) {
    a++;
    Serial.print("a=");
    Serial.println(a);
    delay(2000);
    while (a == 1) {
      if (digitalRead(A1) == 1) {
        delay(2000);
        digitalWrite(3, HIGH);
        delay(3000);
        digitalWrite(3, LOW);
        a = 0;
      }
    }
  }
  DHT.read11(dht_dpin);

  i = DHT.humidity;
  j = DHT.temperature;
  Serial.print(i);
  Serial.print(" ");
  Serial.println(j);
  delay(100);

  if (digitalRead(2) == 1) {
    count = 0;
    Serial.println("AT+CMGF=1"); //set Serial to text mode
    delay(200);
    delay(500);
    while (count < timesTosend) {
      delay(1500);
      Serial.print("AT+CMGS=\"");
      Serial.print("8057976197");
      Serial.println("\"");
      while (Serial.read() != '>');
      {
        Serial.print("Temp =");
        Serial.println(j);

        //SMS body
        delay(1000);
        //SMS body

        Serial.write(0x1A);  // sends ctrl+z end of message
        Serial.write(0x0D);  // Carriage Return in Hex
        Serial.write(0x0A);  // Line feed in Hex

        //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
        delay(5000);
      }
      count++;

    }
  }
  if (j > 32) {

    Serial.println("AT+CMGF=1"); //set Serial to text mode
    delay(200);
    delay(500);
    while (count1 < timesTosend) {
      delay(1500);
      Serial.print("AT+CMGS=\"");
      Serial.print("8057976197");
      Serial.println("\"");
      while (Serial.read() != '>');
      {
        Serial.print("HIGH TEMP");
        Serial.println(j);

        //SMS body
        delay(1000);
        //SMS body

        Serial.write(0x1A);  // sends ctrl+z end of message
        Serial.write(0x0D);  // Carriage Return in Hex
        Serial.write(0x0A);  // Line feed in Hex

        //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
        delay(5000);
      }

      count1++;
    }
  }
}
