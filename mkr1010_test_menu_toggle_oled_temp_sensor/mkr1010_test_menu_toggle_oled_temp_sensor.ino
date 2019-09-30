//BOARD
//MKR 1010

//OLED PINS
//GND GND
//VIN 5V
//SCL SCL
//SDA SDA

//DHT22 PINS
//ANODO 5V
//CATODO GND
//BEFORE RES 5V (DORADO-NARANJA-NEGRO-CAFE) - DATA PIN D0

//TEMP SENSOR
#include "DHT.h"

//OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//TEMP SENSOR KIND & PIN
#define DHTPIN 1
#define DHTTYPE DHT22

//SIZE OLED
#define ANCHO 128
#define ALTO 64 

//OLED SET
#define OLED_RESET 4      
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET); 

//SENSOR TEMP SET
DHT dht(DHTPIN, DHTTYPE);

//GLOBAL VARIABLES BUTTON TOGGLE
int WhichScreen = 1;   // This variable stores the current Screen number
boolean hasChanged = true;
const int buttonPin = 6;    // the number of the pushbutton pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

//GLOBAL VARIABLES DHT SENSOR
float t;
float h;
 
void setup() {

  // SERIAL BEGIN
  Serial.begin(9600);
  
  // PIN TOGGLE
  pinMode(buttonPin, INPUT);
  
  // SENSOR DHT BEGIN
  dht.begin();
  
  // INIT BUS I2C
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);        
}

void loop()
{
   // SENSOR DHT
    
   h = dht.readHumidity();
   t = dht.readTemperature();
   
   float hic = dht.computeHeatIndex(t,h, false); 

   // Print in the serial Monitor
    
   Serial.println(hic);
   delay(500); // we read signal every 500ms

   Serial.println(hasChanged);
   

   //OLED PRINT
   oled.clearDisplay();
   oled.setTextColor(WHITE);
   oled.setCursor(0, 0);     
   oled.setTextSize(1);
   oled.print("Hola, la temperatura de hoy es:"); 
   oled.setCursor (10, 30); 
   oled.setTextSize(2);
   oled.print(hic);  
   oled.print(" C");
   oled.display(); 
  
  // MENU SET FOR OLED
  
  if (hasChanged == true) {
   
  switch(WhichScreen) {
    case 1:
    {
      firstScreen();
    }
      break;
   
    case 2:
      {
        secondScreen();
      }
      break;
   
    case 3:
      {
        thirdScreen();
      }
      break;
   
    case 4:
      {
        fourthScreen();
      }
      break;
   
    case 5:
      {
        fifthScreen();
      }
      break;
   
    case 6:
      {
        sixthScreen();
      }
      break;
      
    }
}

  //-------------------------------
  // BEGIN of the switch debouncing code
  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
 
if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
 
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
 
      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        hasChanged = true;
        WhichScreen++;
      }
    } else {
      hasChanged = false;
    }
  }
  lastButtonState = reading;
  // END of the switch Debouncing code
  // --------------------------------------
  if (WhichScreen > 6){
    WhichScreen = 1;
  }
}

//OLED PRINT SCREENS

void firstScreen()
  {
   
   oled.clearDisplay();
   oled.setTextColor(WHITE);
   oled.setCursor(0, 0);     
   oled.setTextSize(1);
   oled.print("Hola, la temperatura de hoy es: 0"); 
   
  }

void secondScreen()
  {

   oled.clearDisplay();
   oled.setTextColor(WHITE);
   oled.setCursor(0, 0);     
   oled.setTextSize(1);
   oled.print("Hola, la temperatura de hoy es: 1"); 
    
  }

void thirdScreen()
  {
   oled.clearDisplay();
   oled.setTextColor(WHITE);
   oled.setCursor(0, 0);     
   oled.setTextSize(1);
   oled.print("Hola, la temperatira de hoy es:2"); 
  }

void fourthScreen()
  {
   oled.clearDisplay();
   oled.setTextColor(WHITE);
   oled.setCursor(0, 0);     
   oled.setTextSize(1);
   oled.print("Hola, la temperatira de hoy es:3"); 
  }

void fifthScreen()
  {
   oled.clearDisplay();
   oled.setTextColor(WHITE);
   oled.setCursor(0, 0);     
   oled.setTextSize(1);
   oled.print("Hola, la temperatira de hoy es:4"); 
  }

void sixthScreen()
  {
   oled.clearDisplay();
   oled.setTextColor(WHITE);
   oled.setCursor(0, 0);     
   oled.setTextSize(1);
   oled.print("Hola, la temperatira de hoy es:5"); 
  }
