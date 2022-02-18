
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

// IP AND PORT THE SERVER MACHINE WHERE SPRING TRANSFORMER IS RUNNING
const String SERVER_IP_PORT = "192.168.0.188:8090";
const String NODE_ID = "1";
const String SERVICE_URL = "/amt/node/";
const String SERVER_URL = "http://" + SERVER_IP_PORT + SERVICE_URL + NODE_ID;

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
