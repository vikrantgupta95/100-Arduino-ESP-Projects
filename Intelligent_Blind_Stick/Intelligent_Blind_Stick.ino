/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95/
  Copyright: [@ Vikrant Gupta]

  Description: This Arduino code implements a sensor-based system to detect objects, measure light intensity,
  and respond to remote control signals. It uses an ultrasonic sensor to detect objects, a light sensor to measure
  ambient light intensity, and an infrared remote control sensor to receive remote commands. When an object is detected
  too close, it triggers an alert and activates an alarm. It also reacts to variations in light intensity by 
  providing corresponding alerts. 

  Last updated: 26-03-2024
*/

const int trigger = 9;  // Trigger pin of the ultrasonic sensor
const int echo = 10;    // Echo pin of the ultrasonic sensor

long time_taken;
int dist;           // Distance measured by the ultrasonic sensor
int Signal;         // Signal received from the remote control
int Intens;         // Intensity of ambient light
int similar_count;  // Counter for similar remote signals

void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
}

/* Function to calculate distance */
void calculate_distance(int trigger, int echo) {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  time_taken = pulseIn(echo, HIGH);
  dist = time_taken * 0.034 / 2;
  if (dist > 300)
    dist = 300;
}

void loop() {
  calculate_distance(trigger, echo);
  Signal = analogRead(A0);  // Read signal from the remote control sensor
  Intens = analogRead(A1);  // Read light intensity from the light sensor

  // Check if the remote is pressed
  int temp = analogRead(A0);
  similar_count = 0;
  while (Signal == temp) {
    Signal = analogRead(A0);
    similar_count++;
  }

  // If remote is pressed
  if (similar_count < 100) {
    Serial.print(similar_count);
    Serial.println(" Remote Pressed");
    digitalWrite(Buzz, HIGH);
    delay(3000);
    digitalWrite(Buzz, LOW);
  }

  // If light intensity is very dark
  if (Intens < 200) {
    Serial.print(Intens);
    Serial.println(" Bright Light");
    digitalWrite(Buzz, HIGH);
    delay(200);
    digitalWrite(Buzz, LOW);
    delay(200);
    digitalWrite(Buzz, HIGH);
    delay(200);
    digitalWrite(Buzz, LOW);
    delay(200);
    delay(500);
  }

  // If light intensity is very bright
  if (Intens > 800) {
    Serial.print(Intens);
    Serial.println(" Low Light");
    digitalWrite(Buzz, HIGH);
    delay(500);
    digitalWrite(Buzz, LOW);
    delay(500);
    digitalWrite(Buzz, HIGH);
    delay(500);
    digitalWrite(Buzz, LOW);
    delay(500);
  }

  // If an object is detected too close
  if (dist < 30) {
    Serial.print(dist);
    Serial.println(" Object Alert");
    digitalWrite(7, HIGH);  // Activate an alarm or indicator
    digitalWrite(8, LOW);
    delay(1300);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    delay(1000);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    delay(1000);
    for (int i = dist; i > 0; i--)
      delay(10);
  }

  // Print sensor readings
  Serial.print("dist=");
  Serial.println(dist);
  Serial.print("Similar_count=");
  Serial.println(similar_count);
  Serial.print("Intens=");
  Serial.println(Intens);
}
