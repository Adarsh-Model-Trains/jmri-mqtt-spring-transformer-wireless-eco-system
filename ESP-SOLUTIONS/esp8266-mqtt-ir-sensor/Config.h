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

// WiFi
// Make sure to update this for your own WiFi network!
// ESP8266 do not support 5G wifi connection
#define WIFI_SSID "adarsh-model-trains"
#define WIFI_PASSWROD "adarsh@model@trains"

// MQTT
// find this ip using ipconfig or check in router
#define MQTT_SERVER "192.168.0.188"
#define MQTT_USERNAME "adarsh"
#define MQTT_PASSORD "password"

// change the node "number/name"  based on the node
#define CLIENT_ID  "JMRI_NODE_ESP8266_PUBLISHING_1"

#define JMRI_SENSOR_START_ADDRESS 10000
#define NO_OF_BLOCKS 3

/*
 * IR SENSORS PIN CONFIGURATION 
  const int sensorPin[NO_OF_BLOCKS][PINS] = {
  {BLOCK_1_END_PIN, BLOCK_1_START_PIN },
  {BLOCK_2_END_PIN, BLOCK_2_START_PIN },
  ..........
  {BLOCK_N_END_PIN, BLOCK_N_START_PIN }
  };
*/

const int sensorPin[NO_OF_BLOCKS][PINS] = {
  {13, 12 },
  {11, 10 },
  {9, 8}
};
/************************************************************************************************/
#endif
