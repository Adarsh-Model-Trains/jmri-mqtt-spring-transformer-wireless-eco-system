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

#define THROWN "TH"
#define CLOSED "CL"
#define ON "ON"
#define OFF "OF"
#define MSG_SIZE  14
#define BROAD_RATE 115200
#define DELAY_TIME 200
#define PWM_FREQUENCY 1000
/*----------------------------------------------------------------------------------*/
// MUST BE EQUAL TO THE CONFIGURATION DEFINED IN SPRING
// APPLICATION NODE DEFINATION THEN ONLY THIS WILL WORK


#define NO_OF_TURNOUT_BOARDS 2
#define NO_OF_LIGHT_BOARDS 1
#define NO_OF_TOTAL_BOARDS 11
/*----------------------------------------------------------------------------------*/


#define TOTAL_BOARD_PIN 16
#endif
