/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef DefaultConfig_h
#define DefaultConfig_h
#include "Arduino.h"
/************************************************************************************************/
#define CONTENT_TYPE "Content-Type"
#define CONTENT_TYPE_VAL "application/json"
#define ACT "AC"
#define ACTIVE "ACTIVE"
#define INACTIVE "INACTIVE"
#define PAYLOAD_FROUNT "{\"topic\": \"/trains/track/sensor/"
#define PAYLOAD_BACK_ACTIVE "\", \"data\": \"ACTIVE\"}"
#define PAYLOAD_BACK_INACTIVE "\", \"data\": \"INACTIVE\"}"
#define BROAD_RATE 115200
#define DELAY_TIME 1000
#define WIFI_RECONNECT_DELAY_TIME 500
/************************************************************************************************/
#endif
