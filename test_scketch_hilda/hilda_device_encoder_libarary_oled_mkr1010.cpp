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

//LIBRARY FOR WI-FI NETWORK 
#include <SPI.h>
#include <WiFiNINA.h>

// WIFI NETWORK NAME & PIN
#include "arduino_secrets.h" 
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0; 

//VARS & MODE FOR WI-FI CONNECTION
int status = WL_IDLE_STATUS;
WiFiServer server(80);// your network key Index number (needed only for WEP)

//LIBRARY FOR FLASH MEMORY
//#include <FlashStorage.h>

//LIBRARY TO GENERATE JSON FILES
#include <ArduinoJson.h>

//LIBRARY FOR ENCODER
#include <Encoder.h>

//PINS FOR ENCODERS
Encoder knobLeft(0, 1);
Encoder knobRight(4, 5);

//VARS FOR ENCODERS
long positionLeft  = -999;
long positionRight = -999;
long newLeft, newRight;

// RTC
#include <RTCZero.h>

/* Create an rtc object */
RTCZero rtc;

// RTC VARS
String dateDay = "";
String dateMonth = "";
String dateYear = "";

//String hourHour = "";
//String hourMinutes = "";
//String hourSeconds = "";

String date = "";
String hours = "";
//String dateAndHour = "";
long int unixSeg;

//OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//SIZE OLED PINS SET & SIZE
#define ANCHO 128
#define ALTO 64 
#define OLED_RESET 3     
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);

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

//TEMP SENSOR
#include "DHT.h"

//TEMP SENSOR KIND, PIN & INIT
#define DHTPIN 9
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//VARS FOR DHT22
float hic;

//USERNAME & ID DEVICE
String user_name = "Camila";
int user_id_device = 12345;

//COLOR VARS
String name_color = "";
String name_body_part = "";

//STATE OF SCREENS
bool weMessageLogo = false;
bool weMessageNameUser = false;
bool showTemp = false;
//bool sendData = false;

//LED BUILT-IN FOR ON/OFF
int led = 6; 

//BUTTONS
int buttonOnOff = 7;
int buttonTemp = 8;
int buttonSaveData = 10;

//BUTTONS STATE & COUNT
//int buttonState = 0; 
int countRegisters = 0;

//FLASH MEMORY DEFINITION SPACES FOR VARS RESULTS
//FlashStorage(my_flash_store_date_hour, String);
//FlashStorage(my_flash_store_user_name, String);
//FlashStorage(my_flash_store_name_color, String);
//FlashStorage(my_flash_store_newRight, int);
//FlashStorage(my_flash_store_hic, long int);

void setup() {

  // SERIAL BEGIN
  Serial.begin(9600);
  Serial.println("Hilda device Test");

  // //RTC FOR JUST NOW DATE
  rtc.begin(); // initialize RTC
  rtc.setEpoch(1574350789); // SECS UNTIL NOV ALWAYS DEVALUABLE
  
  dateDay = rtc.getDay(); 
  dateMonth = rtc.getMonth(); 
  dateYear = rtc.getYear();

  //hourHour = rtc.getHours();
  //hourMinutes = rtc.getMinutes();
  //hourSeconds = rtc.getSeconds();

  date = dateDay + "/" + dateMonth + "/" + dateYear;
  //hours = hourHour + ":" + hourMinutes + ":" + hourSeconds;
  //dateAndHour = date + "-" + hours;

  // LED RGB SET
  pixels.begin(); // INITIALIZE NeoPixel strip object 

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

  //wifi connection
  //check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  //attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);

  }
  server.begin();

  //you're connected now, so print out the status:
  printWifiStatus();
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

  // eval temp button
  if(showTemp != true){
    tempSensorData();
  }else{
    // do something
  }

  // encoder read
  encoderReadPos();

  // color match and coloring leds
  matchEncoderColor();

  // save data in flash
  // saveDataInFlashMemory();

  writeHttpResponseInJson();
  
  //buttonState = digitalRead(buttonSaveData);
  //if( buttonState == HIGH){
    //counterClicks();
  //}
  
}

// Custom Function - welcomeMessageLogo()
void welcomeMessageLogo() {

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

// Custom Function - welcomeMessageNameUser()
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

// Custom Function - encoderReadPos()
void encoderReadPos() {
  
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  
  if (newLeft != positionLeft || newRight != positionRight) {
    if(newLeft <= 100 || newRight <= 7){
         
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
}

// Custom Function - matchEncoderColor()
void matchEncoderColor(){

  if(newLeft == 10){
    name_color = "Non";
    name_body_part = "Ninguna";
    Serial.println("non");
    printOledColorMessages(name_color);
    printLedRGB( 0, 0, 0); // non  
    
  }

  if(newLeft == 20){
    name_color = "Red";
    name_body_part = "Cabeza";
    Serial.println("red");
    printOledColorMessages(name_color);
    printLedRGB( 255, 0, 0); // red
     
  } 
  if(newLeft == 30){
    name_color = "Orange";
    name_body_part = "Cuello";
    Serial.println("orange");
    printOledColorMessages(name_color);
    printLedRGB( 255, 120, 0); // orange
    
  }
  if(newLeft == 40){
    name_color = "Green";
    name_body_part = "Busto";
    Serial.println("green");
    printOledColorMessages(name_color);
    printLedRGB( 20, 255, 0); // green
    
  }
  if(newLeft == 50){
    name_color = "Yellow";
    name_body_part = "Abdomen";
    Serial.println("yellow");
    printOledColorMessages(name_color);
    printLedRGB( 255, 240, 0); // yellow
    
  }
  if(newLeft == 60){
    name_color = "Brown";
    name_body_part = "Articulaciones";
    Serial.println("brown");
    printOledColorMessages(name_color);
    printLedRGB( 0, 255, 240); // ocean blue
    
  }
  if(newLeft == 70){
    name_color = "Blue";
    name_body_part = "Espalda";
    Serial.println("blue");
    printOledColorMessages(name_color);
    printLedRGB( 0, 60, 255); // blue
    
  }
  if(newLeft == 80){
    name_color = "Fucsia";
    name_body_part = "Pies";
    Serial.println("fucsia");
    printOledColorMessages(name_color);
    printLedRGB( 255, 0, 110); // Fucsia
    
  } 
}

// Custom Function - printLedRGB()
void printLedRGB(int red_light_value, int green_light_value, int blue_light_value) {
  
  pixels.clear(); 
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(red_light_value, green_light_value, blue_light_value));
    pixels.show();
    delay(DELAYVAL);
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
void tempSensorData() {

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

// Custom Function - aveDataInFlashMemory()
// void saveDataInFlashMemory(){

//   if( digitalRead(buttonSaveData) == HIGH & saveData != true){

//     my_flash_store_date_hour.write(dateAndHour);
//     Serial.println(dateAndHour);
//     my_flash_store_user_name.write(user_name);
//     Serial.println(user_name);
//     my_flash_store_name_color.write(name_color);
//     Serial.println(name_color);
//     my_flash_store_newRight.write(newRight);
//     Serial.println(newRight);
//     my_flash_store_hic.write(hic);
//     Serial.println(hic);
    
//     saveData = true;

//   } else {

//     //Serial.println("none data save");
//     saveData = false;
//   }
// }

// Custom Function - writeHttpResponseInJson()
void writeHttpResponseInJson(){

  // listen for incoming clients
  WiFiClient client = server.available();

  // Do we have a client?
  if (client){; 
    Serial.println(F("New client"));
    
    // Is connected?
    while (client.connected()) {

      if (client.available()) {
        
        // Allocate a temporary JsonDocument
        //StaticJsonDocument<500> doc;
        StaticJsonDocument<500> doc;

        // Counter of requests from the client
        counterClicks();

        // write json pairs
        doc["counter_registers_value"] = countRegisters;
        doc["time-unixtime"] = unixSeg;
        doc["date"] = date;
        doc["user_name"] = user_id_device;
        doc["temperature"] = hic;
        doc["pain_level"] = newRight;
        doc["pain_location"] = name_body_part;
        doc["name_color"] = name_color;
        
        Serial.print(F("Sending: "));
        serializeJson(doc, Serial);
        Serial.println();

        // Write response headers
        client.println(F("HTTP/1.0 200 OK"));
        client.println("Access-Control-Allow-Origin: *");
        client.println(F("Content-Type: application/json"));
        client.println(F("Connection: close"));
        client.print(F("Content-Length: "));
        client.println(measureJsonPretty(doc));
        client.println();
        
        // Write JSON document
        serializeJsonPretty(doc, client);

        // give the web browser time to receive the data
        delay(1); 
        
      }
      // Disconnect
      Serial.println("client disonnected");
      //counterClicks();
      client.WiFiClient::stop();
    } 
  }
}

// Custom Function - printWifiStatus()
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  
}

// Custom Function - counterClicks()
void counterClicks(){
  countRegisters++;
  delay(500);
  Serial.println(countRegisters);

}