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

// The I2C LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);

//const byte analogPin = A1;

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

// Variables used for setting "preferences".
bool isFading = false;
char* isFading_text;
unsigned int fadePeriod = 100;
bool isBlinking = false;
char* isBlinking_text;
unsigned int blinkPeriod = 1000;

LiquidLine welcome_line1(1, 0, "LiquidMenu ", LIQUIDMENU_VERSION);
LiquidLine welcome_line2(1, 1, "Functions ex.");
LiquidScreen welcome_screen(welcome_line1, welcome_line2);

LiquidLine ledTitleLine(6, 0, "LED");
LiquidLine led_line(4, 1, "Level: ", led_level);
LiquidScreen led_screen(ledTitleLine, led_line);

LiquidLine fade_line(0, 0, "Fade - ", isFading_text);
LiquidLine fadePeriod_line(0, 1, "Period: ", fadePeriod, "ms");
LiquidScreen fade_screen(fade_line, fadePeriod_line);

LiquidLine blink_line(0, 0, "Blink - ", isBlinking_text);
LiquidLine blinkPeriod_line(0, 1, "Period: ", blinkPeriod, "ms");
LiquidScreen blink_screen(blink_line, blinkPeriod_line);

LiquidMenu menu(lcd, startingScreen);

// Callback functions
void increase_led_level() {
  if (led_level < 225) {
    led_level += 25;
  } else {
    led_level = 0;
  }
  analogWrite(led, led_level);
}

void decrease_led_level() {
  if (led_level > 25) {
    led_level -= 25;
  } else {
    led_level = 250;
  }
  analogWrite(led, led_level);
}

void fade_switch() {
  led_off();
  if (isFading == true) {
    isFading = false;
    isFading_text = (char*)"OFF";
  } else {
    isFading = true;
    isFading_text = (char*)"ON";
    isBlinking = false;
    isBlinking_text = (char*)"OFF";
  }
}

void increase_fadePeriod() {
  if (fadePeriod < 3000) {
    fadePeriod += 10;
  }
}

void decrease_fadePeriod() {
  if (fadePeriod > 10) {
    fadePeriod -= 10;
  }
}

void blink_switch() {
  led_off();
  if (isBlinking == true) {
    isBlinking = false;
    isBlinking_text = (char*)"OFF";
  } else {
    isBlinking = true;
    isBlinking_text = (char*)"ON";
    isFading = false;
    isFading_text = (char*)"OFF";
  }
}

void increase_blinkPeriod() {
  if (blinkPeriod < 3000) {
    blinkPeriod += 50;
  }
}

void decrease_blinkPeriod() {
  if (blinkPeriod > 50) {
    blinkPeriod -= 50;
  }
}

void led_off() {
  led_level = 0;
  analogWrite(led, led_level);
}

// Checks all the buttons.
void buttonsCheck() {
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

// The fading function.
void fade() {
  static bool goingUp = true;
  if (goingUp) {
    led_level += 25;
  } else {
    led_level -= 25;
  }
  if (led_level > 225) {
    goingUp = false;
    led_level = 250;
  }
  if (led_level < 25 && goingUp == false) {
    goingUp = true;
    led_level = 0;
  }
  analogWrite(led, led_level);
}

// The blinking function.
void blink() {
  static bool blinkState = LOW;
  if (blinkState == LOW) {
    blinkState = HIGH;
    led_level = 255;
  } else {
    blinkState = LOW;
    led_level = 0;
  }
  analogWrite(led, led_level);
}

void setup() {

  Serial.begin(250000);
  //pinMode(analogPin, INPUT);

  // This is the I2C LCD object initialization.
    
  lcd.begin();
  lcd.backlight();

  // Menu initialization.
  menu.init();

  Serial.begin(250000);

  pinMode(led, OUTPUT);

  // The increasing functions are attached with identification of 1.
  /*
   * This function can later be called by pressing the 'UP' button
   * when 'led_line' is focused. If some other line is focused it's
   * corresponding function will be called.
  */
  led_line.attach_function(increase, increase_led_level);
  // The decreasing functions are attached with identification of 2.
  led_line.attach_function(decrease, decrease_led_level);

  // Here the same function is attached with two different identifications.
  // It will be called on 'UP' or 'DOWN' button press.
  fade_line.attach_function(1, fade_switch);
  fade_line.attach_function(2, fade_switch);
  fadePeriod_line.attach_function(increase, increase_fadePeriod);
  fadePeriod_line.attach_function(decrease, decrease_fadePeriod);

  blink_line.attach_function(1, blink_switch);
  blink_line.attach_function(2, blink_switch);
  blinkPeriod_line.attach_function(increase, increase_blinkPeriod);
  blinkPeriod_line.attach_function(decrease, decrease_blinkPeriod);

  menu.add_screen(welcome_screen);
  menu.add_screen(led_screen);
  menu.add_screen(fade_screen);
  menu.add_screen(blink_screen);

  isFading_text = (char*)"OFF";
  isBlinking_text = (char*)"OFF";

  menu.update();
}

void loop() {
  buttonsCheck();

  static unsigned long lastMillis_blink = 0;
  if ((isFading == true) && ((millis() - lastMillis_blink) > fadePeriod)) {
    lastMillis_blink = millis();
    fade();
    menu.update();
  }

  static unsigned long lastMillis_fade = 0;
  if ((isBlinking == true) && ((millis() - lastMillis_fade) > blinkPeriod)) {
    lastMillis_fade = millis();
    blink();
    menu.update();
  }

}
