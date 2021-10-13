/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#include <Arduino.h>
#include "IrSensor.h"
#include "Config.h"


void IrSensor::init() {
  _startBlockSensorVal = -1;
  _endBlockSensorVal = -1;
}

void IrSensor::setStartAndEndBlockSensorPin(int startBlockSensorPin, int endBlockSensorPin) {
  this->_startBlockSensorPin = startBlockSensorPin;
  this->_endBlockSensorPin = endBlockSensorPin;
}

void IrSensor::calculateBlockOccupancy() {

  int _startBlockSensorVal = digitalRead(_startBlockSensorPin);
  int _endBlockSensorVal = digitalRead(_endBlockSensorPin);

  switch (_statePrevious) {
    case UNOCCUPIED:
      _stateCurrent =  unOccupiedBlock(_statePrevious, _startBlockSensorVal, _endBlockSensorVal);
      if (_stateCurrent != _statePrevious) {
        _statePrevious = _stateCurrent;
      }
      break;

    case OCCUPYING_FROM_START_OF_BLOCK:
      _stateCurrent = occupiedFromEndOfBlock(_statePrevious, _startBlockSensorVal, _endBlockSensorVal);
      if (_stateCurrent != _statePrevious) {
        _statePrevious = _stateCurrent;
      }
      break;

    case OCCUPYING_FROM_END_OF_BLOCK:
      _stateCurrent = occupiedFromStartOfBlock(_statePrevious, _startBlockSensorVal, _endBlockSensorVal);
      if (_stateCurrent != _statePrevious) {
        _statePrevious = _stateCurrent;
      }
      break;

    case OCCUPIED:
      _stateCurrent = occupiedBlock(_statePrevious, _startBlockSensorVal, _endBlockSensorVal);
      if (_stateCurrent != _statePrevious) {
        _statePrevious = _stateCurrent;
      }
      break;
  }
}

bool IrSensor::isBlockOccupied() {
  calculateBlockOccupancy();
  if (_stateCurrent == UNOCCUPIED) {
    return false;
  } else {
    return true;
  }
}


BLOCK_STATES IrSensor::unOccupiedBlock(BLOCK_STATES signalState, int startSensor, int endSensor) {

  if (startSensor == ON  && endSensor == OFF) {
    signalState = OCCUPYING_FROM_START_OF_BLOCK;// block is occupied entered from sens1
  } else if (startSensor == OFF  && endSensor == ON) {
    signalState = OCCUPYING_FROM_END_OF_BLOCK;// block is occupied entered from sens2
  }
  return signalState;
}


BLOCK_STATES IrSensor::occupiedFromEndOfBlock(BLOCK_STATES signalState, int startSensor, int endSensor) {

  if (startSensor == OFF && endSensor == ON) {
    signalState = OCCUPIED;
  }
  return signalState;
}


BLOCK_STATES IrSensor::occupiedFromStartOfBlock(BLOCK_STATES signalState, int startSensor, int endSensor) {

  if (startSensor == ON  && endSensor == OFF) {
    signalState = OCCUPIED;
  }
  return signalState;
}


BLOCK_STATES IrSensor::occupiedBlock(BLOCK_STATES signalState, int startSensor, int endSensor) {

  if ((startSensor == OFF) && (endSensor == OFF)) {
    signalState = UNOCCUPIED;
  }
  return signalState;
}
