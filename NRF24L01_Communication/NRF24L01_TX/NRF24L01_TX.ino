/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95/

  Copyright (c) 2024 Vikrant Gupta

  Description: This code utilizes an NRF24L01 module along with a DHT11 sensor to transmit temperature 
  and humidity data wirelessly using Arduino. The NRF24L01 module is configured in a 3-pin setup, where 
  both CE and CSN pins are connected to the same pin. The code initializes the NRF24L01 module, sets up
  the address for communication, and continuously reads temperature and humidity data from the DHT11
  sensor. Once the data is read, it is transmitted wirelessly using the NRF24L01 module.


  Last updated: 2024-03-25
*/


#define CE_PIN 5     // Define CE pin
#define CSN_PIN 4    // Define CSN pin (same pin used for CE and CSN in 3-pin configuration)
#define DHT11_PIN 3  // Define pin for DHT11 sensor

#include <RF24.h>  // Include RF24 library
#include <dht.h>   // Include DHT library

RF24 radio(CE_PIN, CSN_PIN);                  // Initialize NRF24L01 module
const byte address[6] = "00001";              // Address of this node
byte addresses[][6] = { "1Node", "000001" };  // Address of this node

// Struct for sending measured data
struct rdata {
  char addr[6] = "1NODE";  // Default address
  int hu, te;              // Humidity and temperature variables
};
rdata r_data;

dht DHT;     // Initialize DHT sensor
float h, t;  // Humidity and temperature variables

void setup() {
  radio.begin();                   // Start up the NRF24L01 module
  radio.openWritingPipe(address);  // Open pipe for transmitting operation
  radio.stopListening();           // Stop listening for incoming data
}

void loop() {
  int chk = DHT.read11(DHT11_PIN);      // Read data from DHT11 sensor
  t = DHT.temperature;                  // Store temperature data
  h = DHT.humidity;                     // Store humidity data
  radio.stopListening();                // Stop listening for incoming data
  r_data.hu = h;                        // Assign humidity data to struct variable
  r_data.te = t;                        // Assign temperature data to struct variable
  radio.write(&r_data, sizeof(rdata));  // Transmit data wirelessly
  delay(3000);                          // Delay for stability
}