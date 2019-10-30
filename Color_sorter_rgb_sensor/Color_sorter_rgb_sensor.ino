/*     Arduino Project - Color Sorting Machine
 *
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *
 */


// RGB SENSOR PINS SET
#define S0 5
#define S1 6
#define S2 7
#define S3 9
#define sensorOut 10

int frequency = 0;
int color=0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void loop() {

  readColor();
 
}

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
    delay(500);
  }
  if(G<165 & G>155 & B<175 &B>160){
    color = 2; // Orange
    Serial.println("orange");
    delay(500);
  }
  if(R<130 & R>110 & G<95 & G>80){
    color = 3; // Green
    Serial.println("green");
    delay(500);
  }
  if(R<75 & R>40 & G<110 & G>90){
    color = 4; // Yellow
    Serial.println("yellow");
    delay(500);
  }
  if(R<175 & R>155 & G<325 & G>305){
    color = 5; // Brown
    Serial.println("brown");
    delay(500);
  }
  if (G<315 & G>280 & B<155 &B>130){
    color = 6; // Blue
    Serial.println("blue");
    delay(500);
  }
  if (G<45 & G>35 & G<45 &G>35){
    color = 7; // white
    Serial.println("white");
    delay(500);
  }
  if (R<450 & R>390 & B<280 &B>250){
    color = 8; // black
    Serial.println("black");
    delay(500);
  }
  return color;  
}
