#include <APA102.h>
#include <ADCTouch.h>

// Define which pins to use.
const uint8_t dataPin = 0;
const uint8_t clockPin = 2;

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

// Set the number of LEDs to control.
const uint16_t ledCount = 2;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[ledCount];

// Set the brightness to use (the maximum is 31).
const uint8_t brightness = 10;

int ref0, ref1;     //reference values to remove offset


void setup() {
  // put your setup code here, to run once:
  colors[0] = rgb_color(0,255,0); //default to green
  colors[1] = rgb_color(0,255,0); //default to green

  ref0 = ADCTouch.read(A3, 500);    //create reference values to 
  ref1 = ADCTouch.read(A2, 500);    //account for the capacitance of the pad (500 samples)
}

void loop() {
  // put your main code here, to run repeatedly:
  int value0 = ADCTouch.read(A3); //read ADC value (default 100 samples)
  int value1 = ADCTouch.read(A2); //read ADC value (default 100 samples)
  value0 -= ref0; //remove offset
  value1 -= ref1; //remove offset

  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  
  if(value0 > 40){ //if first pin is touched
    r=255; //set LED color to red
  } else {
    g=255; //set LED color to green
  }

  if(value1 > 10){ //if second pin is touched
    b=255; //set LED color to blue
    g=0; //turn off green LED from previous if statement
  }

  colors[0] = rgb_color(r,g,b); //set first LED color
  colors[1] = rgb_color(r,g,b); //set second LED color
  ledStrip.write(colors,ledCount,brightness); //push colors to LEDs

}
