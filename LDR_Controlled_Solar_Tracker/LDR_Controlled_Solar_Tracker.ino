/*
Author: Vikrant_Gupta
Email: vikrantgupta95@gmail.com
LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
GitHub: https://github.com/vikrantgupta95

Description: This code reads data from two LDR sensors and controls LEDs based on the sensor readings. 
It monitors the light intensity detected by each LDR and triggers LED outputs accordingly.
If LDR1 detects low light intensity, it turns on LED connected to pin 5. If LDR2 detects low light intensity,
it turns on LED connected to pin 4.
  
  Last Updated: [18-04-2024]
*/


// Define the analog pins connected to the LDRs
int ldr1 = A0; // Pin connected to LDR1
int ldr2 = A1; // Pin connected to LDR2

// Variables to track LED states
int a = 0;
int b = 0;
int c = 0;

void setup() {
  // Start serial communication
  Serial.begin(9600);
  
  // Set LED pins as outputs and ensure LEDs are initially off
  pinMode(4, OUTPUT); // LED pin for LDR2
  digitalWrite(4, LOW);
  pinMode(5, OUTPUT); // LED pin for LDR1
  digitalWrite(5, LOW);
  
  // Set analog reference to default
  analogReference(DEFAULT);
}

void loop() {
  // Read analog values from LDR sensors and print them to serial monitor
  Serial.print("LDR 1: ");
  int ldrValue1 = analogRead(A0);
  Serial.println(ldrValue1);
  delay(500);
  Serial.print("LDR 2: ");
  int ldrValue2 = analogRead(A1);
  Serial.println(ldrValue2);

  // Control LEDs based on LDR readings
  if (ldrValue2 < 100 && b == 0) {
    // Turn on LED for LDR1 and turn off LED for LDR2
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    delay(2000);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    a = 0;
    b = 1;
    c = 0;
  }
  if (ldrValue1 < 700 && c == 0) {
    // Turn on LED for LDR2 and turn off LED for LDR1
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(2000);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    a = 0;
    b = 0;
    c = 1;
  }
}

