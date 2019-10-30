//ROTATORY ENCODER
#define inputA 2
#define inputB 3
#define inputC 8

//VARS FOR ENCODER
int counter = 0; 
int aState;
int aLastState;

void setup() {

   // SERIAL BEGIN
  Serial.begin(115200);

  // BUILT-LED
  pinMode(LED_BUILTIN, OUTPUT);
  
  // ENCODER SET 
  pinMode (inputA,INPUT);
  pinMode (inputB,INPUT);
  pinMode (inputC,INPUT_PULLUP);
  digitalWrite(inputC, LOW);
   
  // Reads the initial state of the outputA
  aLastState = digitalRead(inputA);

  // Attach the routine to service the interrupts
  attachInterrupt(digitalPinToInterrupt(inputC), isr, LOW);

}

void loop() {
  
  encoderPos();

}

// Custom Function - encoderPos()
void encoderPos() { 
   aState = digitalRead(inputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(inputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
}

void isr ()  {
 
          digitalWrite(LED_BUILTIN, HIGH);
   
}
