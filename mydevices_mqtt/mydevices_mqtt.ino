#include <CayenneMQTTESP8266.h>
#include <DHT.h>
#define  CAYENNE_DEBUG
#define CAYENNE_PRINT Serial

char ssid[] = "Lalugam";
char password[] = "Arqlalugam32";

char username[] = "06e745f0-b301-11e9-b6c9-25dbdbf93e02";
char mqtt_password[] = "381349d8fd58cf7fed30249bed1a744454a5b4bc";
char client_id[] = "ef449b50-b305-11e9-9f0a-fd8975d06205";

DHT dht(D2, DHT22); 

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  Cayenne.begin(username, mqtt_password, client_id, ssid, password);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  Cayenne.loop(); 
  delay(2000);
  float temp =  dht.readTemperature();
  float hum = dht.readHumidity();
  Serial.print ("Humedad");
  Serial.print (hum);
  Serial.print ("Temp");
  Serial.print (temp);
  Cayenne.virtualWrite(1, temp, TYPE_TEMPERATURE, UNIT_FAHRENHEIT);
  Cayenne.virtualWrite(2, hum, TYPE_RELATIVE_HUMIDITY, UNIT_PERCENT);
}

CAYENNE_IN(0) 
{
  digitalWrite(2, !getValue.asInt());
}
