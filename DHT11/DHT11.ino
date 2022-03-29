#include "DHT.h"   //temperature
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = "nu4ECQzxb4adsFRKhWqhKp25Cyo3my7K";
char ssid[] = "To Hien";
char pass[] = "12342345";
#define DHTPIN 32    // cảm biến nhiệt độ
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin(); // cảm biến nhiệt độ
  Blynk.begin(auth, ssid, pass);
}
void loop () {
  Blynk.run();
  float h = dht.readHumidity();   //đọc độ ẩm không khí 
  float t = dht.readTemperature(); // đọc nhiệt độ
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V5, h);
  Serial.print(h );
  Serial.println(t );
  delay(2000);
}
