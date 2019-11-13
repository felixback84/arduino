#include <EEPROM.h>

// pin definitions
int ledPin = 6;
int buttonPin = 7;

// global variables
int lastButtonState = 1;
long unsigned int lastPress;
int debounceTime = 20;
int counter;

void setup() {
  // setup pin modes
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  //initialise Serial port
  Serial.begin(9600);

  //assign counter the value of address 0
  counter = EEPROM.read(0);
  //write a 0 to address 0. This allows for consecutive resets to reset the counter
  EEPROM.write(0,0);
}

void loop() {  
  int buttonState = digitalRead(buttonPin);   //read the state of buttonPin and store it as buttonState (0 or 1)
  
  if((millis() - lastPress) > debounceTime)   //if the time between the last buttonChange is greater than the debounceTime
  {
    lastPress = millis();   //update lastPress                                                     
    if(buttonState == 0 && lastButtonState == 1)    //if button is pressed and was released last change
    {
      counter++;
      EEPROM.write(0, counter); //write counter to address 0
      digitalWrite(ledPin, HIGH); //momentary LED
      lastButtonState = 0;    //record the lastButtonState

      //print the results
      Serial.print("Counter: ");
      Serial.println(counter);
    }
    if(buttonState == 1 && lastButtonState == 0)    //if button is not pressed, and was pressed last change
    {
      lastButtonState = 1;    //record the lastButtonState
      digitalWrite(ledPin, LOW);  //momentary LED
    }
  }
}
