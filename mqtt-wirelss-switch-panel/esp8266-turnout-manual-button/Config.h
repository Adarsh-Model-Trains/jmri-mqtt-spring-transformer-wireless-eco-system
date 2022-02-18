/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Config_h
#define Config_h
#include "Arduino.h"
#include "DefaultConfig.h"
/************************************************************************************************/
#define NO_OF_TOTAL_BOARDS 1
const int SERVO_TURNOUT_START_ADDRESS = 40000;
const int TOTOAL_SERVO_TURNOUT = 2;
const int SNAP_TURNOUT_START_ADDRESS = 50000;
const int TOTOAL_SNAP_TURNOUT = 2;
const bool signalLedTypeAnode = true;

// ESP8266 do not support 5G wifi connection
#define WIFI_SSID "adarsh-model-trains"
#define WIFI_PASSWROD "adarsh@model@trains"

// MQTT
// find this ip using ipconfig or check in router
#define  MQTT_SERVER  "192.168.0.188"
#define  MQTT_USER "adarsh"
#define  MQTT_PWD "password"

// change the node "number/name"  based on the node default is 1 in this
#define JMRI_MQTT_SUBSCRIBING_TOPIC "/trains/track/turnout/#"
#define JMRI_MQTT_PUBLISHING_TOPIC  "/trains/track/turnout/"

// change the node "number/name"  based on the node
#define CLIENT_ID  "JMRI_NODE_ESP8266_MANUAL_TURNOUT_NODE_1"

/************************************************************************************************/
#endif
