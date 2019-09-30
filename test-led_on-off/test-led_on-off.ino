#include <FastLED.h>

//led ring pins
#define DATA_PIN    3
//#define CLK_PIN   4

//led ring settings
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    24
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          100
#define FRAMES_PER_SECOND  120


void setup() {
  
  LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB( 255, 68, 221);
      FastLED.show(); 
      delay(10); 
    } 

}
