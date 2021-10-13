
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Pca9685_h
#define Pca9685_h

#include <Arduino.h>
//#include "Adafruit_PWMServoDriver.h"


class Pca9685 {

  private:
    char _type;
    int _boardsAddress;
    int _pwmFrequency;
    bool * _pca9685PinStateList;
    //Adafruit_PWMServoDriver _pwm;

  public:
    Pca9685() {
    }
    void initPca9685(char type);
    void setBoardAddress(int boardsAddress);
    void setPwmFrequency(int pwmFrequency);
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
