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

// Pin definitions and variables for their state.
const byte led = 6;
byte pin6_level = 0;

// Text used for indication for the save lines.
char* pain_level_saved;
char* pain_location_saved;
//char* sync_saved;
//float temp_level_saved;

//Var parts
String parts = "";

//Vars for temp device
float tempDevice = 0;
uint32_t delayMS;

//Pins setup
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

// For check the state of the data saving in cloud
bool stateDataCloud = false;

// A LiquidLine object can be used more that once.
LiquidLine back_line(11, 1, "/BACK");

//Welcome
LiquidLine welcome_line1(1, 0, "Hilda`s World");
LiquidLine welcome_line2(1, 1, "Hola Diana");

LiquidScreen welcome_screen(welcome_line1, welcome_line2);

// Scroll main menu
LiquidLine main_line_1(0, 0, "/PAIN LEVEL");
LiquidLine main_line_2(0, 1, "/PAIN LOCATION");
//LiquidLine main_line_3(0, 2, "/SYNC DATA");
LiquidLine main_line_4(0, 3, "/TEMP DATA");

LiquidScreen main_io_screen;

// This is the first menu.
LiquidMenu main_menu(lcd, welcome_screen, main_io_screen);

//Pain level menu
LiquidLine pain_level_line_title(0, 0, "Pain level");
LiquidLine pain_level_line_value(0, 1, "Cualify: ", pin6_level);
LiquidScreen pain_level_screen(pain_level_line_title, pain_level_line_value );

LiquidLine pain_level_save_line(0, 0, "Save", pain_level_saved);
LiquidScreen pain_level_secondary_screen(pain_level_save_line, back_line);

// This is the second menu.
LiquidMenu pain_level_menu(lcd, pain_level_screen, pain_level_secondary_screen);

//Pain location menu
LiquidLine pain_location_line_1(0, 0, "Local_01");
LiquidLine pain_location_line_2(0, 1, "Local_02");
LiquidLine pain_location_line_3(0, 1, "Local_03");
LiquidLine pain_location_line_4(0, 1, "Local_04");
LiquidLine pain_location_line_5(0, 1, "Local_05");
LiquidScreen pain_location_screen;

LiquidLine pain_location_save_line(0, 0, "Save", pain_location_saved);
LiquidScreen pain_location_secondary_screen(pain_location_save_line, back_line);

// This is the third menu.
LiquidMenu pain_location_menu(lcd, pain_location_screen, pain_location_secondary_screen);

//Sync data menu
//LiquidLine sync_line_title(0, 0, "Sync data");
//LiquidLine sync_line_value(0, 1, "Success: ", stateDataCloud);
//LiquidScreen sync_screen(sync_line_title, sync_line_value);

//LiquidLine sync_save_line(0, 0, "Save", sync_saved);
//LiquidScreen sync_secondary_screen(sync_save_line, back_line);

// This is the four menu.
//LiquidMenu sync_menu(lcd, sync_screen, sync_secondary_screen);

//Pain level menu
LiquidLine temp_line_title(0, 0, "Temperature");
LiquidLine temp_line_value(0, 1, "C: ", tempDevice);
LiquidScreen temp_screen(temp_line_title, temp_line_value);

LiquidLine temp_save_line(0, 0, "Save");
LiquidScreen temp_secondary_screen(temp_save_line, back_line);

// This is the fifth menu.
LiquidMenu temp_menu(lcd, temp_screen, temp_secondary_screen);

// This is the menu system
LiquidSystem menu_system(main_menu, pain_level_menu, pain_location_menu, temp_menu);

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

// go to functions
// Callback function that will be attached to back_line.
void go_back() {
  menu_system.change_menu(main_menu);
}

void goto_pain_level_menu() {
  menu_system.change_menu(pain_level_menu);
}

void goto_pain_location_menu() {
  menu_system.change_menu(pain_location_menu);
}

//void goto_sync_menu() {
  //menu_system.change_menu(sync_menu);
//}

void goto_temp_menu() {
  menu_system.change_menu(temp_menu);
}

// Pain led level
void increase_led_level() {
  if (pin6_level < 7) {
    pin6_level += 1;
  } else {
    pin6_level = 1;
  }
  switch (pin6_level) {

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
  pain_level_saved = (char*)"  ";
}

void decrease_led_level() {
  if (pin6_level > 1) {
    pin6_level -= 1;
  } else {
    pin6_level = 7;
  }
  switch (pin6_level) {

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
  pain_level_saved = (char*)"  ";
}

// functions for pain location menu
void pain_location_1(){
  parts = "Local_01";
  pain_location_saved = (char*)"  ";
  Serial.println(parts);
  }
void pain_location_2(){
  parts = "Local_02";
  pain_location_saved = (char*)"  ";
  Serial.println(parts);
  }
void pain_location_3(){
  parts = "Local_03";
  pain_location_saved = (char*)"  ";
  Serial.println(parts);
  }
void pain_location_4(){
  parts = "Local_04";
  pain_location_saved = (char*)"  ";
  Serial.println(parts);
  }
void pain_location_5(){
  parts = "Local_05";
  pain_location_saved = (char*)"  ";
  Serial.println(parts);
  }

// function for sync data in cloud
//void send_data_cloud(){
  //stateDataCloud = false;
//}

// function for temp sensor
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
    //temp_level_saved = (char*)"  ";
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
}

// function for save data in mem
void save_pain_level() {
  EEPROM.put(9, pin6_level);
  pain_level_saved = (char*)" *";
}

void save_pain_location() {
  EEPROM.put(10, parts);
  pain_location_saved = (char*)" *";
}

//void save_sync_state() {
  //EEPROM.put(11, stateDataCloud);
  //sync_saved = (char*)" *";
//}

//void save_temp_state() {
  //EEPROM.put(12, tempDevice);
  //tempDevice = (char*)" *";
//}

void setup() {

  // Serial init
  Serial.begin(9600);

  // dht begin
  dht.begin();

  // lcd begin
  lcd.begin();
  lcd.backlight();

  // led mode & set
  pinMode(led, OUTPUT);
  analogWrite(led, pin6_level);

  // Reads the values recorded in the EEPROM
  EEPROM.get(9, pin6_level);
  EEPROM.put(10, parts);
  //EEPROM.get(11, stateDataCloud);
  //EEPROM.get(12, tempDevice);

  back_line.set_focusPosition(Position::LEFT);

  back_line.attach_function(1, go_back);
  back_line.attach_function(2, go_back);

  // Add more "lines" than the display has. The extra will be scrolled.
  main_io_screen.add_line(main_line_1);
  main_io_screen.add_line(main_line_2);
  //main_io_screen.add_line(main_line_3);
  main_io_screen.add_line(main_line_4);

  // Attaching a function to the lines is required for scrolling to work.
  main_line_1.attach_function(1, goto_pain_level_menu);
  main_line_1.attach_function(2, goto_pain_level_menu);

  main_line_2.attach_function(1, goto_pain_location_menu);
  main_line_2.attach_function(2, goto_pain_location_menu);

  //main_line_3.attach_function(1, goto_sync_menu);
  //main_line_3.attach_function(2, goto_sync_menu);

  main_line_4.attach_function(1, goto_temp_menu);
  main_line_4.attach_function(2, goto_temp_menu);

  //  Items for scrolling menu
  main_io_screen.set_displayLineCount(2);

  //Pain led level menu
  pain_level_line_value.attach_function(increase, increase_led_level);
  pain_level_line_value.attach_function(decrease, decrease_led_level);

  // functions for all secondaries menus
  pain_level_save_line.attach_function(1, save_pain_level);
  pain_level_save_line.attach_function(2, save_pain_level);

  pain_location_save_line.attach_function(1, save_pain_location);
  pain_location_save_line.attach_function(2, save_pain_location);

  //sync_save_line.attach_function(1, save_sync_state);
  //sync_save_line.attach_function(2, save_sync_state);

  //temp_save_line.attach_function(1, save_temp_state);
  //temp_save_line.attach_function(2, save_temp_state);

  // Add more "lines" than the display has. The extra will be scrolled.
  pain_location_screen.add_line(pain_location_line_1);
  pain_location_screen.add_line(pain_location_line_2);
  pain_location_screen.add_line(pain_location_line_3);
  pain_location_screen.add_line(pain_location_line_4);
  pain_location_screen.add_line(pain_location_line_5);

  // Attaching a function to the lines is required for scrolling to work.
  pain_location_line_1.attach_function(1, pain_location_1);
  pain_location_line_1.attach_function(2, pain_location_1);
  pain_location_line_2.attach_function(1, pain_location_2);
  pain_location_line_2.attach_function(2, pain_location_2);
  pain_location_line_3.attach_function(1, pain_location_3);
  pain_location_line_3.attach_function(2, pain_location_3);
  pain_location_line_4.attach_function(1, pain_location_4);
  pain_location_line_4.attach_function(2, pain_location_4);
  pain_location_line_5.attach_function(1, pain_location_5);
  pain_location_line_5.attach_function(2, pain_location_5);

  //  Items for scrolling menu
  pain_location_screen.set_displayLineCount(2);

  // menu system
  menu_system.update();

}

void loop() {

  buttonsCheck();
  temp_device();


}
