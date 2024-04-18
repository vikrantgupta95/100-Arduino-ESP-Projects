
/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  GitHub: https://github.com/vikrantgupta95


  Description: This Arduino sketch receives data from an nRF24L01 RF transceiver module and forwards it to a serial port.
               It uses the RF24 library for communication. The received data includes temperature, humidity, and battery status.
               The data is then printed on both the Serial monitor and a SoftwareSerial port.
*/

#include <SPI.h>      // Include the SPI Library
#include <nRF24L01.h> // Include the RF24 Library
#include <RF24.h>     // Include the RF24 Header File
#include <SoftwareSerial.h>

// Define pin numbers for the RF module
#define CE_PIN   9
#define CSN_PIN  10

// Define the SoftwareSerial pins for communication with another device
SoftwareSerial mySerial(6, 7); // RX, TX

// Define the address for the RF communication
const byte address[6] = "00001";

// Create an instance of the RF24 class
RF24 radio(CE_PIN, CSN_PIN);

// Define a structure to store the received data
struct rdata {
  char addr[6]; // Address
  int hu;       // Humidity
  int te;       // Temperature
  int bt;       // Battery status
};
rdata r_data;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  mySerial.begin(115200);

  // Initialize RF communication
  radio.begin();
  radio.openReadingPipe(0, address); // Set the reading pipe
  radio.setPALevel(RF24_PA_MAX);     // Set the power amplifier level to maximum
  radio.startListening();

  // Print setup completion message
  Serial.println("Setup complete");
}

void loop() {
  // Check if data is available from the RF module
  if (radio.available()) {
    // Read the data from the RF module
    radio.read(&r_data, sizeof(r_data));

    // Print the received data to the Serial monitor
    Serial.print(String(r_data.addr));
    Serial.print("#");
    Serial.print(r_data.te);
    Serial.print(";");
    Serial.print(r_data.hu);
    Serial.print(",");
    Serial.print(r_data.bt);
    Serial.print("-");
    Serial.println("");

    // Print the received data to the SoftwareSerial port
    mySerial.print(String(r_data.addr));
    mySerial.print("#");
    mySerial.print(r_data.te);
    mySerial.print(";");
    mySerial.print(r_data.hu);
    mySerial.print(",");
    mySerial.print(r_data.bt);
    mySerial.print("-");
    mySerial.print("");

    // Add a delay to avoid flooding the serial port
    delay(1000);
  }
}
