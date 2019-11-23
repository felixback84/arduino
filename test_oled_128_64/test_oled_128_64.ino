/*
  Capitulo 47 de Arduino desde cero en Español.
  Programa que muestra texto en la zona amarilla de la pantalla OLED y en la zona
  cyan los segundos transcurridos desde iniciado el programa
  Requiere instalar librerias Adafruit GFX y Adafruit SSD1306

  Autor: bitwiseAr  

*/

#include <Wire.h>     // libreria para bus I2C
#include <Adafruit_GFX.h>   // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>   // libreria para controlador SSD1306
 
#define ANCHO 128     // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64       // reemplaza ocurrencia de ALTO por 64

#define OLED_RESET 3      // necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto


extern uint8_t logo_cara1_1[];
extern uint8_t logo_cara2_1[];
extern uint8_t logo_cara3_1[];
extern uint8_t logo_cara4_1[];
extern uint8_t logo_cara5_1[];
extern uint8_t logo_cara6_1[];
extern uint8_t logo_cara7_1[];
extern uint8_t logo_pies[];
extern uint8_t logo_cabeza[];
extern uint8_t logo_cuello[];
extern uint8_t logo_espalda[];
extern uint8_t logo_busto[];
extern uint8_t logo_abdomen[];
extern uint8_t logo_ebaja[];

#define LOGO_HEIGHT   50
#define LOGO_WIDTH    50

void setup() {
  Wire.begin();         // inicializa bus I2C
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inicializa pantalla con direccion 0x3C
}
 
void loop() {

  welcomeMessageLogo();
  welcomeMessageLogo1();
  welcomeMessageLogo2();
  welcomeMessageLogo3();
  welcomeMessageLogo4();
  welcomeMessageLogo5();
  welcomeMessageLogo6();
  welcomeMessageLogo7();
  welcomeMessageLogo8();
  welcomeMessageLogo9();
  welcomeMessageLogo10();
  welcomeMessageLogo11();
  welcomeMessageLogo12();
  welcomeMessageLogo13();
}

void welcomeMessageLogo() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_cara1_1, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}

void welcomeMessageLogo1() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_cara2_1, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}

void welcomeMessageLogo2() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_cara3_1, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}

void welcomeMessageLogo3() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_cara4_1, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}

void welcomeMessageLogo4() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_cara5_1, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}

void welcomeMessageLogo5() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_cara6_1, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}

void welcomeMessageLogo6() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_cara7_1, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}

void welcomeMessageLogo7() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_pies, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}

void welcomeMessageLogo8() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_cabeza, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}

void welcomeMessageLogo9() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_cuello, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}

void welcomeMessageLogo10() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_espalda, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}

void welcomeMessageLogo11() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_busto, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}

void welcomeMessageLogo12() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_abdomen, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}

void welcomeMessageLogo13() {

  // Print in oled temp results
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.drawBitmap(
    (oled.width()  - LOGO_WIDTH ) / 2,
    (oled.height() - LOGO_HEIGHT) / 2,
    logo_ebaja, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.display();
  delay(5000);
  
  
}
