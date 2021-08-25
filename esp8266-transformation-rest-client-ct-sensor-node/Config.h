#ifndef Config_h
#define Config_h
#include "Arduino.h"

// ESP8266 do not support 5G wifi connection
#define WIFI_SSID "adarsh_radha_2G"
#define WIFI_PASSWROD "********"

// IP OF THE SERVER MACHINE WHERE SPRING TRANSFORMER IS RUNNING
#define SERVER_URL "http://192.168.0.188:8090/amt/node/1"
#define NODE_ID "1"

#define CONTENT_TYPE "Content-Type"
#define CONTENT_TYPE_VAL "application/json"
#define JMRI_SENSOR_START_ADDRESS 10000
#define BROAD_RATE 115200
#define DELAY_TIME 1000
#define ACTIVE "ACTIVE"
#define INACTIVE "INACTIVE"
#define ACT "AC"

#define PAYLOAD_FROUNT "{\"topic\": \"/trains/track/sensor/"
#define PAYLOAD_BACK_ACTIVE "\", \"data\": \"ACTIVE\"}"
#define PAYLOAD_BACK_INACTIVE "\", \"data\": \"INACTIVE\"}"

/*
 * CT SENSORS PIN CONFIGURATION 
  const int sensorPin[NO_OF_BLOCKS][PINS] = {
  BLOCK_1__PIN,
  BLOCK_2_PIN,
  ..........
  BLOCK_N_PIN
  };
*/
#define NO_OF_BLOCKS 2
const int sensorPin[NO_OF_BLOCKS] = {
  7, 6
};
#endif
