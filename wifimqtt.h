#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include "credentials.h"
extern byte led;
extern byte pump;
extern byte light;


String clientID ="ESP32-";
const char* mqttServer = "192.168.161.223";
const char* mqttUser = "admin";
const char* mqttPassword = "9203";
WiFiClient espClient;
PubSubClient client( espClient );


void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
       clientID += String(random(0xffff),HEX);

        if (client.connect(clientID.c_str(), mqttUser, mqttPassword)) 
        {
            Serial.println("connected");
            client.subscribe("fromnodered");
            client.subscribe("ledstate");
            client.subscribe("home/actuators/fan");
            client.subscribe("home/actuators/pump");
            client.subscribe("home/actuators/light");
            client.subscribe("jsonfromnodered");
            
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" trying again in 5 seconds...");
            delay(5000);
        }
    }
}

void callback (char *topic , byte *message ,unsigned int length)
{
    String messageTemp;
    for(int i=0; i<length;i++){
        messageTemp += (char)message[i];
    }

    if (String(topic)=="fromnodered")
    {
        Serial.println(messageTemp);
    }
    else if (String(topic)=="home/actuators/fan")
    {
        if(messageTemp == "1"){
            digitalWrite(led ,LOW);
        }
        else if(messageTemp == "0"){
            digitalWrite(led , HIGH);
        }
    }
    else if (String(topic)=="home/actuators/pump")
    {
        if(messageTemp == "1"){
            digitalWrite(pump , LOW);
        }
        else if(messageTemp == "0"){
            digitalWrite(pump , HIGH);
        }
    }
    else if (String(topic)=="home/actuators/light")
    {
        if(messageTemp == "1"){
            digitalWrite(light , LOW);
        }
        else if(messageTemp == "0"){
            digitalWrite(light , HIGH);
        }
    }
    if (String(topic)=="jsonfromnodered")
    {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, messageTemp);

        if (error)
         {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return;
        }

        const char* device = doc["device"]; 
        int temperature = doc["temperature"]; 
        int humidity = doc["humidity"]; 
        int lux = doc["lux"]; 
        String output =  String(device)+" +"+String(temperature)+" "+String(humidity)+" "+String(lux);
        Serial.println(output);
    }
}

void connectAP() 
{
    Serial.println("Connecting to WiFi...");
    WiFi.begin (ssid, password);
    byte cnt =0 ;
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
        cnt ++;
        if (cnt>30)
        {
            ESP.restart();

        }
    }

}

