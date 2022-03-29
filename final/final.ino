#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"   //temperature


#define moisture 34 // độ ẩm đất 
#define pump 27  // relay control motor
#define DHTPIN 32    // cảm biến nhiệt độ
#define water 35// cảm biến mức nước
#define buzzer 33  //buzzer
#define MANUAL 1
#define AUTO 0

int MODE = MANUAL;
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

char auth[] = "nu4ECQzxb4adsFRKhWqhKp25Cyo3my7K"; //"jtkRthVUNn7EwTfdO7t-ulix5F49oWqX";
char ssid[] = "Bat ho";
char pass[] = "21903002";

boolean state = false;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin(); // cảm biến nhiệt độ
  pinMode (moisture, INPUT);
  pinMode (pump, OUTPUT);
  pinMode (water, INPUT);
  pinMode (buzzer, OUTPUT);

}

void loop() {
  
  Blynk.run();
  float h = dht.readHumidity();   //đọc độ ẩm không khí 
  float t = dht.readTemperature(); // đọc nhiệt độ
  Serial.println(h);
  Serial.println(t);
  int moisture_value = analogRead(moisture); //độ ẩm đất
  Serial.println(moisture_value);
  int water_level = analogRead(water); //mức nước
  water_level = map(water_level,0,2000,0,500);
  moisture_value = map(moisture_value,500,4100,100,0); 
  if (MODE == AUTO){
    if (moisture_value < 55)
    {
      digitalWrite(pump,HIGH);
      digitalWrite(buzzer, HIGH);
      delay(3000);
    }
    else
    {
      digitalWrite(pump,LOW);
      digitalWrite(buzzer, LOW);
    }
    Serial.println("Mode Auto");
  }
  else
  {
    if (water_level < 100)
    {
    Blynk.notify("The bottle is empty. Refill required...");
    }
    if (moisture_value < 45)
    {
    Blynk.notify("I need water...");
    }
      Serial.println("Mode Manual");
  }
  
  //App Blynk
  Blynk.virtualWrite(V7, moisture_value);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V4, water_level);
}

//bơm
BLYNK_WRITE(V1)
{
  if (MODE == AUTO)
  {
    Serial.println("Trong mode Auto");
  }
  else
  {
    Serial.println("Trong mode Manual");
  //tưới nước
    if (state == false) {
      state = true;
      digitalWrite(pump,HIGH);
      digitalWrite(buzzer,HIGH);
 
    }
  //ngừng tưới
    else {
      state = false;
      digitalWrite(pump,LOW);
      digitalWrite(buzzer, LOW);
    }
  }
  Serial.println("V1");
}

BLYNK_WRITE(V2)
{
  MODE = param.asInt();
}
