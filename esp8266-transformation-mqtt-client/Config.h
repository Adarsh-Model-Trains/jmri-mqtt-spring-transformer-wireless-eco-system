
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Config_h
#define Config_h
#include "Arduino.h"

// WiFi
// Make sure to update this for your own WiFi network!
#define ssid "adarsh_radha_2G" // ESP8266 do not support 5G wifi connection
#define wifi_password "******"
#define mqtt_username "adarsh"
#define mqtt_password "password"

// MQTT
// find this ip using ipconfig or check in router
#define mqtt_server "192.168.0.188"

// change the node "number/name"  based on the node default is 1 in this
#define mqtt_topic "/amt/node/1/#"
#define mqtt_topic_light "/amt/node/1/light/"
#define mqtt_topic_turnout "/amt/node/1/turnout/"
#define mqtt_topic_signalhead "/amt/node/1/signal/"

// change the node "number/name"  based on the node
#define clientID "JMRI_SUBSCRIBER_NODE_ESP8266_1"

#define BROAD_RATE 115200
#define DELAY_TIME 1000

#endif
