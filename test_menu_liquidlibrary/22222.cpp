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
#include <EEPROM.h>
#include "Button.h"

//TEMP SENSOR LIBRARIES
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//TEMP SENSOR KIND & PIN
#define DHTPIN 11
#define DHTTYPE DHT22

//SENSOR TEMP SET
DHT_Unified dht(DHTPIN, DHTTYPE);

//LED SETUP
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Vars for temp device
volatile float tempDevice = 0;
uint32_t delayMS;

// Pin definitions and variables for their state.
const byte pin6 = 6;
byte pin6_level = 0;

const byte pinA4 = A4;
byte pinA4_value = 0;

const byte pinA5 = A5;
byte pinA5_value = 0;

// The analog reading sample period in seconds.
// It is later overwritten by it's EEPROM value.
unsigned short sample_period = 2;

// Text used for indication for the save lines.
char* input_saved;
char* output_saved;

const bool pullup = true;
Button left(A0, pullup);
Button right(7, pullup);
Button up(8, pullup);
Button down(9, pullup);
Button enter(10, pullup);


// There are two types of functions for this example, one that increases some
// value and one that decreases it.
enum FunctionTypes {
  increase = 1,
  decrease = 2,
};

// A LiquidLine object can be used more that once.
LiquidLine back_line(11, 1, "/BACK");


LiquidLine welcome_line1(1, 0, "LiquidMenu ", LIQUIDMENU_VERSION);
LiquidLine welcome_line2(1, 1, "Temp:", tempDevice);
LiquidScreen welcome_screen(welcome_line1, welcome_line2);

// These lines direct to other menus.
LiquidLine outputs_line(0, 0, "/Outputs");
LiquidLine inputs_line(0, 1, "/Inputs");
LiquidScreen io_screen(outputs_line, inputs_line);

// This is the first menu.
LiquidMenu main_menu(lcd, welcome_screen, io_screen, 1);


LiquidLine pin6_line(0, 0, "Pin 6: ", pin6_level);
LiquidScreen pin6_screen(pin6_line);

LiquidLine oSave_line(0, 0, "Save", output_saved);
LiquidScreen oSecondary_screen(oSave_line, back_line);

// This is the second menu.
LiquidMenu outputs_menu(lcd, pin6_screen, oSecondary_screen);


LiquidLine pinA4_line(0, 0, "Pin A4: ", pinA4_value);
LiquidLine pinA5_line(0, 1, "Pin A5: ", pinA5_value);
LiquidScreen pinsA4_A5_screen(pinA4_line, pinA5_line);

LiquidLine iSample_line(0, 0, "Sample: ", sample_period, "s");
LiquidLine iSave_line(0, 1, "Save", input_saved);
LiquidScreen iSecondary_screen(iSample_line, iSave_line, back_line);

// And this is the final third menu.
LiquidMenu inputs_menu(lcd, pinsA4_A5_screen, iSecondary_screen);

/*
 * LiquidSystem object combines the LiquidMenu objects to form
 * a menu system. It provides the same functions as LiquidMenu
 * with the addition of add_menu() and change_menu().
 */
LiquidSystem menu_system(main_menu, outputs_menu, inputs_menu);


// Checks all the buttons.
void buttonsCheck() {
  if (right.check() == LOW) {
    menu_system.next_screen();
  }
  if (left.check() == LOW) {
    menu_system.previous_screen();
  }
  if (up.check() == LOW) {
    menu_system.call_function(increase);
  }
  if (down.check() == LOW) {
    menu_system.call_function(decrease);
  }
  if (enter.check() == LOW) {
    menu_system.switch_focus();
  }
}

// Callback function that will be attached to back_line.
void go_back() {
  // This function takes reference to the wanted menu.
  menu_system.change_menu(main_menu);
}

void goto_outputs_menu() {
  menu_system.change_menu(outputs_menu);
}

void goto_inputs_menu() {
  menu_system.change_menu(inputs_menu);
}

void increase_pin6() {
  if (pin6_level < 225) {
    pin6_level += 25;
  } else {
    pin6_level = 250;
  }
  analogWrite(pin6, pin6_level);
  output_saved = (char*)"  ";
}

void decrease_pin6() {
  if (pin6_level > 25) {
    pin6_level -= 25;
  } else {
    pin6_level = 0;
  }
  analogWrite(pin6, pin6_level);
  output_saved = (char*)"  ";
}

void save_input() {
  EEPROM.put(11, sample_period);
  input_saved = (char*)" *";
}

void save_output() {
  EEPROM.put(9, pin6_level);
  output_saved = (char*)" *";
}

void increase_samplePeriod() {
  if (sample_period < 10) {
    sample_period++;
    input_saved = (char*)"  ";
  }
}

void decrease_samplePeriod() {
  if (sample_period > 0) {
    sample_period--;
    input_saved = (char*)"  ";
  }
}

void temp_device() {

  // Delay between measurements.
  sensor_t sensor;
  delayMS = sensor.min_delay / 1000;

  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    tempDevice = event.temperature;
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

}

void setup() {
  Serial.begin(250000);

  pinMode(pin6, OUTPUT);

  // Reads the values recorded in the EEPROM
  EEPROM.get(9, pin6_level);
  EEPROM.get(11, sample_period);
  analogWrite(pin6, pin6_level);

  // dht begin
  dht.begin();

  lcd.begin();
  lcd.backlight();

  back_line.set_focusPosition(Position::LEFT);

  back_line.attach_function(1, go_back);
  back_line.attach_function(2, go_back);

  outputs_line.attach_function(1, goto_outputs_menu);
  outputs_line.attach_function(2, goto_outputs_menu);
  inputs_line.attach_function(1, goto_inputs_menu);
  inputs_line.attach_function(2, goto_inputs_menu);

  pin6_line.attach_function(increase, increase_pin6);
  pin6_line.attach_function(decrease, decrease_pin6);

  oSave_line.attach_function(1, save_output);
  oSave_line.attach_function(2, save_output);
  iSave_line.attach_function(1, save_input);
  iSave_line.attach_function(2, save_input);
  iSample_line.attach_function(increase, increase_samplePeriod);
  iSample_line.attach_function(decrease, decrease_samplePeriod);

  input_saved = (char*)" *";
  output_saved = (char*)" *";

  menu_system.update();
}

void loop() {
  buttonsCheck();
  temp_device();

  static unsigned long lastMillis_sample = 0;
  if (millis() - lastMillis_sample > (sample_period * 1000)) {
    lastMillis_sample = millis();
    pinA4_value = analogRead(pinA4);
    pinA5_value = analogRead(pinA5);
    //menu_system.update();
  }

}
