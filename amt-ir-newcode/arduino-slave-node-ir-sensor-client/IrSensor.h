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
    BLOCK_STATES * _blockStatesCurrent;
    BLOCK_STATES * _blockStatesPrevious;

    void init();
    void calculateBlockOccupancy(int blockNo);
    BLOCK_STATES unOccupiedBlock(BLOCK_STATES signalState, int startSensor, int endSensor);
    BLOCK_STATES occupiedFromEndOfBlock(BLOCK_STATES signalState, int startSensor, int endSensor);
    BLOCK_STATES occupiedFromStartOfBlock(BLOCK_STATES signalState, int startSensor, int endSensor);
    BLOCK_STATES occupiedBlock(BLOCK_STATES signalState, int startSensor, int endSensor) ;

  public:

    IrSensor() {
      void init();
    }

    bool isBlockOccupied(int blockNo);

    ~IrSensor() {
    }

};

#endif
