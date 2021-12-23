/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Pca9685BoardManager_h
#define Pca9685BoardManager_h

#include <Arduino.h>
#include "Adafruit_PWMServoDriver.h"
#include "Config.h"

class Pca9685BoardManager {

  private:
    int _boardAddress[64] = {
      0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
      0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
      0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
      0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F
    };
    int index = 0;
    Adafruit_PWMServoDriver * _pwmBoards;
    char * _pwmBoardTypes;


  public:
    Pca9685BoardManager()  {
    }

    void initPca9685Boards();
    bool switchThrow(int boardId, int pinId);
    bool switchClose(int boardId, int pinId);
    bool switchOnLight(int boardId, int pinId);
    bool switchOffLight(int boardId, int pinId);
    bool switchOnSignal(int boardId, int pinId);
    bool switchOffSignal(int boardId, int pinId);

    ~Pca9685BoardManager() {
      for (int i = 0; i < NO_OF_TOTAL_BOARDS; i++) {
        delete &_pwmBoards[i];
      }
      delete[] _pwmBoards;
    }
};
#endif
