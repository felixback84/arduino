//TEMP SENSOR
#include "DHT.h"

//TEMP SENSOR KIND, PIN & INIT
#define DHTPIN 11
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//SIZE OLED PINS SET & SIZE
#define ANCHO 128
#define ALTO 64 
#define OLED_RESET 4      
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  

//RGB LED PINS SET
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 8 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels

//ROTATORY ENCODER 1
#define outputA_1 2
#define outputB_1 3

//VARS FOR ENCODER 1
int counter_1; 
int aState_1;
int aLastState_1;

//ROTATORY ENCODER 2
#define outputA_2 6
#define outputB_2 7

//VARS FOR ENCODER 2
int counter_2 = 0; 
int aState_2;
int aLastState_2;

//COLOR VAR
int color = 0;

void setup() {

  // SERIAL BEGIN
  Serial.begin(9600);

  // ENCODER 1 SET 
  pinMode (outputA_1,INPUT);
  pinMode (outputB_1,INPUT);
   
  // Reads the initial state of the outputA_1
  aLastState_1 = digitalRead(outputA_1); 

  // ENCODER 2 SET 
  pinMode (outputA_2,INPUT);
  pinMode (outputB_2,INPUT);
   
  // Reads the initial state of the outputA_2
  aLastState_2 = digitalRead(outputA_2);
  
  // LED RGB SET
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  
  // SENSOR DHT BEGIN
  dht.begin();
  
  // INIT BUS I2C
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop(){
  
  //tempSensor();
  encoderPosCualify();
  encoderPosColor();

  if(counter_2 == 0){
    color = 0; 
    Serial.println("non");
      
  }

  if(counter_2 == 10){
    color = 1; 
    Serial.println("red");
      
  } 
  if(counter_2 == 20){
    color = 2;
    Serial.println("orange");
   
  }
  if(counter_2 == 30){
    color = 3;
    Serial.println("green");
  
  }
  if(counter_2 == 40){
    color = 4;
    Serial.println("yellow");

  }
  if(counter_2 == 50){
    color = 5;
    Serial.println("brown");
    
  }
  if(counter_2 == 60){
    color = 6;
    Serial.println("blue");
    
  }
  if(counter_2 == 70){
    color = 7;
    Serial.println("fucsia");
    
  } 
  
  switch (color)

  {
    case 0:
    
    break;
    
    case 1:
    pixels.clear();
    for(int i=0; i<NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    pixels.show(); 
    }
    break;

    case 2:
    //printLedRGB( 255, 120, 0); // orange
    break;

    case 3:
    //printLedRGB( 20, 255, 0); // green
    break;

    case 4:
    //printLedRGB( 255, 240, 0); // yellow
    break;

    case 5:
    //printLedRGB( 85, 65, 0); // brown
    break; 

    case 6:
    //printLedRGB( 0, 60, 255); // blue
    break; 

    case 7:
    //printLedRGB( 255, 0, 109); // Fucsia
    break;  
  }
  
}

// Custom Function - tempSensor()
void tempSensor() {

  float t;
  float h;
  h = dht.readHumidity();
  t = dht.readTemperature();
     
  float hic = dht.computeHeatIndex(t,h, false);

  // Print in the serial Monitor
  Serial.println(hic);
  // Print in oled temp results
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

}

// Custom Function - encoderPosCualify()
void encoderPosCualify() { 
   aState_1 = digitalRead(outputA_1); // Reads the "current" state of the outputA
   
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState_1 != aLastState_1){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB_1) != aState_1) { 
       if (counter_1 < 7)
       {counter_1 ++;}
     } else {
       if (counter_1 > 0)
       {counter_1 --;}
     }
     Serial.print("Position_1: ");
     Serial.println(counter_1);
   }  
   aLastState_1 = aState_1; // Updates the previous state of the outputA with the current state
}

// Custom Function - encoderPosColor()
void encoderPosColor() { 
   aState_2 = digitalRead(outputA_2); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState_2 != aLastState_2){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB_2) != aState_2) { 
       counter_2 ++;
     } else {
       counter_2 --;
     }
     Serial.print("Position_2: ");
     Serial.println(counter_2);
   } 
   aLastState_2 = aState_2; // Updates the previous state of the outputA with the current state
}
