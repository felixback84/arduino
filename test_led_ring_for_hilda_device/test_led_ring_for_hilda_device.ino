//RGB LED PINS SET
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 0 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels

void setup() {
  // put your setup code here, to run once:
  // LED RGB SET
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

}

void loop() {
  // put your main code here, to run repeatedly:
  printLedRGB( 255, 240, 0);
}

// Custom Function - printLedRGB()
void printLedRGB(int red_light_value, int green_light_value, int blue_light_value) {
  
  pixels.clear(); // Set all pixel colors to 'off'

  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(red_light_value, green_light_value, blue_light_value));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop

  } 

}
