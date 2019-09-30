
//fastled last library
#include <FastLED.h>
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

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

//joystick pins
int JoyStick_X = A0; // x
int JoyStick_Y = A1; // y
int JoyStick_Z = A2; // button

void setup() {

  //joystick setup
  
  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);
  pinMode (JoyStick_Z, INPUT);
  // serial begin
  Serial.begin (9600); // 9600 bps

  //fastled setup

  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  
}

void loop() {

  //joystick
  
  //joystick variables
  int x, y, z;
  x = analogRead (JoyStick_X);
  y = analogRead (JoyStick_Y);
  z = analogRead (JoyStick_Z);
  
  // Serial print datos joystick:
  Serial.print(" X axis = ");
  Serial.print (x, DEC);
  Serial.print("       Y axis = ");
  Serial.print (y, DEC);
  Serial.print("       Button  value = ");
  Serial.print (z, DEC);
  delay(100);
  if(z == 0){
  Serial.print(" BUTTON is PRESSED");
  delay(1000);
  }
  Serial.println(); // start a new line
  delay (100);
  // insert a delay to keep the framerate modest
  //FastLED.delay(1000/FRAMES_PER_SECOND);

  setRGB(x, y, z);
}

  //This function will update the RGB LED when called
  void setRGB(int rLed, int gLed, int bLed)
  {
    //leds ring
    for(int i = 0; i < 24; i++) {
      leds[i].setRGB( rLed, gLed, bLed);
      FastLED.show();  
    } 
  }

  void sinelon()
  {
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy( leds, NUM_LEDS, 20);
    int pos = beatsin16( 13, 0, NUM_LEDS-1 );
    leds[pos] += CHSV( gHue, 255, 192);
  }
