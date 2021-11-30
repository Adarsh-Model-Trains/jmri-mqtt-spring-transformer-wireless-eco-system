
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

    if (NO_OF_SERVO_TURNOUT_BOARDS > -1 && NO_OF_SERVO_TURNOUT_BOARDS < 65) {
      Serial.print("Total Pca9685 boards for Servo Turnout ");
      Serial.println(NO_OF_SERVO_TURNOUT_BOARDS);
    } else {
      Serial.println("invalid arguments supplied ");
      return;
    }

    if (NO_OF_SNAP_TURNOUT_BOARDS > -1 && NO_OF_SNAP_TURNOUT_BOARDS < 65) {
      Serial.print("Total Pca9685 boards for Snap Turnout ");
      Serial.println(NO_OF_SNAP_TURNOUT_BOARDS);
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
      // _pca9685Boards = new Pca9685[NO_OF_TOTAL_BOARDS];

      _pwmBoards = new Adafruit_PWMServoDriver[NO_OF_TOTAL_BOARDS];
      _pwmBoardTypes  = new char[NO_OF_TOTAL_BOARDS];


      while (index < NO_OF_TOTAL_BOARDS) {
        if ( index < NO_OF_SERVO_TURNOUT_BOARDS) {
          _pwmBoards[index] = Adafruit_PWMServoDriver(_boardAddress[index]);
          _pwmBoards[index].begin();
          _pwmBoards[index].setPWMFreq(PWM_LIGHT_FREQUENCY);
          _pwmBoardTypes[index] = M;

          Serial.print(" value of Index ");
          Serial.println(index);
        } else if (index >= NO_OF_SERVO_TURNOUT_BOARDS &&  index < NO_OF_SNAP_TURNOUT_BOARDS + NO_OF_SERVO_TURNOUT_BOARDS) {
          _pwmBoards[index] = Adafruit_PWMServoDriver(_boardAddress[index]);
          _pwmBoards[index].begin();
          _pwmBoards[index].setPWMFreq(PWM_SNAP_TURNOUT_FREQUENCY);
          _pwmBoardTypes[index] = S;

          Serial.print(" value of Index ");
          Serial.println(index);
        } else  {
          _pwmBoards[index] = Adafruit_PWMServoDriver(_boardAddress[index]);
          _pwmBoards[index].begin();
          _pwmBoards[index].setPWMFreq(PWM_LIGHT_FREQUENCY);
          _pwmBoardTypes[index] = L;

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

  if (_pwmBoardTypes[boardId] == M) {
    _pwmBoards[boardId].writeMicroseconds(pinId,  turnoutRange[boardId][pinId][0]);
    Serial.println(TURNOUT_THROWN);
    return true;
  } else if (_pwmBoardTypes[boardId] == S) {
    _pwmBoards[boardId].setPWM(pinId, F4096, F0);
    delay(DELAY_TIME);
    _pwmBoards[boardId].setPWM(pinId, F0, F4096);
    Serial.println(TURNOUT_THROWN);
  } else {
    return false;
  }
}

bool Pca9685BoardManager::switchClose(int boardId, int pinId) {
  if (_pwmBoardTypes[boardId] == M) {
    _pwmBoards[boardId].writeMicroseconds(pinId, turnoutRange[boardId][pinId][1]);
    Serial.println(TURNOUT_CLOSE);
    return true;
  } else if (_pwmBoardTypes[boardId] == S) {
    _pwmBoards[boardId].setPWM(pinId, F4096, F0);
    delay(DELAY_TIME);
    _pwmBoards[boardId].setPWM(pinId, F0, F4096);
    Serial.println(TURNOUT_CLOSE);
  } else {
    return false;
  }
}

bool Pca9685BoardManager::switchOn(int boardId, int pinId) {

  if (_pwmBoardTypes[boardId] == L) {
    if (signalLedTypeAnode) {
      _pwmBoards[boardId].setPWM(pinId, F4096, F0);
    } else {
      _pwmBoards[boardId].setPWM(pinId, F0, F4096);
    }
    Serial.println(LED_ON);
    return true;
  } else {
    return false;
  }
}

bool Pca9685BoardManager::switchOff(int boardId, int pinId) {

  if (_pwmBoardTypes[boardId] == L) {
    if (signalLedTypeAnode) {
      _pwmBoards[boardId].setPWM(pinId, F0, F4096);
    } else {
      _pwmBoards[boardId].setPWM(pinId, F4096, F0);
    }
    Serial.println(LED_OFF);
    return true;
  } else {
    return false;
  }
}
