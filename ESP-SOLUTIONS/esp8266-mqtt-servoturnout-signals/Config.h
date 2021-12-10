#ifndef Config_h
#define Config_h
#include "Arduino.h"

/************************************************************************************************/
#define T 'T'
#define L 'L'
#define S 'S'
#define O 'O'

#define THROWN "TH"
#define CLOSED "CL"
#define ON "ON"
#define OFF "OF"
#define MSG_SIZE  14
#define BROAD_RATE 115200
#define DELAY_TIME 200
#define WIFI_RECONNECT_DELAY_TIME 500
#define TOTAL_BOARD_PIN 16
#define RANGE_TYPE 2
#define PWM_LIGHT_FREQUENCY 1000
#define PWM_TURNOUT_FREQUENCY 50 
#define F0 0
#define F4096 4096
/************************************************************************************************/
#define REST_API_DISABLED "REST API IS NOT ENABLED FOR THIS NODE"
#define BOARDS_CONFIG "BOARD NUMBER EXCEEDED THE NO OF BOARD CONFIGURED"
#define TURNOUT_THROWN "TURNOUT THROW\n"
#define TURNOUT_CLOSE "TURNOUT CLOSE\n"
#define LED_ON " LED ON\n"
#define LED_OFF " LED OFF\n"
/************************************************************************************************/

// ESP8266 do not support 5G wifi connection
#define WIFI_SSID  "adarsh-model-trains"
#define WIFI_PASSWROD  "adarsh@model@trains"

// MQTT
// find this ip using ipconfig or check in router
#define MQTT_SERVER "192.168.0.188"
#define MQTT_USERNAME "adarsh"
#define MQTT_PASSORD "password"

// change the node "number/name"  based on the node default is 1 in this
#define MQTT_TOPIC "/amt/node/1/#"

// change the node "number/name"  based on the node
#define CLIENT_ID "JMRI_SUBSCRIBER_NODE_ESP8266_1"


// MUST BE EQUAL TO THE CONFIGURATION DEFINED IN SPRING
// APPLICATION NODE DEFINATION THEN ONLY THIS WILL WORK
#define NO_OF_TURNOUT_BOARDS 1
#define NO_OF_LIGHT_BOARDS 0
#define NO_OF_TOTAL_BOARDS 1


const bool signalLedTypeAnode = true;

/*
int turnoutRange[][TOTAL_BOARD_PIN][RANGE_TYPE] = {
  {  // BOARD 0 
    {OPEN_RANGE, CLOSE_RANGE},  // PIN 0
    {OPEN_RANGE, CLOSE_RANGE}   // PIN 1
    ........
   },
   {  // BOARD 1 
    {OPEN_RANGE, CLOSE_RANGE},  // PIN 0
    {OPEN_RANGE, CLOSE_RANGE}   // PIN 1
    ........
   },
   
   ........
   ........
   
   {  // BOARD N 
    {OPEN_RANGE, CLOSE_RANGE},  // PIN 0
    {OPEN_RANGE, CLOSE_RANGE}   // PIN 1
    ........
   }
};
*/
const int turnoutRange[][TOTAL_BOARD_PIN][RANGE_TYPE] = {
  {
    {1350, 1650},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000}
  },
  {
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000},
    {1000, 2000}
  }
};


#endif
