#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server;
uint8_t pin_led = 2;
char* ssid = "ElTranquilo";
char* password ="nenayluis";
char* mySsid = "ElTranquilo2";

IPAddress ip(192,168,11,4);
IPAddress gateway(192,168,11,1);
IPAddress subnet(255,255,255,0);

void setup()
{
	pinMode(pin_led, OUTPUT);
  WiFi.mode(WIFI_AP_STA);
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

  WiFi.softAPConfig(ip,gateway,subnet);
  WiFi.softAP(mySsid, password);

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
