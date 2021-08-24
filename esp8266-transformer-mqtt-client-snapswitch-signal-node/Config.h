#ifndef Config_h
#define Config_h
#include "Arduino.h"

#define T 'T'
#define L 'L'
#define S 'S'

#define THROWN "TH"
#define CLOSED "CL"
#define ON "ON"
#define OFF "OF"
#define MSG_SIZE  14
#define BROAD_RATE 115200
#define DELAY_TIME 200
#define PWM_FREQUENCY 1000
/*----------------------------------------------------------------------------------*/
// MUST BE EQUAL TO THE CONFIGURATION DEFINED IN SPRING
// APPLICATION NODE DEFINATION THEN ONLY THIS WILL WORK

#define NO_OF_TURNOUT_BOARDS 2
#define NO_OF_LIGHT_BOARDS 1
#define NO_OF_TOTAL_BOARDS 11
/*----------------------------------------------------------------------------------*/
#define TOTAL_BOARD_PIN 16


// ESP8266 do not support 5G wifi connection
#define WIFI_SSID  "adarsh_radha_2G"
#define WIFI_PASSWROD  "*********"

// MQTT
// find this ip using ipconfig or check in router
#define MQTT_SERVER "192.168.0.188"
#define MQTT_USERNAME "adarsh"
#define MQTT_PASSORD "password"

// change the node "number/name"  based on the node default is 1 in this
#define MQTT_TOPIC "/amt/node/1/#"

// change the node "number/name"  based on the node
#define CLIENT_ID "JMRI_SUBSCRIBER_NODE_ESP8266_1"

#endif
