/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/
#ifndef IrSensor_h
#define IrSensor_h

#include "Config.h"

class IrSensor {

  private:
    int i = 0;
    int _startBlockSensorVal;
    int _endBlockSensorVal;
    int * _blockStatesCurrent;
    int * _blockStatesPrevious;


    void calculateBlockOccupancy(int blockNo);
    int unOccupiedBlock(int signalState, int startSensor, int endSensor);
    int occupiedFromEndOfBlock(int signalState, int startSensor, int endSensor);
    int occupiedFromStartOfBlock(int signalState, int startSensor, int endSensor);
    int occupiedBlock(int signalState, int startSensor, int endSensor) ;

  public:
    void init();
    IrSensor() {
    }

    bool isBlockOccupied(int blockNo);

    ~IrSensor() {
    }

};

#endif
