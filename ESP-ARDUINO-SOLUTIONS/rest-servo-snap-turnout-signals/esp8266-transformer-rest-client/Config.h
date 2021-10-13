#ifndef Config_h
#define Config_h
#include "Arduino.h"

// ESP8266 do not support 5G wifi connection
#define WIFI_SSID "adarsh_radha_2G"
#define WIFI_PASSWROD "*******"

// IP OF THE SERVER MACHINE WHERE SPRING TRANSFORMER IS RUNNING 
#define SERVER_URL "http://192.168.0.188:8090/amt/node/1"
#define NODE_ID "1"

#define BROAD_RATE 115200
#define DELAY_TIME 5000
#define WIFI_RECONNECT_DELAY_TIME 500

#endif
