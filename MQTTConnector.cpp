#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <elapsedMillis.h>

#include "MQTTConnector.h"
#include "Credentials.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

boolean mqttInitCompleted = false;
String clientId = "IoTPractice-" + String(ESP.getChipId());
int indoor, outdoor, datapayload;
/* Incoming data callback. */
void dataCallback(char* topic, byte* payload, unsigned int length)
{
  char payloadStr[length + 1];
  memset(payloadStr, 0, length + 1);
  strncpy(payloadStr, (char*)payload, length);
  Serial.printf("Data    : dataCallback. Topic : [%s]\n", topic);
  Serial.printf("Data    : dataCallback. Payload : %s\n", payloadStr);
  if (topic = "aryanathaaa@gmail.com/motion") {
    Serial.printf("aryanathaaa@gmail.com/motion \n");

    if (payloadStr[0] == '1') {
      indoor = 1;
      datapayload = 1;
    
    }
    if (payloadStr[0] == '2') {
      outdoor = 1;
      datapayload = 2;
    }
    
    //current = atoi(payloadStr);
    
    
//    if (timer > 3000) {
//      indoor = 0;
//      outdoor = 0;
//      Serial.println("timeout");
//    }
//    
//    if (indoor == 1 && outdoor == 1) {
//      //timeout = 0;
//      if (last == 2 && current == 1) {
//        stat = 1; //masuk
//        Serial.println("Masuk");
//      }
//      else if (last == 1 && current == 2) {
//        stat = 2; // keluar
//        Serial.println("Keluar");
//      }
//
//      last = current;
//    }
  }
}

void performConnect()
{
  uint16_t connectionDelay = 5000;
  while (!mqttClient.connected())
  {
    Serial.printf("Trace   : Attempting MQTT connection...\n");
    if (mqttClient.connect(clientId.c_str(), MQTT_USERNAME, MQTT_KEY))
    {
      Serial.printf("Trace   : Connected to Broker.\n");

      /* Subscription to your topic after connection was succeeded.*/
      MQTTSubscribe(TOPIC);
    }
    else
    {
      Serial.printf("Error!  : MQTT Connect failed, rc = %d\n", mqttClient.state());
      Serial.printf("Trace   : Trying again in %d msec.\n", connectionDelay);
      delay(connectionDelay);
    }
  }
}

boolean MQTTPublish(const char* topic, char* payload)
{
  boolean retval = false;
  if (mqttClient.connected())
  {
    retval = mqttClient.publish(topic, payload);
  }
  return retval;
}

boolean MQTTSubscribe(const char* topicToSubscribe)
{
  boolean retval = false;
  if (mqttClient.connected())
  {
    retval = mqttClient.subscribe(topicToSubscribe);
  }
  return retval;
}

boolean MQTTIsConnected()
{
  return mqttClient.connected();
}

void MQTTBegin()
{
  mqttClient.setServer(MQTT_BROKER, MQTT_BROKER_PORT);
  mqttClient.setCallback(dataCallback);
  mqttInitCompleted = true;
}

void MQTTLoop()
{
  if (mqttInitCompleted)
  {
    if (!MQTTIsConnected())
    {
      performConnect();
    }
    mqttClient.loop();
  }
}
void writeIndoor(int x) {
  indoor = x;
}
void writeOutdoor(int x) {
  outdoor = x;
}
int getIndoor() {
  return indoor; 
}
int getOutdoor() {
  return outdoor; 
}
int getPayload() {
  return datapayload; 
}
