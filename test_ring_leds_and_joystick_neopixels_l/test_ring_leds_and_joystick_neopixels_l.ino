//BOARD
// MKR 1010 WIFI

//RING LEDS PINS
//5V 5V
//GND GND
//D1 D1
//D0 -

//JOYSTICK
//5V 5V
//GND GND
//VRX A1
//VRY A0
//SW A2

//neopixels library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        1 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels


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

  //led ring setup
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

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
  Serial.println(); 
  delay (100);

  //leds

  pixels.clear(); 
  for(int i=0; i<NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(x, y, z));

    pixels.show(); 
    delay(DELAYVAL); 
  }
}
