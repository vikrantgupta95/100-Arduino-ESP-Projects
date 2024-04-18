/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  GitHub: https://github.com/vikrantgupta95
  
  Description:
 
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the PubSubClient library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages it receives.
    NB - it assumes the received payloads are strings, not binary.
  - If the first character of the topic "inTopic" is a '1', switch ON the ESP Led, else switch it off.

 It will reconnect to the server if the connection is lost using a blocking reconnect function.
 See the 'mqtt_reconnect_nonblocking' example for how to achieve the same result without blocking the main loop.

 To install the ESP8266 board (using Arduino 1.6.4+):
  - Add the following 3rd-party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266
  - Select your ESP8266 in "Tools -> Board"

  
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

// Pin configuration for SoftwareSerial
SoftwareSerial swSer(12, 14, false, 256);  // RX, TX
const char* ssid = "Icreate_Campus";
const char* password = "nxtGen@005";
const char* mqtt_server = "192.168.12.18";

WiFiClient espClient;
PubSubClient client(espClient);
String inputString = "";
String topic = "";
String tem, hum, bt;

// Function prototypes
void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void trig_call();
void read_sms();
void send_sms(String st);
void gpss();

void setup() {
  // Initialize Serial ports and pins
  swSer.begin(115200);
  inputString.reserve(200);
  pinMode(BUILTIN_LED, OUTPUT);  // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);

  // Setup Wi-Fi connection and MQTT client
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(50);
  // Connect to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  delay(9000);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Process received MQTT messages
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on/off the LED based on the received payload
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);  // Turn the LED on
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off
  }
}

void reconnect() {
  // Reconnect to MQTT server
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ADMININ")) {
      Serial.println("connected");

      // Subscribe to MQTT topics
      client.subscribe("ADMININ/LIGHT");
      client.subscribe("ADMININ/AC");
      client.subscribe("ADMININ/AC");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  // Ensure MQTT client is connected
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Process incoming data from SoftwareSerial
  if (swSer.available() > 0) {
    inputString = swSer.readString();
    int hash = inputString.indexOf('#') + 1;
    int semic = inputString.indexOf(';') + 1;
    int coma = inputString.indexOf(',') + 1;
    int dash = inputString.indexOf('-') + 1;
    topic = inputString.substring(0, hash - 1);

    String ttef = topic, thuf = topic, tbtf = topic;
    ttef += "/TE";
    thuf += "/HU";
    tbtf += "/BT";
    char tte[ttef.length() + 1], thu[thuf.length() + 1], tbt[tbtf.length() + 1];
    ttef.toCharArray(tte, ttef.length() + 1);
    thuf.toCharArray(thu, thuf.length() + 1);
    tbtf.toCharArray(tbt, tbtf.length() + 1);
    tem = inputString.substring(hash, semic);
    hum = inputString.substring(semic, coma);
    bt = inputString.substring(coma, dash);
    char mssg[5];
    tem.toCharArray(mssg, 5);
    client.publish(tte, mssg);

    hum.toCharArray(mssg, 5);
    client.publish(thu, mssg);

    bt.toCharArray(mssg, 5);
    client.publish(tbt, mssg);

    Serial.flush();
    inputString = "";
    Serial.flush();
