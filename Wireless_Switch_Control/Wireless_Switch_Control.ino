/*
  Receiver data pin to Arduino pin 12
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This code receives messages wirelessly using the VirtualWire library. It controls different buzzers based on the 
  received messages, simulating actions related to different objects. It sets specific buzzers on and off depending 
  on the received message.

  Last updated: 18-04-2024
*/

#include <VirtualWire.h>

byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

void setup() {
  Serial.begin(9600);
  Serial.println("Device is ready");
  
  pinMode(5, OUTPUT); // buzzer 1
  pinMode(4, OUTPUT); // buzzer 2
  pinMode(3, OUTPUT); // buzzer 3
  pinMode(2, OUTPUT); // buzzer 4
  
  digitalWrite(5, LOW);  
  digitalWrite(4, LOW);
  digitalWrite(3, LOW); 
  digitalWrite(2, LOW);

  // Initialize the IO and ISR
  vw_set_rx_pin(12);
  vw_setup(2000); // Bits per sec
  vw_rx_start(); // Start the receiver
}

void loop() {
  if (vw_get_message(message, &messageLength)) { // Non-blocking
    Serial.print("Received: ");
    for (int i = 0; i < messageLength; i++) {
      Serial.write(message[i]);
    }
    Serial.println();

    if (message[0] == 'o') { // shoes
      Serial.println("shoes");
      digitalWrite(5, HIGH);  
      digitalWrite(4, LOW); 
      digitalWrite(3, LOW);  
      digitalWrite(2, LOW); 
      delay(500);
      digitalWrite(5, HIGH);  
      digitalWrite(4, LOW); 
      digitalWrite(3, LOW);  
      digitalWrite(2, LOW); 
      delay(500);
      digitalWrite(5, LOW);  
      digitalWrite(4, LOW); 
      digitalWrite(3, LOW);  
      digitalWrite(2, LOW); 
    } else if (message[0] == 'p') { // almira
      Serial.println("almira");
      digitalWrite(5, LOW);  
      digitalWrite(4, HIGH); 
      digitalWrite(3, LOW);  
      digitalWrite(2, LOW); 
      delay(1000);
      digitalWrite(5, LOW);  
      digitalWrite(4, HIGH); 
      digitalWrite(3, LOW);  
      digitalWrite(2, LOW); 
      delay(1000);
      digitalWrite(5, LOW);  
      digitalWrite(4, LOW); 
      digitalWrite(3, LOW);  
      digitalWrite(2, LOW); 
    } else if (message[0] == 't') { // water-jug
      Serial.println("water-jug");
      digitalWrite(5, LOW);  
      digitalWrite(4, LOW); 
      digitalWrite(3, HIGH);  
      digitalWrite(2, LOW);
      delay(1500);
      digitalWrite(5, LOW);  
      digitalWrite(4, LOW); 
      digitalWrite(3, HIGH);  
      digitalWrite(2, LOW); 
      delay(1500);
      digitalWrite(5, LOW);  
      digitalWrite(4, LOW); 
      digitalWrite(3, LOW);  
      digitalWrite(2, LOW); 
    } else if (message[0] == 'f') { // switch-board
      Serial.println("switch-board");
      digitalWrite(5, LOW);
      digitalWrite(4, LOW); 
      digitalWrite(3, LOW); 
      digitalWrite(2, HIGH);
      delay(2000);
      digitalWrite(5, LOW);  
      digitalWrite(4, LOW); 
      digitalWrite(3, LOW);  
      digitalWrite(2, HIGH); 
      delay(2000); 
      digitalWrite(5, LOW);  
      digitalWrite(4, LOW); 
      digitalWrite(3, LOW);  
      digitalWrite(2, LOW); 
    }
  }
}
