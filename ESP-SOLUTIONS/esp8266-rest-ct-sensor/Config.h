
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

// ESP8266 do not support 5G wifi connection
#define WIFI_SSID "adarsh-model-trains"
#define WIFI_PASSWROD "adarsh@model@trains"

// IP OF THE SERVER MACHINE WHERE SPRING TRANSFORMER IS RUNNING
#define SERVER_URL "http://192.168.0.188:8090/amt/node/1"
#define NODE_ID "1"

#define JMRI_SENSOR_START_ADDRESS 10000

#define ENABLE_PULLUP true
#define NO_OF_BLOCKS 2

/*
 * CT SENSORS PIN CONFIGURATION 
  const int sensorPin[NO_OF_BLOCKS][PINS] = {
  BLOCK_1__PIN,
  BLOCK_2_PIN,
  ..........
  BLOCK_N_PIN
  };
*/

const int sensorPin[NO_OF_BLOCKS] = {
  7, 6
};

/************************************************************************************************/
#endif
