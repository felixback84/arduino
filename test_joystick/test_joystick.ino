//Code write by Moz for YouTube changel LogMaker360, 12-10-2015
//Code belongs to this video: https://www.youtube.com/watch?v=-h_FQR-KcAY

int JoyStick_X = A0; // x
int JoyStick_Y = A1; // y
int JoyStick_Z = A2; // button
void setup ()
{
  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);
  pinMode (JoyStick_Z, INPUT);
  Serial.begin (9600); // 9600 bps

}
void loop ()
{
  int x, y, z;
  x = analogRead (JoyStick_X - 512);
  y = analogRead (JoyStick_Y - 512);
  z = analogRead (JoyStick_Z);
  Serial.print(" X axis = ");
  Serial.print (x, DEC);
  Serial.print("       Y axis = ");
  Serial.print (y, DEC);
  Serial.print("       Button  value = ");
  Serial.print (z, DEC);
  delay(100);
  if(z == 0){
  Serial.print(" BUTTON is PRESSED");
  delay(1000);
  }
  Serial.println(); // start a new line
  delay (100);
}
