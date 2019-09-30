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

//OLED SET
#define OLED_RESET 4      
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  

//SENSOR TEMP SET
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  
  // SERIAL BEGIN
  Serial.begin(9600);
  
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
  
  delay(500); 
  
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);     
  oled.setTextSize(1);
  oled.print("Hola, la temperatira de hoy es:"); 
  oled.setCursor (10, 30); 
  oled.setTextSize(2);
  oled.print(hic);  
  oled.print(" C");
  oled.display();
}
