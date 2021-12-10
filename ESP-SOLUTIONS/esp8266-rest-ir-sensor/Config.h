#ifndef Config_h
#define Config_h
#include "Arduino.h"

/************************************************************************************************/
#define PINS 2
#define JMRI_SENSOR_START_ADDRESS 10000
#define BROAD_RATE 115200
#define DELAY_TIME 1000
#define WIFI_RECONNECT_DELAY_TIME 500
#define ON LOW
#define OFF HIGH
#define CONTENT_TYPE "Content-Type"
#define CONTENT_TYPE_VAL "application/json"
#define PAYLOAD_FROUNT "{\"topic\": \"/trains/track/sensor/"
#define PAYLOAD_BACK_ACTIVE "\", \"data\": \"ACTIVE\"}"
#define PAYLOAD_BACK_INACTIVE "\", \"data\": \"INACTIVE\"}"
#define SEND_THRESHOLD 3
/************************************************************************************************/
#define WIFI_MSG_F " NOT CONNECTED TO WIFI "
#define INVALID_SENSOR_NUMBER " INVLAID SENEOR NUMBER "
#define INVALID_SENSOR_PIN " INVLAID SENEOR PIN NO "
/************************************************************************************************/

// ESP8266 do not support 5G wifi connection
#define WIFI_SSID "adarsh-model-trains"
#define WIFI_PASSWROD "adarsh@model@trains"

// IP OF THE SERVER MACHINE WHERE SPRING TRANSFORMER IS RUNNING
#define SERVER_URL "http://192.168.0.188:8090/amt/node/1"
#define NODE_ID "1"

#define NO_OF_BLOCKS 3

/*
   IR SENSORS PIN CONFIGURATION
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

#endif
