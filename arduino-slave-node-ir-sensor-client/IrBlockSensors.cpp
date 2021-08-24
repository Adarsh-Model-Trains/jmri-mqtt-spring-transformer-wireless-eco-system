/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#include <Arduino.h>
#include "IrBlockSensors.h"

void IrBlockSensors::initBlockSensors(int totalSensor) {
  if (totalSensor > 0) {
    if (totalSensor > 0)
      _totalSensor = totalSensor;
    this->_irSensorBlocks = new IrSensor[_totalSensor];
    for (int i = 0; i < _totalSensor; i++) {
      this->_irSensorBlocks[i].setStartAndEndBlockSensorPin(0, 0);
    }
  } else {
    Serial.println("Invalid Sensor Count");
  }
}

void IrBlockSensors::setBlockSensorPins(int blockNo, int startBlockSensorPin, int endBlockSensorPin) {
  if (blockNo > -1 && blockNo <= _totalSensor ) {
    if (startBlockSensorPin > -1 && endBlockSensorPin > -1) {
      pinMode(startBlockSensorPin, INPUT);
      pinMode(endBlockSensorPin, INPUT);
      _irSensorBlocks[blockNo - 1].setStartAndEndBlockSensorPin(startBlockSensorPin, endBlockSensorPin);
    } else {
      Serial.println("Invalid Block Sensor Pin No.");
    }
  } else {
    Serial.println("Invalid Block Sensor Input No.");
  }
}

bool IrBlockSensors::isSensorBlockOccupied(int blockNo) {
  if (blockNo > -1 && blockNo <= _totalSensor) {
    return _irSensorBlocks[blockNo - 1].isBlockOccupied();
  } else {
    Serial.println("Invalid Block Sensor No");
    return false;
  }
}
