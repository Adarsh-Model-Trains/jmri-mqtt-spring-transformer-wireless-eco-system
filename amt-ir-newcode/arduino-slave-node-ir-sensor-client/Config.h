/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Config_h
#define Config_h
#include "Arduino.h"

/************************************************************************************************/
enum BLOCK_STATES {
  UNOCCUPIED,
  OCCUPYING_FROM_START_OF_BLOCK,
  OCCUPYING_FROM_END_OF_BLOCK,
  OCCUPIED,
};
#define ON LOW
#define OFF HIGH
#define ACTIVE ":AC\n"
#define INACTIVE ":IN\n"
#define PINS 2
#define BROAD_RATE 115200
#define DELAY_TIME 200
#define SEND_THRESHOLD 3
/************************************************************************************************/
#define INVALID_SENSOR_NUMBER " INVLAID SENEOR NUMBER "
#define INVALID_SENSOR_PIN " INVLAID SENEOR PIN NO "
/************************************************************************************************/
#define JMRI_SENSOR_START_ADDRESS 10000

/*
 * IR SENSORS PIN CONFIGURATION 
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
  {12, 11 },
  {11, 10 },
};

#endif
