#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7);

int boton= 0;


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  int valor = analogRead(boton);
  
  lcd.setCursor(2,0);
  lcd.print("hi");
  delay(100);
}
