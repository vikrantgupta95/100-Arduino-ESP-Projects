/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Copyright (c) 2024 Vikrant Gupta

  Description:

  This code utilizes the ESP8266WiFi library along with the BlynkSimpleEsp8266 library to establish a connection between 
  an ESP8266-based microcontroller and the Blynk IoT platform. It allows the microcontroller to communicate with the Blynk 
  app through Wi-Fi, enabling remote control and monitoring of connected devices or sensors. The code initializes Wi-Fi 
  credentials and Blynk authentication token, sets up serial communication for debugging, and continuously runs the Blynk 
  loop to handle incoming and outgoing data.

  Last updated: 2024-03-25
*/


//#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YOUR AUTH TOKEN";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YOUR SSID";
char pass[] = "YOUR PASSWORD";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}