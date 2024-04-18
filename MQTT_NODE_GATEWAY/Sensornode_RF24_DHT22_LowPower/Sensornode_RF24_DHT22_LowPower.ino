/*
  Author: Vikrant Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  Instagram: https://www.instagram.com/crazyvikku/
  GitHub: https://github.com/vikrantgupta95

  Copyright (c) 2024 Vikrant Gupta

  Description: This Arduino sketch implements a low-power sensor node using the RF24 module and DHT22 sensor.
               The node periodically measures temperature, humidity, and battery voltage, then transmits the data wirelessly using RF24.
*/

#include <avr/sleep.h>
#include <avr/wdt.h>
#include <RF24.h>
#include <dht.h>

#define CE_PIN   5
#define CSN_PIN  4
#define DHT22_PIN 3

RF24 radio(CE_PIN, CSN_PIN);
dht DHT;

const byte address[6] = "00001";
byte addresses[][6] = {"1Node", "000001"};

struct rdata {                  
  char addr[6] = "NODE3"; // Node address
  int hu, te, bt;         // Humidity, temperature, battery voltage
};
rdata r_data;  // Variable of the type rdata (structure)

volatile boolean f_wdt = 1; // Watchdog interrupt flag
int ct = 0; // Counter for sleep cycles

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  setup_watchdog(6);
}

void loop() {
  if (f_wdt == 1 && ct > 1) {
    f_wdt = 0;
    int chk = DHT.read22(DHT22_PIN);
    float t = DHT.temperature * 100;
    float h = DHT.humidity * 100;
    radio.stopListening();
    int k = readVcc();
    r_data.te = t;
    r_data.hu = h;
    r_data.bt = k;
    radio.powerUp();
    radio.write(&r_data, sizeof(r_data));
    radio.powerDown();
    system_sleep();
    ct = 0;
  } else {
    system_sleep();
    ct++;
  }
}

void system_sleep() {
  cbi(ADCSRA, ADEN);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_bod_disable();
  sleep_enable();
  sleep_mode();
  sleep_disable();
  sbi(ADCSRA, ADEN);
}

void setup_watchdog(int ii) {
  byte bb;
  int ww;
  if (ii > 9) ii = 9;
  bb = ii & 7;
  if (ii > 7) bb |= (1 << 5);
  bb |= (1 << WDCE);
  ww = bb;
  MCUSR &= ~(1 << WDRF);
  WDTCR |= (1 << WDCE) | (1 << WDE);
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}

ISR(WDT_vect) {
  f_wdt = 1;
}

long readVcc() {
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = _BV(MUX3) | _BV(MUX2);
#else
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif

  delay(2);
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC));
  uint8_t low = ADCL;
  uint8_t high = ADCH;
  long result = (high << 8) | low;
  result = (1125300L / result);
  return result;
}
