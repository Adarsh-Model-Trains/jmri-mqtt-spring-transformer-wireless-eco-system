/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Config_h
#define Config_h
#include "Arduino.h"

/************************************************************************************************/
#define T 'T'
#define L 'L'
#define S 'S'
#define O 'O'
#define E 'E'
#define THROWN "TH"
#define CLOSED "CL"
#define ON "ON"
#define OFF "OF"
#define MSG_SIZE  14
#define TOTAL_BOARD_PIN 16
#define PWM_FREQUENCY 1000
#define BROAD_RATE 115200
#define DELAY_TIME 200
#define F0 0
#define F4096 4096
/************************************************************************************************/
#define REST_API_DISABLED "REST API IS NOT ENABLED FOR THIS NODE"
#define NO_DATA_AVALIABLE "NO DATA AVALIABLE FOR THIS NODE"
#define BOARDS_CONFIG "BOARD NUMBER EXCEEDED THE NO OF BOARD CONFIGURED"
#define TURNOUT_THROW "TURNOUT THROW\n"
#define TURNOUT_CLOSE "TURNOUT CLOSE\n"
#define LED_ON " LED ON\n"
#define LED_OFF " LED OFF\n"
/************************************************************************************************/

const bool signalLedTypeAnode = true;

// MUST BE EQUAL TO THE CONFIGURATION DEFINED IN SPRING
// APPLICATION NODE DEFINATION THEN ONLY THIS WILL WORK
#define NO_OF_TURNOUT_BOARDS 2
#define NO_OF_LIGHT_BOARDS 2
#define NO_OF_TOTAL_BOARDS 4

#endif
