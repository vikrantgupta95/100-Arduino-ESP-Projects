/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Copyright (c) 2024 Vikrant Gupta

  Description: This code establishes communication between two NRF24L01 modules using Arduino. 
  One module serves as a transmitter, sending temperature and humidity data, while the other 
  acts as a receiver, receiving the data and printing it on the serial monitor. The code initializes
  the necessary libraries, sets up the NRF24L01 modules with specific addresses, and continuously 
  listens for incoming data. Once data is received, it is parsed and printed on the serial monitor. 

  Last updated: 2024-03-25
*/

#include <SPI.h>       // Include SPI library
#include <nRF24L01.h>  // Include NRF library
#include <RF24.h>      // Include RF24 header
#include <SoftwareSerial.h>

#define CE_PIN A1                 // Define CE pin
#define CSN_PIN A2                // Define CSN pin
const byte address[6] = "00001";  // Address of this node
//byte address[][6] = {"1Node","000001"};    // Use this line in case of error
byte addresses[][6] = { "1Node", "000001" };  // Address of this node

struct rdata {  // Define structure for received data
  char addr[6];
  int hu, te;
};
rdata r_data;

char outcome;        // Define variable for outcome
byte inxy[2];        // Define byte array for input
String mainst = "";  // Initialize an empty string for unknown purpose

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  //mySerial.begin(115200);
  radio.begin();                      // Initialize NRF module
  radio.openReadingPipe(0, address);  // Open pipe for receiving operation
  //radio.setPALevel(RF24_PA_MAX);
  radio.startListening();         // Start listening for incoming data
  Serial.println("Data Coming");  // Print message indicating data reception is ongoing
}

void loop() {
  if (radio.available()) {                // Check if data is available to read
    radio.read(&r_data, sizeof(r_data));  // Read the data from NRF module

    // Print received data
    Serial.print(String(r_data.addr));
    Serial.print("#");
    Serial.print(r_data.te);
    Serial.print("#");
    Serial.print(r_data.hu);
    Serial.println("");
    delay(1000);  // Delay for stability
  }
}