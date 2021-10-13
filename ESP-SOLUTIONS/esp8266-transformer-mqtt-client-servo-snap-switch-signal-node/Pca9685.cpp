
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#include "Pca9685.h"
#include "Config.h"


void Pca9685::initPca9685(char type, char subType, int boardNumber) {
  //_pwm = Adafruit_PWMServoDriver(_boardsAddress);
  // _pwm.begin();
  this->_type = type;
  this->_subType = subType;
  this->_boardNumber = boardNumber;
  if (_type == L) {
    _pca9685PinStateList = new bool[TOTAL_BOARD_PIN];
    // _pwm.setPWMFreq(PWM_LIGHT_FREQUENCY);
    for (int i = 0; i < TOTAL_BOARD_PIN; i++) {
      _pca9685PinStateList[i] = false;
    }
    Serial.print("Type ");
    Serial.print(_type);
    Serial.print("SubType ");
    Serial.print(_subType);
    Serial.print(" Board Address ");
    Serial.print(_boardsAddress);
  } else if (_type == T && _subType == M) {
    // _pwm.setPWMFreq(PWM_SERVO_TURNOUT_FREQUENCY);
    _pca9685PinList = new Pca9685Pin[TOTAL_BOARD_PIN];
    for (int i = 0; i < TOTAL_BOARD_PIN; i++) {
      _pca9685PinList[i]._openState = turnoutRange[_boardNumber][i][0];
      _pca9685PinList[i]._closeState = turnoutRange[_boardNumber][i][1];
      _pca9685PinList[i]._isOpen = false;
    }
    Serial.print("Type ");
    Serial.print(_type);
    Serial.print("SubType ");
    Serial.print(_subType);
    Serial.print(" Board Address ");
    Serial.print(_boardsAddress);
  } else if (_type == T && _subType == N) {
    // _pwm.setPWMFreq(PWM_SNAP_TURNOUT_FREQUENCY);
    _pca9685PinStateList = new bool[TOTAL_BOARD_PIN];
    for (int i = 0; i < TOTAL_BOARD_PIN; i++) {
      _pca9685PinStateList[i] = false;
    }
    Serial.print("Type ");
    Serial.print(_type);
    Serial.print("SubType ");
    Serial.print(_subType);
    Serial.print(" Board Address ");
    Serial.print(_boardsAddress);
  }
}

bool Pca9685::setSwitchOpenCloseRange(int pinNo, int openRange, int closeRange) {
  if (_type == T) {
    _pca9685PinList[pinNo]._openState = openRange;
    _pca9685PinList[pinNo]._closeState = closeRange;
    return true;
  } else {
    return false;
  }
}

void Pca9685::setPwmFrequency(int pwmFrequency) {
  this->_pwmFrequency = pwmFrequency;
  // _pwm.setPWMFreq(_pwmFrequency);
}

void Pca9685::setBoardAddress(int boardsAddress) {
  this->_boardsAddress = boardsAddress;
}

void Pca9685::turnoutThrow(int pinNo) {
  if (this->_type == T && this->_subType == M) {
    _pca9685PinList[pinNo]._isOpen = true;
    //_pwm.writeMicroseconds(i, _pca9685PinList[pinNo]._openState );
    Serial.println(" TURNOUT THROW\n");
  } else if (this->_type == T && this->_subType == N) {
    _pca9685PinStateList[pinNo] = true;
    _pca9685PinStateList[pinNo + 1] = false;
    //  _pwm.setPWM(pinNo, 4096, 0);
    delay(200);
    //  _pwm.setPWM(pinNo, 0, 4096);
    Serial.println(" TURNOUT THROW\n");
  }
}

void Pca9685::turnoutClose(int pinNo) {
  if (this->_type ==  T && this->_subType == M) {
    _pca9685PinList[pinNo]._isOpen = false;
    //_pwm.writeMicroseconds(i, _pca9685PinList[pinNo]._closeState );
    Serial.println(" TURNOUT CLOSE\n");
  } else if (this->_type ==  T && this->_subType == N) {
    _pca9685PinStateList[pinNo] = true;
    _pca9685PinStateList[pinNo - 1] = false;
    // _pwm.setPWM(pinNo, 4096, 0);
    delay(200);
    // _pwm.setPWM(pinNo, 0, 4096);
    Serial.println(" TURNOUT CLOSE\n");
  }
}

void Pca9685::ledOn(int pinNo) {
  if (this->_type == L) {
    _pca9685PinStateList[pinNo] = true;
    // _pwm.setPWM(pinNo, 4096, 0);
    Serial.println(" LED ON\n");
  }
}
void Pca9685::ledOff(int pinNo) {
  if (this->_type == L) {
    _pca9685PinStateList[pinNo] = false;
    // _pwm.setPWM(pinNo, 0, 4096);
    Serial.println(" LED OFF\n");
  }
}

char Pca9685::getType() {
  return this->_type;
}
