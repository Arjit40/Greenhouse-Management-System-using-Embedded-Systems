#include <Arduino.h>
#include <ArduinoJson.h>
#include "wifimqtt.h"
#include <Wire.h>
#include <DHT.h>

byte led = 21; 
byte pump =18;
byte light=2;




const int LDR_PIN  = 36;
const int soilPin  = 34;
const int mq3Pin = 35;
const int DHTPIN   = 4;
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
  float temperature = NAN;
  float humidity = NAN;

  int ldrValue;

  int soilValue = 0;
  const int wetThreshold = 900;  
  const int dryThreshold = 4095;
  int moisturePercent;

  int alcoholPercent;


void sendsensorvaluesmqtt(){
  DynamicJsonDocument doc(1024);
  doc["temperature"]= temperature;
  doc["humidity"]= humidity;
  doc["lux"]= ldrValue;
  doc["SoilMoisture"]= moisturePercent;
  doc["CO2 level"]= alcoholPercent;

  char buff[256];
  serializeJson(doc, buff);
  client.publish("Greenhouse",buff);
}

void printsensorvalues(){
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C ");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Light intensity: ");
  Serial.print(ldrValue);
  Serial.println(" lx");

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.println(" %");

  Serial.print("CO2 Level: ");
  Serial.print(alcoholPercent);
  Serial.println(" %");

}
unsigned long previousmillis = millis();

void setup() {
  Serial.begin(115200);
 
  pinMode(led, OUTPUT);

  pinMode(pump, OUTPUT);

  pinMode(light, OUTPUT);


  dht.begin();
  Serial.println("Initializing DHT22 sensor...");
  connectAP();
   Serial.println("\nWiFi Connected!");
  Serial.print("ESP32 IP: ");  
  Serial.println(WiFi.localIP());
 
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
  


}

void loop(){
  if(!client.connected()){
    reconnect();
  }
  if(!client.loop()){
    client.connect("ESP32-");
   
  }


  unsigned long currentmillis = millis();
  if(currentmillis - previousmillis > 5000){
    previousmillis = currentmillis;
   
     ldrValue = analogRead(LDR_PIN); 

     int mq3Value = analogRead(mq3Pin);
     alcoholPercent = map(mq3Value, 0, 4095, 0, 100);


     soilValue = analogRead(soilPin);
     moisturePercent = map(soilValue, dryThreshold,wetThreshold, 0, 100);

  
  if (moisturePercent < 0) moisturePercent = 0;
  if (moisturePercent > 100) moisturePercent = 100;
  
  for (int attempts = 0; attempts < 5; attempts++) 
  {
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    if (!isnan(humidity) && !isnan(temperature)) 
    {
      break;  
    }

    Serial.println("Failed to read from DHT sensor. Retrying...");
    delay(1000);  
  }

  if (!isnan(humidity) && !isnan(temperature)) {
    Serial.print("-----HELLO ARJIT & SARASWATI-------\n");
    Serial.print("-----GREENHOUSE MANAGEMENT USING EMBEDDED SYSTEM ---------\n");
  } else {
    Serial.println("❌ Could not read valid data from DHT22 after multiple attempts.");
  }


 printsensorvalues();
 sendsensorvaluesmqtt();
  
  }
    
}n
