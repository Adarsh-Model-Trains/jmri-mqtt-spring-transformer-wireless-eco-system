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

// MUST BE EQUAL TO THE CONFIGURATION DEFINED IN SPRING
// APPLICATION NODE DEFINATION THEN ONLY THIS WILL WORK
#define NO_OF_TURNOUT_BOARDS 2
#define NO_OF_LIGHT_BOARDS 9
#define NO_OF_TOTAL_BOARDS 11
const bool signalLedTypeAnode = false;
const bool slowMove = true;
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
/************************************************************************************************/
#endif
