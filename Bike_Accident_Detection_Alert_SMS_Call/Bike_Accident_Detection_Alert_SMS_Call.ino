/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  GitHub: https://github.com/vikrantgupta95

  Description:
  This Arduino sketch implements a GSM-based SMS and call functionality. It monitors for incoming SMS messages and DTMF tones. If a specific DTMF tone is detected, it triggers an action without sending an SMS. If no SMS is received within a certain time, it sends an SMS containing GPS coordinates. It also allows for reading and storing phone numbers from incoming SMS messages using EEPROM.

  Name: Bike_Accident_Detection_SMS_Call
*/

#include <SoftwareSerial.h>
#include <EEPROM.h>

SoftwareSerial mySerial(10, 11); // Define a SoftwareSerial object for communication with GSM module
unsigned long time1 = 30000, time2 = 60000, tpr = 0, tpr1 = 0; // Time intervals for SMS and GPS functionalities
char i[11], i2[11]; // Arrays to store phone numbers

byte flg = 0; // Flag to determine if an action has been triggered

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  mySerial.begin(9600);

  // Set pin modes and initial states
  pinMode(7, OUTPUT);
  digitalWrite(7, 1);

  // Read phone numbers from EEPROM
  for (int k2 = 11; k2 < 22; k2++)
    i2[k2 - 11] = EEPROM.read(k2);
  Serial.print(String(i2));

  // Initialize GSM module
  digitalWrite(7, 0);
  delay(5000);
  digitalWrite(7, 1);
  mySerial.println("AT");
  delay(1000);
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+DDET=1,5,0");
  delay(1000);
  if (mySerial.available())
    mySerial.readString();
}

void loop() {
  // Check for incoming messages or DTMF tones
  if (mySerial.available()) {
    String k = mySerial.readStringUntil('\n');
    Serial.println(k);
    if (k.startsWith("+CMTI"))
      read_sms(); // Process incoming SMS
    if (k.startsWith("+DTMF: 1")) {
      flg = 1; // Set flag if DTMF tone is detected
      Serial.println("success bass 3.0 no sms trigger");
    }
  }

  // Check time intervals for SMS and GPS functionalities
  if (millis() - tpr == time1) {
    read_sms(); // Process incoming SMS
    trig_call(); // Trigger a call
    Serial.println("sms donr");
  }

  if (millis() - tpr1 == time2 && flg == 0) {
    Serial.println("success bass 3.0 sms trigger");
    gpss(); // Get GPS coordinates and send SMS
    flg = 1;
  }

  // Forward serial data between Arduino and GSM module
  if (Serial.available()) {
    while (Serial.available()) {
      mySerial.write(Serial.read());
    }
    mySerial.println();
  }
}

// Function to trigger a call
void trig_call() {
  // Read phone number from EEPROM
  for (int k1 = 0; k1 < 11; k1++)
    i[k1] = EEPROM.read(k1);
  Serial.println(String(i));

  // Initiate a call to the stored phone number
  String cl = "ATD " + String(i) + ";";
  Serial.print(cl);
  mySerial.println(cl);
}

// Function to read incoming SMS messages
void read_sms() {
  Serial.println("SMS IN");

  // Request GSM module to read unread SMS messages
  mySerial.println("AT+CMGL=\"REC UNREAD\"");
  while (!mySerial.available());
  while (mySerial.available()) {
    String a = mySerial.readStringUntil('\n');
    Serial.println(a);
    if (a.startsWith("ctlm")) { // Check for control messages
      // Extract and store phone numbers from SMS
      String n1 = a.substring(4, 14);
      String n2 = a.substring(14, 24);
      char nn1[11], nn2[11];
      n1.toCharArray(nn1, 11);
      n2.toCharArray(nn2, 11);
      for (int c1 = 0; c1 < 11; c1++)
        EEPROM.write(c1, nn1[c1]);
      for (int c2 = 11; c2 < 22; c2++)
        EEPROM.write(c2, nn2[c2 - 11]);
    }
  }
  Serial.println("DONE");
}

// Function to send SMS containing GPS coordinates
void send_sms(String st) {
  // Read phone number from EEPROM
  for (int k2 = 11; k2 < 22; k2++)
    i2[k2 - 11] = EEPROM.read(k2);
  Serial.println(String(i2));

  // Format SMS message and send to stored phone number
  mySerial.println("AT+CMGS=\"+91" + String(i2) + "\"\r");
  delay(1000);
  mySerial.println(st);
  delay(100);
  mySerial.println((char)26); // Send CTRL+Z to indicate end of message
  delay(1000);
  Serial.println(st);
}

// Function to retrieve GPS coordinates and send SMS
void gpss() {
  // Power on GPS module
  mySerial.println("AT+CGPSPWR=1");
  delay(3000);
  if (mySerial.available())
    mySerial.readString();
  mySerial.flush();
  mySerial.println("AT+CGPSSTATUS?");
  delay(1000);
  while (mySerial.available()) {
    String k = mySerial.readStringUntil('\n');
    Serial.println(k);
    if (k.startsWith("+CGPSSTATUS: Location 2") || k.startsWith("+CGPSSTATUS: Location 3")) {
      mySerial.println("AT+CGPSINF=0");
      while (!mySerial.available());
      while (mySerial.available()) {
        String k1 = mySerial.readStringUntil('+');
        Serial.println(k1);
        if (k1.startsWith("CGPSINF:"))
          send_sms(k1); // Send SMS with GPS coordinates
      }
    }
  }
}
