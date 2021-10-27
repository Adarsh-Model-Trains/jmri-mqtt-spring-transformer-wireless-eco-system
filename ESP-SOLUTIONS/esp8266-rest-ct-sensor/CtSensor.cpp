/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/
#include <Arduino.h>
#include "CtSensor.h"


int i;
int val;
void CtSensor::initCtSensor(int sensorsCount) {
  if (sensorsCount > 0) {
    _sensorsCount = sensorsCount;
    _sensorsPins = new int[_sensorsCount];
    for ( i = 0; i < _sensorsCount; i++) {
      _sensorsPins[i] = -1;
    }
  } else {
    Serial.println("Invalid Sensor Count");
  }
}

void CtSensor::setSensorPin(int sensorNo, int pinNo) {
  if (sensorNo > -1 && sensorNo <= _sensorsCount) {
    if (pinNo > -1) {
      _sensorsPins[sensorNo - 1] = pinNo;
      if (ENABLE_PULLUP) {
        pinMode(pinNo, INPUT_PULLUP);
      } else {
        pinMode(pinNo, INPUT);
      }
    } else {
      Serial.println("Invalid Sensor Pin No");
    }
  } else {
    Serial.println("Invalid Sensor Number");
  }
}

bool CtSensor:: isSensorActive(int sensorNo) {
  if (sensorNo > -1 && sensorNo <= _sensorsCount) {
    val = digitalRead(_sensorsPins[sensorNo - 1]);
    if ( val == 0) {
      Serial.print(sensorNo - 1);
      Serial.print("  ");
      Serial.println(val);
      return true;
    } else {
      return false;
    }
  } else {
    Serial.println("Invalid Sensor Number");
    return false;
  }
}


void CtSensor::displayPins() {
  Serial.println();
  for ( i = 0; i < _sensorsCount; i++) {
    Serial.print( _sensorsPins[i]);
    Serial.print("  ");
  }
  Serial.println();
}
