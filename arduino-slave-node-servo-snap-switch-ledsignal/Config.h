/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Config_h
#define Config_h
#include "Arduino.h"

#define T 'T'
#define L 'L'
#define S 'S'
#define O 'O'
#define M 'M'
#define N 'N'

#define THROWN "TH"
#define CLOSED "CL"
#define ON "ON"
#define OFF "OF"
#define MSG_SIZE  14
#define BROAD_RATE 115200
#define DELAY_TIME 200
#define TOTAL_BOARD_PIN 16
#define PWM_LIGHT_FREQUENCY 1000
#define PWM_SNAP_TURNOUT_FREQUENCY 1000
#define PWM_SERVO_TURNOUT_FREQUENCY 50 
#define DEFAULT_OPEN 1000
#define DEFAULT_CLOSE 2000

/*----------------------------------------------------------------------------------*/
// MUST BE EQUAL TO THE CONFIGURATION DEFINED IN SPRING
// APPLICATION NODE DEFINATION THEN ONLY THIS WILL WORK


#define NO_OF_SERVO_TURNOUT_BOARDS 1
#define NO_OF_SNAP_TURNOUT_BOARDS 1
#define NO_OF_LIGHT_BOARDS 3
#define NO_OF_TOTAL_BOARDS 5
/*----------------------------------------------------------------------------------*/

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
#define RANGE_TYPE 2
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
  }
};
const bool slowMove = true;


#endif
