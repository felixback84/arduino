
/*


*/

//TEMP SENSOR
#include "DHT.h"

//TEMP SENSOR KIND, PIN & INIT
#define DHTPIN 9
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
#define PIN 1 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels

// RGB SENSOR PINS SET
#define S0 2
#define S1 3
#define S2 12
#define S3 13
#define sensorOut 8

//VARS FOR SENSOR RGB
int frequency = 0;
int color = 0;
String nameColor = "";
//char* iconPart = [];

//ROTATORY ENCODER
#define outputA 5
#define outputB 6
#define outputC 7

//VARS FOR ENCODER
int counter = 0; 
int aState;
int aLastState;

//USER INFO
String userName = "Diana";

void setup() {

  // SERIAL BEGIN
  Serial.begin(9600);

  // ENCODER SET 
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  pinMode (outputC,INPUT);
  digitalWrite(outputC, HIGH);
   
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA); 
  
  // LED RGB SET
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  
  // SENSOR DHT BEGIN
  dht.begin();
  
  // INIT BUS I2C
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  //PINS CONFIG FOR SENSOR RGB
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20% to RGB Sensor
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

}

void loop(){
  encoderPos();

  if(counter == 9 & digitalRead(outputC) == LOW){
    printOledHi();

  }

  if(counter == 18 & digitalRead(outputC) == LOW){
    tempSensor();
  }

  if(counter == 27 & digitalRead(outputC) == LOW){
    readColor();
          
  }
  
}

// Custom Function - encoderPos()
void encoderPos() { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
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
  delay(50);

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
  delay(50);

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
  delay(50);

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
  if(R<55 & R>40 & G<75 & G>60){
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

  //color = readColor();
  //delay(100); 
  
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

  // Print in the serial Monitor
  //Serial.println(nameColor);
  // Print in oled color results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);     
  oled.setTextSize(1);
  oled.print("El color es:"); 
  oled.setCursor (10, 30); 
  oled.setTextSize(2);
  oled.print(nameColor);
  //oled.print(iconPart);
  oled.display();
}