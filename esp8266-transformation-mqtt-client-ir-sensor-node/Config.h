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
#define SS_ID "adarsh_radha_2G" // ESP8266 do not support 5G wifi connection
#define WIFI_PWD "******"
#define  MQTT_USER "adarsh"
#define  MQTT_PWD "password"

// MQTT
// find this ip using ipconfig or check in router
#define  MQTT_SERVER  "192.168.0.188"

// change the node "number/name"  based on the node default is 1 in this
#define JMRI_MQTT_TOPIC  "/trains/track/#"
#define JMRI_MQTT_SENSOR_TOPIC "/trains/track/sensor/"

// change the node "number/name"  based on the node
#define CLIENT_ID  "JMRI_NODE_ESP8266_PUBLISHING_1"

#define BROAD_RATE 115200
#define DELAY_TIME 5000
#define ACTIVE "ACTIVE"
#define INACTIVE "INACTIVE"
#define ON LOW
#define OFF HIGH
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
#define PINS 2
const int sensorPin[NO_OF_BLOCKS][PINS] = {
  {13, 12 },
  {11, 10 },
  {9, 8}
};

#endif
