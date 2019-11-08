//BOARD

//MKR 1010

//OLED

//VCC 5V
//GND GND
//SDA 11 (SDA PIN)
//SCL 12 (SCL PIN)

//ENCODER 01

//VCC 5V
//GND GND
//DT D4
//CLK D5

//ENCODER 02

//VCC 5V
//GND GND
//DT D1
//CLK D0

//DHT 22

//VCC 5V
//GND GND
//OUT D9 (SCK PIN)

//LED STRIPE

//VCC 5V
//GND GND
//D1 D2

//PUSH BUTTONS 1,2,3

//VCC 5V
//GND BEFORE RESISTENCIA (CAFE-NEGRO-NARANJA-DORADO) TO GND
// DATA PIN IN FRONT DE GND TO D7, D8, D10 


//LIBRARY FOR ENCODER
#include <Encoder.h>

//PINS FOR ENCODERS
Encoder knobLeft(0, 1);
Encoder knobRight(4, 5);

//VARS FOR ENCODERS
long positionLeft  = -999;
long positionRight = -999;
long newLeft, newRight;

//OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//SIZE OLED PINS SET & SIZE
#define ANCHO 128
#define ALTO 64 
#define OLED_RESET 3     
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);

//TEMP SENSOR
#include "DHT.h"

//TEMP SENSOR KIND, PIN & INIT
#define DHTPIN 9
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//VARS FOR DHT22
float hic;

//RGB LED PINS SET
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 2 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 5 // Time (in milliseconds) to pause between pixels

//COLOR VARS
String name_color = "";

//USERNAME
String user_name = "Camila";

//STATE
bool weMessageLogo = false;
bool weMessageNameUser = false;
bool showTemp = false;

//LED ON/OFF
int led = 6;

//BUTTONS
int buttonOnOff = 7;
int buttonTemp = 8;
int buttonSaveData = 10;

void setup() {

  Serial.begin(9600);
  Serial.println("TwoKnobs Encoder Test:");

  // LED RGB SET
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  // INIT BUS I2C
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // SENSOR DHT BEGIN
  dht.begin();

  //LED
  pinMode(led,OUTPUT);

  //BUTTONS
  pinMode(buttonOnOff,INPUT);
  pinMode(buttonTemp,INPUT);
  pinMode(buttonSaveData,INPUT);
}

void loop(){

  // eval welcome logo
  if(weMessageLogo != true){
    welcomeMessageLogo();  
  }

  // eval welcome message
  if(weMessageNameUser != true){  
    welcomeMessageNameUser();
  } 

  // eval push built-in led button
  // if(digitalRead(buttonOnOff) == HIGH){
  //   digitalWrite(led,HIGH);
  // }else{
  //   digitalWrite(led,LOW);
  // }  

  // eval temp button
  if(showTemp != true){
    tempSensor();
  }else{
    // do something
  }

  // encoder
  encoderPos();

  // color match
  matchEncoderColor();

}

void welcomeMessageLogo() {

  //weMessageLogo;
  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE); 
  oled.setCursor (10, 30); 
  oled.setTextSize(2);
  oled.print("hola, logo Hilda aqui");  
  oled.display();
  delay(5000);
  weMessageLogo = true;
  
}

void welcomeMessageNameUser(){

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE); 
  oled.setCursor (10, 30); 
  oled.setTextSize(2);
  oled.print("hola," + user_name);  
  oled.display();
  delay(5000);
  weMessageNameUser = true;
 
}

void encoderPos() {
  
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  
  if (newLeft != positionLeft || newRight != positionRight) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionLeft = newLeft;
    positionRight = newRight;

    // Print in oled temp results
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    
    oled.setCursor(0, 0);     
    oled.setTextSize(1);
    oled.print(newLeft); 

    oled.setCursor(6, 6);     
    oled.setTextSize(1);
    oled.print(newRight);

    oled.display();
  }  
}

// Custom Function - matchEncoderColor()
void matchEncoderColor(){

  if(newLeft == 10){
    name_color = "Non";
    Serial.println("non");
    printOledColorMessages(name_color);
    printLedRGB( 0, 0, 0); // non  
    
  }

  if(newLeft == 20){
    name_color = "Red";
    Serial.println("red");
    printOledColorMessages(name_color);
    printLedRGB( 255, 0, 0); // red
     
  } 
  if(newLeft == 30){
    name_color = "Orange";
    Serial.println("orange");
    printOledColorMessages(name_color);
    printLedRGB( 255, 120, 0); // orange
    
  }
  if(newLeft == 40){
    name_color = "Green";
    Serial.println("green");
    printOledColorMessages(name_color);
    printLedRGB( 20, 255, 0); // green
    
  }
  if(newLeft == 50){
    name_color = "Yellow";
    Serial.println("yellow");
    printOledColorMessages(name_color);
    printLedRGB( 255, 240, 0); // yellow
    
  }
  if(newLeft == 60){
    name_color = "Brown";
    Serial.println("brown");
   printOledColorMessages(name_color);
    printLedRGB( 85, 65, 0); // brown
    
  }
  if(newLeft == 70){
    name_color = "Blue";
    Serial.println("blue");
    printOledColorMessages(name_color);
    printLedRGB( 0, 60, 255); // blue
    
  }
  if(newLeft == 80){
    name_color = "Fucsia";
    Serial.println("fucsia");
    printOledColorMessages(name_color);
    printLedRGB( 255, 0, 110); // Fucsia
    
  } 
}

// Custom Function - printLedRGB()
void printLedRGB(int red_light_value, int green_light_value, int blue_light_value) {
  
  pixels.clear(); 
  for(int i=0; i<NUMPIXELS; i++) {
    //int bucle;
    //bucle ++;
    pixels.setPixelColor(i, pixels.Color(red_light_value, green_light_value, blue_light_value));
    pixels.show();
    delay(DELAYVAL);

    //if(bucle = NUMPIXELS){
      //  pixels.clear();
      //}
  } 
}

// Custom Function - printOledMessages()
void printOledColorMessages(String name_color){

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);       
  oled.setCursor (10, 30); 
  oled.setTextSize(2);
  oled.print(name_color);  
  oled.display();
}

// Custom Function - tempSensor()
void tempSensor() {

  float t;
  float h;
  
  h = dht.readHumidity();
  t = dht.readTemperature();
     
  hic = dht.computeHeatIndex(t,h, false);

  //Print in the serial Monitor
  Serial.println(hic);

  //Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);     
  oled.setTextSize(1);
  oled.print("La temperatura de Hilda es:"); 
  oled.setCursor (10, 30); 
  oled.setTextSize(2);
  oled.print(hic);  
  oled.print(" C");
  oled.display();
  delay(5000);
  
  showTemp = true;

}