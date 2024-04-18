/*
  Author: Vikrant_Gupta
  Email: vikrantgupta95@gmail.com
  LinkedIn: https://www.linkedin.com/in/vikrantgupta95/
  GitHub: https://github.com/vikrantgupta95


  Author: [Author's Name]
  Description:
  This code controls multiple servo motors representing fingers of a robotic hand. The servos are connected to the Arduino board,
  and each servo corresponds to a specific finger: pinkie, ring, middle, index, and thumb. The code defines logic states for each
  finger to control their movement ranges. It listens for input from the serial monitor to trigger predefined movements of the fingers.
*/

// Include the Servo library
#include <Servo>

// Define servomotors
Servo pinkie;
Servo ring;
Servo middle;
Servo index;
Servo thumb;

// Logic states for each finger
int pinkieL = 20;   // Lower position for pinkie
int pinkieH = 180;  // Higher position for pinkie
int ringL = 30;     // Lower position for ring finger
int ringH = 180;    // Higher position for ring finger
int middleL = 120;  // Lower position for middle finger
int middleH = 0;    // Higher position for middle finger
int indexL = 15;    // Lower position for index finger
int indexH = 180;   // Higher position for index finger
int thumbL = 140;   // Lower position for thumb
int thumbH = 0;     // Higher position for thumb

// Define variable to store serial input
char z;

void setup() {
  // Attach servo motors to respective pins
  pinkie.attach(11);
  ring.attach(10);
  middle.attach(9);
  index.attach(6);
  thumb.attach(5);
  
  // Begin serial communication
  Serial.begin(9600);
}

void loop(){
  // Check if data is available on serial port
  if(Serial.available() > 0){
    // Read the incoming character
    z = Serial.read();
  }
  
  // Perform actions based on the received character
  if(z == 'a'){
    // Open all fingers
    allopened();
  }
  else if(z == 's'){
    // Close all fingers
    allclosed();
  }
  else if(z == 'd'){
    // Move index and thumb
    indexthumb();
  }
}

// Function to close all fingers
void allclosed(){
  pinkie.write(pinkieH);
  ring.write(ringH);
  middle.write(middleH);
  index.write(indexH);
  thumb.write(thumbH);
}
  
// Function to open all fingers
void allopened(){
  pinkie.write(pinkieL);
  ring.write(ringL);
  middle.write(middleL);
  index.write(indexL);
  thumb.write(thumbL);
}

// Function to move index and thumb
void indexthumb(){
  pinkie.write(pinkieL);
  ring.write(ringL);
  middle.write(middleL);
  index.write(indexH);
  thumb.write(thumbH);
}
