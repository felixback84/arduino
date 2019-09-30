//BOARD
//Genuino UNO

//OLED PINS
//GND GND
//VIN 5V
//SCL A5
//SDA A4

// LED PINS
//1 RED
//CATODO  RESISTENCIA (PURPLE-ROJO-ROJO) GND
//ANODO 13

//2 GREEN
//CATODO  RESISTENCIA (PURPLE-ROJO-ROJO) GND
//ANODO 12

//DHT22 PINS
//ANODO 5V
//CATODO GND
//BEFORE RES 5V (DORADO-NARANJA-NEGRO-CAFE) - DATA PIN D3

//TEMP SENSOR
#include "DHT.h"

//OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//TEMP SENSOR KIND & PIN
#define DHTPIN 3
#define DHTTYPE DHT22

//SIZE OLED
#define ANCHO 128
#define ALTO 64 

//PINS LEDS ALARM
#define LED_RED 13
#define LED_GREEN 12

//OLED SET
#define OLED_RESET 4      
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  

//SENSOR TEMP SET
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  // SERIAL BEGIN
  Serial.begin(9600);
  
  // LEDS SET
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  // SENSOR DHT BEGIN
  dht.begin();
  
  // INIT BUS I2C
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);        
}

float t;
float h;

void loop() {
  
  h = dht.readHumidity();
  t = dht.readTemperature();
     
  float hic = dht.computeHeatIndex(t,h, false);

  // Print in the serial Monitor
  Serial.println(hic);
  
  // Turn On/Off the LED If is greather than 22°C
  if(hic > 22) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);    
  } else {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
  }
  
  delay(500); // we read signal every 500ms

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);     
  oled.setTextSize(1);
  oled.print("Hola, la temperatira de hoy es:"); 
  oled.setCursor (10, 30); 
  oled.setTextSize(2);
  oled.print(hic);  
  oled.print(" ºC");
  oled.display();
}
