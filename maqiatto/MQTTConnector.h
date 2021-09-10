#ifndef ARDUINO_MQTTCONNECTOR_H
#define ARDUINO_MQTTCONNECTOR_H

#include <Arduino.h>

void    MQTTBegin();
void    MQTTLoop();
boolean MQTTPublish(const char* topic, char* payload);
boolean MQTTSubscribe(const char* topicToSubscribe);
boolean MQTTIsConnected();
int jumlah(int add);
int getIndoor();
int getOutdoor();
int getPayload();
void writeIndoor(int x);
void writeOutdoor(int x);

#endif /* ARDUINO_MQTTCONNECTOR_H */
