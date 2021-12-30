/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef DefaultConfig_h
#define DefaultConfig_h
#include "Arduino.h"
/************************************************************************************************/

enum BLOCK_STATES {
  UNOCCUPIED,                    //UOB
  OCCUPYING_FROM_START_OF_BLOCK, //OSB
  OCCUPYING_FROM_END_OF_BLOCK,   //OEB
  OCCUPIED,                      //OPB
};

#define ON LOW
#define OFF HIGH
#define ACTIVE ":AC\n"
#define INACTIVE ":IN\n"
#define PINS 2
#define BROAD_RATE 115200
#define DELAY_TIME 200
#define SEND_THRESHOLD 3

#define INVALID_SENSOR_NUMBER " INVLAID SENEOR NUMBER "
#define INVALID_SENSOR_PIN " INVLAID SENEOR PIN NO "
/************************************************************************************************/

#endif
