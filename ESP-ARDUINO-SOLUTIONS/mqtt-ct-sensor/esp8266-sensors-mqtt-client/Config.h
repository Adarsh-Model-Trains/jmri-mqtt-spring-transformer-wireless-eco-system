/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Config_h
#define Config_h
#include "Arduino.h"

/************************************************************************************************/
#define ACTIVE "ACTIVE"
#define INACTIVE "INACTIVE"
#define ACT "AC"
#define BROAD_RATE 115200
#define DELAY_TIME 5000
#define WIFI_RECONNECT_DELAY_TIME 500
/************************************************************************************************/

// WiFi
// Make sure to update this for your own WiFi network!
#define WIFI_SSID "adarsh-model-trains" // ESP8266 do not support 5G wifi connection
#define WIFI_PASSWROD "adarsh@model@trains"

// MQTT
// find this ip using ipconfig or check in router
#define  MQTT_SERVER  "192.168.0.188"
#define  MQTT_USER "adarsh"
#define  MQTT_PWD "password"

// change the node "number/name"  based on the node default is 1 in this
#define JMRI_MQTT_TOPIC  "/trains/track/#"
#define JMRI_MQTT_SENSOR_TOPIC "/trains/track/sensor/"

// change the node "number/name"  based on the node
#define CLIENT_ID  "JMRI_NODE_ESP8266_PUBLISHING_1"

#endif
