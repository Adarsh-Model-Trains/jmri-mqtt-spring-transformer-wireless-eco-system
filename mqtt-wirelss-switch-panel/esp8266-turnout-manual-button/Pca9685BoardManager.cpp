
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

    Serial.print(" TOTAL PCA9685 BOARDS FOR SIGNALS ");
    Serial.println(NO_OF_TOTAL_BOARDS);

    if (index <= 0) {
      int i = 0;
      _pwmBoards = new Adafruit_PWMServoDriver[NO_OF_TOTAL_BOARDS];
      while (index < NO_OF_TOTAL_BOARDS) {
        _pwmBoards[index] = Adafruit_PWMServoDriver(_boardAddress[index]);
        _pwmBoards[index].begin();
        _pwmBoards[index].setPWMFreq(PWM_LIGHT_FREQUENCY);
        for (i = 0 ; i < TOTAL_BOARD_PIN; i++) {
          _pwmBoards[index].setPWM(i, 0, 4096);
        }
        Serial.println(" BOARD INDEX " + String(index) + " BOARD ADDRESS " + String(_boardAddress[index], HEX) + " SIGNALS ");
        delay(50);
        index++;
      }
    }
  } else {
    Serial.println(" INVALID BOARD COUNT FOR TURNOUT LIGHTS ");
  }
}
bool Pca9685BoardManager::switchOnSignal(int boardId, int pinId) {

  if (signalLedTypeAnode) {
    _pwmBoards[boardId].setPWM(pinId, F4096, F0);
  } else {
    _pwmBoards[boardId].setPWM(pinId, F0, F4096);
  }
  Serial.print(LED_ON);
  Serial.println(" " + String(boardId) + " " + String(pinId));
  return true;
}

bool Pca9685BoardManager::switchOffSignal(int boardId, int pinId) {
  if (signalLedTypeAnode) {
    _pwmBoards[boardId].setPWM(pinId, F0, F4096);
  } else {
    _pwmBoards[boardId].setPWM(pinId, F4096, F0);
  }
  Serial.print(LED_OFF);
  Serial.println(" " + String(boardId) + " " + String(pinId));
  return true;
}
