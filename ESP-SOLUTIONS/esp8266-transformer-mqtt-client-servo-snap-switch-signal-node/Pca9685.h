
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Pca9685_h
#define Pca9685_h

#include <Arduino.h>
//#include "Adafruit_PWMServoDriver.h"

typedef struct {
  int _openState;
  int _closeState;
  bool _isOpen;
} Pca9685Pin;

class Pca9685 {

  private:
    char _type;
    char _subType;
    int _boardsAddress;
    int _pwmFrequency;
    int _boardNumber;
    Pca9685Pin * _pca9685PinList;
    bool * _pca9685PinStateList;
    //Adafruit_PWMServoDriver _pwm;

  public:
    Pca9685() {
    }
    void initPca9685(char type, char subType, int boardNumber);
    void setBoardAddress(int boardsAddress);
    void setPwmFrequency(int pwmFrequency);
    bool setSwitchOpenCloseRange(int pinNo, int openRange, int closeRange);
    void turnoutThrow(int pinNo);
    void turnoutClose(int pinNo);
    void ledOn(int pinNo);
    void ledOff(int pinNo);
    char getType();

    ~Pca9685() {
      delete [] _pca9685PinStateList;
    }
};

#endif
