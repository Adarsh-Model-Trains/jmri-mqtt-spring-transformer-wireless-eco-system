/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Config_h
#define Config_h
#include "Arduino.h"

#define ON LOW
#define OFF HIGH

#define JMRI_SENSOR_START_ADDRESS 10000
#define BROAD_RATE 115200
#define DELAY_TIME 5000
#define ACTIVE ":AC\n"
#define INACTIVE ":IN\n"
#define NO_OF_BLOCKS 3

/*
 * IR SENSORS PIN CONFIGURATION 
  const int sensorPin[NO_OF_BLOCKS][PINS] = {
  {BLOCK_1_END_PIN, BLOCK_1_START_PIN },
  {BLOCK_2_END_PIN, BLOCK_2_START_PIN },
  ..........
  {BLOCK_N_END_PIN, BLOCK_N_START_PIN }
  };
*/
#define PINS 2
const int sensorPin[NO_OF_BLOCKS][PINS] = {
  {13, 12 },
  {11, 10 },
  {9, 8}
};

#endif
