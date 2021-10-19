/*
 * VSM (Virtual Scoring Machine) repeater light LED controller for Arduino
 * VSM automatically detects and utilizes the DLP-IOR4 for turning off and on repeater lights
 * 
 * Requires: 
 *   LED strip
 *   DLP-IOR4 - 4 channel USB relay.
 * 
 * Instructions:
 * - Change NUM_LEDS to the number of LEDs you have.
 * - In the FastLED.addLeds command, change your LED driver if it is not WS2812. Most LED strips are WS2812 so that is default.
 * 
 * On the DLP-IOR4:
 * The common terminal is the middle channel on each relay (number label), 5v power needs to go here on all 4 relays (Arduino 5v is fine).
 * The left (letter A label) terminal is the "normally open" (NO) circuit. 
 * The right (letter B label) terminal is the "normally closed" (NC) circuit.
 * 
 * B terminal for relay 1 to pin 2 on Arduino.
 *   Attach a pull down resistor (a resistor from GND into the circuit with terminal B to the Arduino.)
 * B terminal for relay 2 to pin 3 on Arduino.
 *   Attach pull down resistor.
 * B terminal for relay 3 to pin 4 on Arduino.
 *   Attach pull down resistor.
 * B terminal for relay 4 to pin 5 on Arduino.
 *   Attach pull down resistor.
 *   
 * Vehemont 5.28.21
 * 
 */

#include <FastLED.h>

const int DATA_LEFT = 7; // LED DIN / Data in pin for FOTL
const int DATA_RIGHT = 6; // LED DIN / Data in pin for FOTR


const int LEFT_ON = 5; // 4; // Relay 1 is FOTL on target 2
const int RIGHT_ON = 4; // 5; // Relay 2 is FOTR on target 3 
const int RIGHT_OFF = 3; // 2; // Relay 3 is FOTR off target 4
const int LEFT_OFF = 2;// 3;  // Relay 4 is FOTL off target 5

const int NUM_LEDS = 64; // Number of LEDs in your LED strip/matrix

const int BRIGHTNESS = 50;


CRGB left[NUM_LEDS]; // FOTL LED array
CRGB right[NUM_LEDS]; // FOTR LED array

void setup() {
  // Initialize the pins with built in pull up
  // Initialize FastLED arrays named left (FOTL) and right (FOTR)
  pinMode(LEFT_ON, INPUT_PULLUP); 
  pinMode(LEFT_OFF, INPUT_PULLUP); 
  pinMode(RIGHT_ON, INPUT_PULLUP); 
  pinMode(RIGHT_OFF, INPUT_PULLUP); 
  FastLED.addLeds<WS2812, DATA_LEFT>(left, NUM_LEDS);
  FastLED.addLeds<WS2812, DATA_RIGHT>(right, NUM_LEDS);
  //FastLED.setBrightness(BRIGHTNESS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500); 
}

void loop() {
  
  // FOTL on target and off target lights
  if (digitalRead(LEFT_ON) == HIGH){
    // If LEFT_ON target pin is on, make the left LEDs red
    fill_solid(left, NUM_LEDS, CRGB::Green);
  }
  else if (digitalRead(LEFT_OFF) == HIGH){
    // If LEFT_OFF target pin is on, make the left LEDs white
    fill_solid(left, NUM_LEDS, CRGB::White);
  }
  else if (left)  {
    // If neither of the above are true and the FOTL LEDs are on then turn them off
    fill_solid(left, NUM_LEDS, CRGB::Black);
  }


  // FOTR on target and off target lights
  if (digitalRead(RIGHT_ON) == HIGH){
    // If RIGHT_ON target pin is on, make the left LEDs green
    fill_solid(right, NUM_LEDS, CRGB::Red);
  }
  else if (digitalRead(RIGHT_OFF) == HIGH){
    // If RIGHT_OFF target pin is on, make the left LEDs white
    fill_solid(right, NUM_LEDS, CRGB::White);
  }
  else if (right)  {
    // If neither of the above are true and the FOTR LEDs are on then turn them off
    fill_solid(right, NUM_LEDS, CRGB::Black);
  }
  
  FastLED.show(); // Send the changes to the LEDs
 
}
