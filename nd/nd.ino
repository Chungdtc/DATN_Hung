#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float nd = 0; 
float da=0;
void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  pinMode(A5,INPUT);
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h)|| isnan(t)) {}
  else {
    da = h;
    nd = t;
  }
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print("%");
  Serial.println();
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println();
  Serial.print(map(analogRead(A5),0,1023,100,0));
  Serial.print(F("% "));
  Serial.println();
}
