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
/************************************************************************************************/
#endif
