#ifndef Config_h
#define Config_h
#include "Arduino.h"
#include "DefaultConfig.h"

/************************************************************************************************/
const bool signalLedTypeAnode = false;

// MUST BE EQUAL TO THE CONFIGURATION DEFINED IN SPRING
// APPLICATION NODE DEFINATION THEN ONLY THIS WILL WORK
#define NO_OF_TURNOUT_BOARDS 2
#define NO_OF_LIGHT_BOARDS 1
#define NO_OF_TOTAL_BOARDS 11

// ESP8266 do not support 5G wifi connection
#define WIFI_SSID  "adarsh-model-trains"
#define WIFI_PASSWROD  "adarsh@model@trains"

// MQTT
// find this ip using ipconfig or check in router
#define MQTT_SERVER "192.168.0.188"
#define MQTT_USERNAME "adarsh"
#define MQTT_PASSORD "password"

// change the node "number/name"  based on the node default is 1 in this
#define MQTT_TOPIC "/amt/node/1/#"

// change the node "number/name"  based on the node
#define CLIENT_ID "JMRI_SUBSCRIBER_NODE_ESP8266_1"

/************************************************************************************************/
#endif
