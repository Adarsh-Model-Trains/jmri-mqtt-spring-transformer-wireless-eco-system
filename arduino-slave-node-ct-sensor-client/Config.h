/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Config_h
#define Config_h
#include "Arduino.h"


#define JMRI_SENSOR_START_ADDRESS 10000
#define BROAD_RATE 115200
#define DELAY_TIME 5000
#define ACTIVE ":AC\n"
#define INACTIVE ":IN\n"
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

#endif
