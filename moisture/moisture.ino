#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define moisture 35 // độ ẩm đất 

char auth[] = "nu4ECQzxb4adsFRKhWqhKp25Cyo3my7K";
char ssid[] = "To Hien";
char pass[] = "12342345";

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode (moisture, INPUT);

}

void loop() {
  Blynk.run();
  int moisture_value = analogRead(moisture); //độ ẩm đất
  Serial.print("moisture_value: ");
  Serial.println(moisture_value);
  moisture_value = map(moisture_value,0,4000,0,100);
  //App Blynk
  Blynk.virtualWrite(V7, moisture_value);
  Serial.print("moisture_valuezzz: ");
  Serial.println(moisture_value);
  delay(1000);
}
