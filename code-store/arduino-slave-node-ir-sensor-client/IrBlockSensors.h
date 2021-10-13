/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/
#ifndef IrBlockSensors_h
#define IrBlockSensors_h

#include "IrSensor.h"

class IrBlockSensors {

  private:
    int _totalSensor;
    IrSensor * _irSensorBlocks;

  public:
    IrBlockSensors() {
    }

    void initBlockSensors(int totalSensor);
    void setBlockSensorPins(int blockNo, int startBlockSensorPin, int endBlockSensorPin);
    bool isSensorBlockOccupied(int blockNo);

    ~IrBlockSensors() {
      for (int i = 0; i < _totalSensor; i++) {
        delete &_irSensorBlocks[i];
      }
      delete[] _irSensorBlocks;
    }
};

#endif
