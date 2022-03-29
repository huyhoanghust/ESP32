#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define water 35// cảm biến mức nước
char auth[] = "nu4ECQzxb4adsFRKhWqhKp25Cyo3my7K";
char ssid[] = "To Hien";
char pass[] = "12342345";
void setup() {
  Serial.begin(9600);
  pinMode (water, INPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  int water_level = analogRead(water); //mức nước
  water_level = map(water_level,0,2000,0,500);
  Serial.println(water_level);
  delay(2000);
  Blynk.virtualWrite(V4, water_level);
}
