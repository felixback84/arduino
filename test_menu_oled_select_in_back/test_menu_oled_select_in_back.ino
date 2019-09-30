#include <OLED_I2C.h>
extern u_int8_t SmallFont[];
int i = 10;
int m = 207;
int page = 1;
int x = 0; int y = 0;
int last1 = 0; int last2 = 0; int last3 = 0;
int other1 = 1; int other2 = 1; int other3 = 1;
volatile boolean inv1 = false; volatile boolean inv2 = false;
volatile boolean tus1 = false; volatile boolean tus2 = false;

OLED myOLED (SDA, SCL, 0);

void setup(){

  myOLED.begin();
  myOLED.clrScr();

  pinMode(2, INPUT);
  myOLED.setFont(SmallFont);
}

void loop(){

  int x = digitalRead(2);
  int y = digitalRead(3);
  int z = digitalRead(4);

  back();

  if (page == 1){

    myOLED.clrScr();
    myOLED.invertText(true);
    myOLED.print("MENU HILDA 1.0", CENTER, 0);
    myOLED.invertText(false);
    myOLED.print("INVERT MODE", 10, 10);
    myOLED.print("COUNTER", 10, 25);
    myOLED.print("MENU ALT", 10, 40);

    if(inv2 == true && page == 1)
      myOLED.print("ON", 85 , 10);

    if(inv2 == false && page == 1)
      myOLED.print("OFF", 85 , 10);

    myOLED.print(">", 0, i); 
    myOLED.update();
    arrow(); 
  }

  choice(); 


  if (page == 2){

    myOLED.clrScr();
    myOLED.invertText(true);
    myOLED.print("MENU ALT" , CENTER, 0);
    myOLED.invertText(false);
    myOLED.print("ALT 01", 10, 10);
    myOLED.print("ALT 02", 10, 25);
    myOLED.print("ALT 03", 10, 40);

    myOLED.print(">", 0, i);
    myOLED.update();
    arrow(); 
  }

  invertFunc();

  if(i == 25 && page == 1 && y == 1){
    page = 3;
  } 

  if(page == 3){
    myOLED.clrScr();
    myOLED.print("COUNTER" , 0, i);
    myOLED.printNumI(m, 60, 25);
    myOLED.update();

    if(y == 1 && page == 3)
      counter();
  }

  myOLED.setBrightness(m);
}

void choice(){
  if(y == 1 && i != 10 && i != 25){
    page == 2;
    i = 10;
  }

}

void arrow(){
  int x = digitalRead(2);

  if(x == 0)
    other1 = 0;

  if(x == 1 && other1 == 0){
    last1 == 1;
    tus1 = true;  
    }

  if(last1 == 1 && tus1 == true){
    other1 = 1;
    myOLED.clrScr();
    myOLED.update();
    i = 1 + 15;
    tus1 = false;
    last1 = 0;

    if(i > 40){
      i = 10;
    }
  } 
}   

void back(){
  int z = digitalRead(4);
  if(z == 1){
    i = 10;

    page = page - 1;
    if(page < 1)
      page - 1;
  } 
}

void counter(){
  int y = digitalRead(3);
  if(y == 0)
    other3 = 0;
  if(y == 1 && other3 == 0 ){
    last3 = 1;
    tus2 = true;
  }

  if(last3 == 1 && tus2 == true){
    other3 = 1;
    myOLED.clrScr();
    myOLED.update();
    m = m + 20;
    tus2 = false;
    last3 = 0;

    if(m > 255){
      m = 0;
    }
  }
}  

void invertFunc(){

  int y = digitalRead(3);

  if(i == 10 && page == 1 && y == 1 && last2 == 0){
    last2 = 1;

    if(inv2 == false){
      inv2 == true;
    } else if ( inv2 == true) {
      inv2 = false;
    }
  } 

  else if (i == 10 && page == 1 && y == 0 && last2 == 1)
    last2 = 0;
  if(inv2 == true)
    myOLED.invert(true);
  if(inv2 == false)
    myOLED.invert(false);
} 
