// BOARD 
// UNO

// PROTOCOL
// I2C

// LCD PINS
// VCC 5V
// GND GND
// SDA A4
// SCL A5

// LED PINS
// ANODO ANTES RES (ROJO,NARANJA,PURPURA,DORADO) PARA D6
// CATODO GND

// DHT PINS
// CATODO GND 
// ANODO 5V
// DATA PIN D11

// PUSH BUTTON UP
// CATODO GND 
// ANODO A1

// PUSH BUTTON DOWN
// CATODO GND 
// ANODO D7

// PUSH BUTTON LEFT
// CATODO GND 
// ANODO D8

// PUSH BUTTON RIGHT
// CATODO GND 
// ANODO D9

// PUSH BUTTON ENTER
// CATODO GND 
// ANODO D10



#include <Wire.h>
// The I2C LCD library
#include <LiquidCrystal_I2C.h>
// The menu wrapper library
#include <LiquidMenu.h>
#include "Button.h"

//TEMP SENSOR
#include "DHT.h"

//TEMP SENSOR KIND & PIN
#define DHTPIN 11
#define DHTTYPE DHT22

//SENSOR TEMP SET
DHT dht(DHTPIN, DHTTYPE);

// The I2C LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);

// This variable can be passed to the LiquidMenu object to set the starting screen.
const byte startingScreen = 1;

// Button objects instantiation
/*
 * The Button class is not a part of the LiquidMenu library. The first
 * parameter is the button's pin, the second enables or disables the
 * internal pullup resistor (not required) and the third is the debounce
 * time (not required).
 */
 
const bool pullup = true;
Button left(A0, pullup);
Button right(7, pullup);
Button up(8, pullup);
Button down(9, pullup);
Button enter(10, pullup);

/*
 * An enumerator can be used for the callback functions. It sets the number
 * for similar functions. Later when a function is attached it can be passed
 * with this enum rather than a magic number.
 */
// There are two types of functions for this example, one that increases some
// value and one that decreases it.
enum FunctionTypes {
  increase = 1,
  decrease = 2,
};

// These are the pin definitions and variables for their PWM state.
const byte led = 6;
byte led_level = 0;

//Var for temp device

float tempDevice = 0;
float t;
float h;

// Scroll menu: pain parts
LiquidLine line1(0, 0, "Hilda Toys");
LiquidLine line2(0, 0, "Pain level");
LiquidLine line3(0, 0, "Pain location");
LiquidLine line4(0, 0, "Temp device");
LiquidLine line5(0, 0, "Sync data");
LiquidScreen screen;

// Pain led level sceen
LiquidLine ledTitleLine(0, 0, "Pain level");
LiquidLine led_line(0, 1, "Cualify: ", led_level);
LiquidScreen led_screen(ledTitleLine, led_line);

// Welcome screen
LiquidLine pain_line_1(0, 0, "Pain location ");
LiquidLine pain_line_2(0, 1, "Where: ");
LiquidScreen pain_screen(pain_line_1, pain_line_2);

// Temp screen
LiquidLine temp_line_1(0, 0, "Temp device");
LiquidLine temp_line_2(0, 1, "Celsius: ", tempDevice);
LiquidScreen temp_screen(temp_line_1, temp_line_2);

// sync screen
LiquidLine sync_line_1(0, 0, "Sync data");
LiquidLine sync_line_2(0, 1, "Sending");
LiquidScreen sync_screen(sync_line_1, sync_line_2);

// LCD Setup
LiquidMenu menu(lcd, startingScreen);

// Callback functions
// Pain led level

void increase_led_level() {
  if (led_level < 7) {
    led_level += 1;
  } else {
    led_level = 1;
  }
  switch (led_level) {
    
    case 0:
    analogWrite(led, 0);
    break;
    case 1:
    analogWrite(led, 35);
    break;
    case 2:
    analogWrite(led, 70);
    break;
    case 3:
    analogWrite(led, 105);
    break;
    case 4:
    analogWrite(led, 140);
    break;
    case 5:
    analogWrite(led, 175);
    break;
    case 6:
    analogWrite(led, 210);
    break;
    case 7:
    analogWrite(led, 245);
    break;
  }
  
}

void decrease_led_level() {
  if (led_level > 1) {
    led_level -= 1;
  } else {
    led_level = 7;
  }
  switch (led_level) {
    
    case 0:
    analogWrite(led, 0);
    break;
    case 1:
    analogWrite(led, 35);
    break;
    case 2:
    analogWrite(led, 70);
    break;
    case 3:
    analogWrite(led, 105);
    break;
    case 4:
    analogWrite(led, 140);
    break;
    case 5:
    analogWrite(led, 175);
    break;
    case 6:
    analogWrite(led, 210);
    break;
    case 7:
    analogWrite(led, 245);
    break;
    
  }
  
}

//Scrolling menu
// Used for attaching something to the lines, to make them focusable.

void blankFunction1() {
  menu.add_screen(led_screen);
  delay(5000);
    menu.update();
}

void blankFunction2() {
  menu.add_screen(pain_screen);
  delay(5000);
    menu.update();
}

void blankFunction3() {
  menu.add_screen(temp_screen);
  delay(5000);
    menu.update();
}

void blankFunction4() {
  menu.add_screen(sync_screen);
  delay(5000);
    menu.update();
    
}

//Temp menu
void temp_device(){

  h = dht.readHumidity();
  t = dht.readTemperature();
     
  tempDevice = dht.computeHeatIndex(t,h, false);
  
}

// Checks all the buttons.
void buttons_check() {
  if (right.check() == LOW) {
    menu.next_screen();
  }
  if (left.check() == LOW) {
    menu.previous_screen();
  }
  if (up.check() == LOW) {
    // Calls the function identified with
    // increase or 1 for the focused line.
    menu.call_function(increase);
  }
  if (down.check() == LOW) {
    menu.call_function(decrease);
  }
  if (enter.check() == LOW) {
    // Switches focus to the next line.
    menu.switch_focus();
  }
}

void setup() {

  Serial.begin(250000);

  // SENSOR DHT BEGIN
  dht.begin();

  // Print in the serial Monitor
  Serial.println(tempDevice);
  //delay(500); // we read signal every 500ms

  // This is the I2C LCD object initialization.
  lcd.begin();
  lcd.backlight();

  // Menu initialization.
  menu.init();

  // led set
  pinMode(led, OUTPUT);

  // Add more "lines" than the display has. The extra will be scrolled.
  screen.add_line(line1);
  screen.add_line(line2);
  screen.add_line(line3);
  screen.add_line(line4);
  screen.add_line(line5);
  
  // Menu callbacks
  
  //Pain led level menu
  led_line.attach_function(increase, increase_led_level);
  led_line.attach_function(decrease, decrease_led_level);

  // Scrolling menu: pain parts
  // Attaching a function to the lines is required for scrolling to work.

  line2.attach_function(1, blankFunction1);
  line3.attach_function(1, blankFunction2);
  line4.attach_function(1, blankFunction3);
  line5.attach_function(1, blankFunction4);

  // Temp menu
  //temp_line_2.attach_function(1, led_off);

  //  Items for scrolling menu
  screen.set_displayLineCount(2);
  
  // Menu inscriptions
  
  
  menu.add_screen(screen);
  

  // Set the number of decimal places for a "line".
  //line5.set_decimalPlaces(5);

  menu.update();
}

void loop() {

  // Buttons check initial set
  
  buttons_check();

  if ( tempDevice = 1  ) {
    temp_device();
    
  }
  
 }
  

  
