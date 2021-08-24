
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/


#include <Arduino.h>
#include "Pca9685BoardManager.h"
#include "Config.h"

void Pca9685BoardManager::initPca9685Boards() {

  if ((NO_OF_TOTAL_BOARDS) > 0 && (NO_OF_TOTAL_BOARDS) < 65) {

    Serial.print("Total Pca9685 boards for Turnout and Light ");
    Serial.println(NO_OF_TOTAL_BOARDS);

    if (NO_OF_TURNOUT_BOARDS > -1 && NO_OF_TURNOUT_BOARDS < 65) {
      Serial.print("Total Pca9685 boards for Turnout ");
      Serial.println(NO_OF_TURNOUT_BOARDS);
    } else {
      Serial.println("invalid arguments supplied ");
      return;
    }

    if (NO_OF_LIGHT_BOARDS > -1 && NO_OF_LIGHT_BOARDS < 65) {
      Serial.print("Total Pca9685 boards for Light ");
      Serial.println(NO_OF_LIGHT_BOARDS);
    } else {
      Serial.println("invalid arguments supplied ");
      return;
    }

    if (index <= 0) {
      _pca9685Boards = new Pca9685[NO_OF_TOTAL_BOARDS];
      while (index < NO_OF_TOTAL_BOARDS) {
        if ( index < NO_OF_TURNOUT_BOARDS) {
          _pca9685Boards[index].setBoardAddress(_boardAddress[index]);
          _pca9685Boards[index].initPca9685(T, index);
          Serial.print(" value of Index ");
          Serial.println(index);
        } else  {
          _pca9685Boards[index].setBoardAddress(_boardAddress[index]);
          _pca9685Boards[index].initPca9685(L, index);
          Serial.print(" value of Index ");
          Serial.println(index);
        }
        delay(50);
        index++;
      }
    }
  } else {
    Serial.println("invalid arguments supplied ");
  }
}

bool Pca9685BoardManager::switchThrow(int boardId, int pinId) {
  if (_pca9685Boards[boardId].getType() == T) {
    _pca9685Boards[boardId].turnoutThrow(pinId);
    return true;
  } else {
    return false;
  }
}

bool Pca9685BoardManager::switchClose(int boardId, int pinId) {
  if (_pca9685Boards[boardId].getType() == T) {
    _pca9685Boards[boardId].turnoutClose(pinId);
    return true;
  } else {
    return false;
  }
}

bool Pca9685BoardManager::switchOn(int boardId, int pinId) {
  if (_pca9685Boards[boardId].getType() == L) {
    _pca9685Boards[boardId].ledOn(pinId);
    return true;
  } else {
    return false;
  }
}

bool Pca9685BoardManager::switchOff(int boardId, int pinId) {
  if (_pca9685Boards[boardId].getType() == L) {
    _pca9685Boards[boardId].ledOff(pinId);
    return true;
  } else {
    return false;
  }
}
