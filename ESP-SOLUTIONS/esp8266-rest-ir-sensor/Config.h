
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
/************************************************************************************************/
#endif
