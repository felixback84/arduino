//5V TO 5V
// GND TO GND

//LED
// CATODO PIN D6
// ANODO DIRECTAMENTE A RESISTENCIA AMARRILLO-PURPLE-ROJO-DORADO TO GND

//SENSOR DE PRESION
//5V TO CATODO
//GND TO UNA DE LAS SALIDAS DE LA RESISTENCIA ROJO-ROJO-PURPLE-DORADO Y AHI SI ANODO DEL SENSOR,
//Y DE EL OTRO EXTREMO DE LA RESISTENCIA ES SALIDA A BOARD A PIN A0

int fsrAnalogPin = 0;
int ledPin = 6;
int fsrReading;
int ledBrightness;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  fsrReading = analogRead(fsrAnalogPin);
  //Serial.print("Analog reading = ");
  //Serial.println(fsrReading);

  matchPresure();

  
}

void printInLed(){
  ledBrightness = map(fsrReading, 0, 1023, 0, 255);
  analogWrite(ledPin, ledBrightness);
  delay(100);
  }

void matchPresure(){

    if(fsrReading < 50 & fsrReading > 0 ){
        Serial.print("Analog reading = ");
        Serial.println("0");
        printInLed();
      }

    if(fsrReading < 100 & fsrReading > 50){
        Serial.print("Analog reading = ");
        Serial.println("1");
        printInLed();
      }

    if(fsrReading < 150 & fsrReading > 100){
        Serial.print("Analog reading = ");
        Serial.println("2");
        printInLed();
      } 

    if(fsrReading < 200 & fsrReading > 150){
        Serial.print("Analog reading = ");
        Serial.println("3");
        printInLed();
      }  

    if(fsrReading < 250 & fsrReading > 200){
        Serial.print("Analog reading = ");
        Serial.println("4");
        printInLed();
      }  

    if(fsrReading < 300 & fsrReading > 250){
        Serial.print("Analog reading = ");
        Serial.println("5");
        printInLed();
      }  

    if(fsrReading < 350 & fsrReading > 300){
        Serial.print("Analog reading = ");
        Serial.println("6");
        printInLed();
      }             

    if(fsrReading < 400 & fsrReading > 350){
        Serial.print("Analog reading = ");
        Serial.println("6");
        printInLed();
      }  
  }
