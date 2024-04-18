/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95/
  Copyright: [@ Vikrant Gupta]

  
  Description: This Arduino sketch transmits a short text message using the VirtualWire library. 
  It reads sensor values from multiple analog pins and sends corresponding messages based on the sensor readings. 
  If it detects rain, it sends a "rain" message. If there is no rain but the soil moisture is high, it sends a "nmoi" message. 
  If the soil moisture is low, it sends a "ymoi" message.
  Last updated: [Date]
*/

// Define analog sensor pins
int sensepin = A0;
int sensepin1 = A1;
int sensepin2 = A2;
int sensepin3 = A3;
int sensepin4 = A4;

int mois;

#include <VirtualWire.h>

void setup() {
  // Initialize the IO and ISR
  pinMode(4, OUTPUT);    // Motor control pin
  digitalWrite(4, LOW);  // Initially turn off the motor
  analogReference(DEFAULT);
  vw_setup(2000);  // Bits per second for VirtualWire
}

void loop() {
  // Check rain sensor reading
  if (analogRead(sensepin1) < 500) {                                                                                                       // If rain is detected
    digitalWrite(4, LOW);                                                                                                                  // Turn off motor
    send("rain");                                                                                                                          // Send "rain" message
  } else {                                                                                                                                 // If no rain
    if (analogRead(sensepin) > 500 && analogRead(sensepin2) > 500 && analogRead(sensepin3) > 500 && analogRead(sensepin4) > 500) {         // If no moisture
      digitalWrite(4, HIGH);                                                                                                               // Turn on motor
      send("nmoi");                                                                                                                        // Send "nmoi" message (no moisture)
    } else if (analogRead(sensepin) < 500 && analogRead(sensepin2) < 500 && analogRead(sensepin3) < 500 && analogRead(sensepin4) < 500) {  // If moisture detected
      digitalWrite(4, LOW);                                                                                                                // Turn off motor
      send("ymoi");                                                                                                                        // Send "ymoi" message (yes moisture)
    }
  }
}

void send(char *message) {
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();  // Wait until the whole message is sent
}
