#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht (DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("DHT Test");
  dht.begin();
}


void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("fallo datos");
    return;
    }

  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print ("Humedad");
  Serial.print(h);

}
