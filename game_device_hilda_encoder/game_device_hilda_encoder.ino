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
#define PIN 0 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels

// RGB SENSOR PINS SET
#define S0 5
#define S1 6
#define S2 7
#define S3 9
#define sensorOut 10

//VARS FOR SENSOR RGB
int frequency = 0;
int color = 0;
String nameColor = "";
//char* iconPart = [];

// ENCODER SET & VARS
// Used for generating interrupts using CLK signal
const int PinA = 2;
// Used for reading DT signal
const int PinB = 3;
// Used for the push button switch
const int PinSW = 8;
// Keep track of last rotary value
int lastCount = 0;
// Updated by the ISR (Interrupt Service Routine)
volatile int virtualPosition = 0;

//USER INFO
String userName = "Diana";

// MAIN SETUP
void setup() {

  // SERIAL BEGIN
  Serial.begin(115200);
  
  // BUILT-LED
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Rotary pulses are INPUTs
  pinMode(PinA, INPUT);
  pinMode(PinB, INPUT);

  // Switch is floating so use the in-built PULLUP so we don't need a resistor
  pinMode(PinSW, INPUT_PULLUP);

  // Attach the routine to service the interrupts
  attachInterrupt(digitalPinToInterrupt(PinA), isr, LOW);
  
  // INIT BUS I2C
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // LED RGB SET
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  
  // SENSOR DHT BEGIN
  dht.begin();

  //PINS CONFIG FOR SENSOR RGB
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20% to RGB Sensor
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Ready to go!
  Serial.println("Start");
}


//MAIN LOOP
void loop() {

//  if(virtualPosition == 9){
//    printOledHi();
//
//  }
//
//  if(virtualPosition == 18){
//    tempSensor();
//  }

  if(virtualPosition == 27){
    printLedRGB(20, 255, 0);    
  }


  // If the current rotary switch position has changed then update everything
  if (virtualPosition != lastCount) {

    // Write out to serial monitor the value and direction
    Serial.print(virtualPosition > lastCount ? "Up  :" : "Down:");
    Serial.println(virtualPosition);

    // Keep track of this new value
    lastCount = virtualPosition ;

    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setCursor(0, 0);     
    oled.setTextSize(2);
    oled.print(virtualPosition); 
    oled.display();
  }
}

// INTERRUPT 
void isr ()  {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  // If interrupts come faster than 5ms, assume it's a bounce and ignore
  if (interruptTime - lastInterruptTime > 5) {
    if (digitalRead(PinB) == LOW)
    {
      virtualPosition-- ; // Could be -5 or -10
    }
    else {
      virtualPosition++ ; // Could be +5 or +10
    }
  }
     
  // Keep track of when we were here last (no more than every 5ms)
  lastInterruptTime = interruptTime;
  
}

// Custom Function - printOledHi()
void printOledHi(){

  // Print in the serial Monitor
  Serial.println(userName);
  // Print in oled color results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);     
  oled.setTextSize(1);
  oled.print("Hilda te dice: Hola"); 
  oled.setCursor (10, 30); 
  oled.setTextSize(2);
  oled.print(userName);  
  oled.display();

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

//COLOR FUNCTIONS
// Custom Function - readColor()
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(500);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(500);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(500);

  if(R<85 & R>60 & G<265 & G>250){
    color = 1; // Red
    Serial.println("red");
    delay(3000);
  }
  if(G<165 & G>155 & B<175 &B>160){
    color = 2; // Orange
    Serial.println("orange");
    delay(3000);
  }
  if(R<130 & R>110 & G<95 & G>80){
    color = 3; // Green
    Serial.println("green");
    delay(3000);
  }
  if(R<75 & R>55 & G<105 & G>80){
    color = 4; // Yellow
    Serial.println("yellow");
    delay(3000);
  }
  if(R<175 & R>155 & G<325 & G>305){
    color = 5; // Brown
    Serial.println("brown");
    delay(3000);
  }
  if (G<315 & G>280 & B<155 &B>130){
    color = 6; // Blue
    Serial.println("blue");
    delay(3000);
  }
  if (G<45 & G>35 & G<45 &G>35){
    color = 7; // white
    Serial.println("white");
    delay(3000);
  }
  if (R<450 & R>390 & B<280 &B>250){
    color = 8; // black
    Serial.println("black");
    delay(3000);
  }
  return color;  
}

//Custom Function - ledColorOn()
void ledColorOn() {

  if(virtualPosition == 27){
    printLedRGB( 255, 255, 255); 
    delay(3000);
    } 
  
  switch (color) {
    
    case 0:
    printLedRGB( 0, 0, 0); // non
    delay(3000);
    break;
    case 1:
    printLedRGB( 255, 0, 0); // red
    delay(3000);
    break;
    case 2:
    printLedRGB( 255, 120, 0); // orange
    delay(3000);
    break;
    case 3:
    printLedRGB( 20, 255, 0); // green
    delay(3000);
    break;
    case 4:
    printLedRGB( 255, 240, 0); // yellow
    delay(3000);
    break;
    case 5:
    printLedRGB( 85, 65, 0); // brown
    delay(3000);
    break; 
    case 6:
    printLedRGB( 0, 60, 255); // blue
    delay(3000);
    break;   
  }
  
}

// Custom Function - printLedRGB()
void printLedRGB(int red_light_value, int green_light_value, int blue_light_value) {
  
  pixels.clear(); // Set all pixel colors to 'off'

  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(red_light_value, green_light_value, blue_light_value));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop

  } 

}
