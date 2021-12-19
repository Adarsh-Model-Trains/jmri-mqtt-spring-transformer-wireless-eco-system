/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Config_h
#define Config_h
#include "Arduino.h"

enum BLOCK_STATES {
  UNOCCUPIED,                    //UOB
  OCCUPYING_FROM_START_OF_BLOCK, //OSB
  OCCUPYING_FROM_END_OF_BLOCK,   //OEB
  OCCUPIED,                      //OPB
};

/************************************************************************************************/
#define BROAD_RATE 115200
#define DELAY_TIME 200
#define ON LOW
#define OFF HIGH
#define PINS 2
/************************************************************************************************/
#define INVALID_SENSOR_NUMBER " INVLAID SENEOR NUMBER "
#define INVALID_SENSOR_PIN " INVLAID SENEOR PIN NO "
/************************************************************************************************/


/*
   IR SENSORS PIN CONFIGURATION
  const int sensorPin[NO_OF_BLOCKS][PINS] = {
  {BLOCK_1_END_PIN, BLOCK_1_START_PIN },
  {BLOCK_2_END_PIN, BLOCK_2_START_PIN },
  ..........
  {BLOCK_N_END_PIN, BLOCK_N_START_PIN }
  };
*/
#define NO_OF_BLOCKS 3
const int sensorPin[NO_OF_BLOCKS][PINS] = {
  {13, 12 },
  {12, 11},
  {11, 10}
};

#endif
