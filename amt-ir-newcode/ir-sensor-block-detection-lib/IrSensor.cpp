/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#include <Arduino.h>
#include "IrSensor.h"
#include "Config.h"


void IrSensor::init() {
  if (NO_OF_BLOCKS > 0) {
    _blockStatesCurrent = new int[NO_OF_BLOCKS];
    _blockStatesPrevious = new int[NO_OF_BLOCKS];
    for ( i = 0; i < NO_OF_BLOCKS; i++) {
      if (sensorPin[i][1] > -1 && sensorPin[i][0] > -1) {
        pinMode(sensorPin[i][0], INPUT);  // block end pin
        pinMode(sensorPin[i][1], INPUT);  // block start pin
        _blockStatesCurrent[i] = UNOCCUPIED;
        _blockStatesPrevious[i] = UNOCCUPIED;
      } else {
        Serial.println(INVALID_SENSOR_PIN);
      }
    }
  } else {
    Serial.println("INVLAID SENEOR COUNT");
  }
}



void IrSensor::calculateBlockOccupancy(int blockNo) {

  _startBlockSensorVal = digitalRead(sensorPin[blockNo][0]);
  _endBlockSensorVal = digitalRead(sensorPin[blockNo][1]);

  //Serial.println("blockNo " + String(blockNo) + " _startBlockSensorVal " + String(_startBlockSensorVal) + " _startBlockSensorVal " + String(_startBlockSensorVal) + " _blockStatesCurrent " + String(_blockStatesCurrent[blockNo]) + " _blockStatesPrevious " + String(_blockStatesPrevious[blockNo]));

  switch (_blockStatesPrevious[blockNo]) {
    case UNOCCUPIED:
      _blockStatesCurrent[blockNo] =  unOccupiedBlock(_blockStatesPrevious[blockNo], _startBlockSensorVal, _endBlockSensorVal);
      if ( _blockStatesCurrent[blockNo] != _blockStatesPrevious[blockNo]) {
        _blockStatesPrevious[blockNo] =  _blockStatesCurrent[blockNo];
      }
      break;

    case OCCUPYING_FROM_START_OF_BLOCK:
      _blockStatesCurrent[blockNo] = occupiedFromEndOfBlock(_blockStatesPrevious[blockNo], _startBlockSensorVal, _endBlockSensorVal);
      if ( _blockStatesCurrent[blockNo] != _blockStatesPrevious[blockNo]) {
        _blockStatesPrevious[blockNo] =  _blockStatesCurrent[blockNo];
      }
      break;

    case OCCUPYING_FROM_END_OF_BLOCK:
      _blockStatesCurrent[blockNo] = occupiedFromStartOfBlock(_blockStatesPrevious[blockNo], _startBlockSensorVal, _endBlockSensorVal);
      if ( _blockStatesCurrent[blockNo] != _blockStatesPrevious[blockNo]) {
        _blockStatesPrevious[blockNo] =  _blockStatesCurrent[blockNo];
      }
      break;

    case OCCUPIED:
      _blockStatesCurrent[blockNo] = occupiedBlock(_blockStatesPrevious[blockNo], _startBlockSensorVal, _endBlockSensorVal);
      if ( _blockStatesCurrent[blockNo] != _blockStatesPrevious[blockNo]) {
        _blockStatesPrevious[blockNo] =  _blockStatesCurrent[blockNo];
      }
      break;
  }
}

bool IrSensor::isBlockOccupied(int blockNo) {

  if (blockNo > -1 && blockNo <= NO_OF_BLOCKS) {
    calculateBlockOccupancy(blockNo - 1);
    if (_blockStatesCurrent[blockNo - 1] == UNOCCUPIED) {
      return false;
    } else {
      return true;
    }
  } else {
    Serial.println(INVALID_SENSOR_NUMBER);
    return false;
  }
}


int IrSensor::unOccupiedBlock(int signalState, int startSensor, int endSensor) {

  if (startSensor == ON  && endSensor == OFF) {
    Serial.println("unOccupiedBlock startSensor " + String(startSensor) + " endSensor " + String(endSensor) + " OCCUPYING_FROM_START_OF_BLOCK");
    signalState = OCCUPYING_FROM_START_OF_BLOCK;
  } else if (startSensor == OFF  && endSensor == ON) {
    Serial.println("unOccupiedBlock startSensor " + String(startSensor) + " endSensor " + String(endSensor) + " OCCUPYING_FROM_END_OF_BLOCK");
    signalState = OCCUPYING_FROM_END_OF_BLOCK;
  }
  return signalState;
}


int IrSensor::occupiedFromEndOfBlock(int signalState, int startSensor, int endSensor) {

  if (startSensor == OFF && endSensor == ON) {
    Serial.println("occupiedFromEndOfBlock  startSensor " + String(startSensor) + " endSensor " + String(endSensor) + " OCCUPIED");
    signalState = OCCUPIED;
  }
  return signalState;
}


int IrSensor::occupiedFromStartOfBlock(int signalState, int startSensor, int endSensor) {
  if (startSensor == ON  && endSensor == OFF) {
    Serial.println("occupiedFromStartOfBlock  startSensor " + String(startSensor) + " endSensor " + String(endSensor) + " OCCUPIED");
    signalState = OCCUPIED;
  }
  return signalState;
}


int IrSensor::occupiedBlock(int signalState, int startSensor, int endSensor) {

  if ((startSensor == OFF) && (endSensor == OFF)) {
    Serial.println("occupiedBlock  startSensor " + String(startSensor) + " endSensor " + String(endSensor) + " UNOCCUPIED");
    signalState = UNOCCUPIED;
  }
  return signalState;
}
