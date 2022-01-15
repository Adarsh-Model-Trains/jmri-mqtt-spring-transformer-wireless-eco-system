/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Config_h
#define Config_h
#include "Arduino.h"

/************************************************************************************************/
#define BROAD_RATE 115200
#define DELAY_TIME 1000
#define THROWN ":TH\n"
#define CLOSED ":CL\n"
/************************************************************************************************/

#define NO_OF_TURNOUT 2
/*
  NO_OF_TURNOUT  2
  cont int swtichs[][NO_OF_TURNOUT][3] = {
    { THROW_PIN_NO, CLOSE_PIN_NO, JMRIADDRESS, THROW_STATE, CLOSE_STATE },
    { THROW_PIN_NO, CLOSE_PIN_NO, JMRIADDRESS, THROW_STATE, CLOSE_STATE },

  };
*/
const int swtichs[NO_OF_TURNOUT][5] = {
  {3, 4, 40001, 0, 0},
  {5, 6, 50001, 0, 0},
};

#endif
