#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server;
uint8_t pin_led = 2;
char* ssid = "ElTranquilo";
char* password ="nenayluis";


void setup()
{
	pinMode(pin_led, OUTPUT);
	WiFi.begin(ssid,password);
	Serial.begin(115200);
	while(WiFi.status()!=WL_CONNECTED)
	{
    	
	Serial.print("."); 
	delay(500);	
  	}	
	Serial.println("");
	Serial.print("IP Address: ");
	Serial.print(WiFi.localIP());

	server.on("/",[](){server.send(200,"text/plain","hello world");});
	server.on("/toggle", toggleLED );
	server.begin();

}


void loop()
{

	server.handleClient();
}

void toggleLED()
{
	digitalWrite(pin_led,!digitalRead(pin_led));
	server.send(204,"");
}
