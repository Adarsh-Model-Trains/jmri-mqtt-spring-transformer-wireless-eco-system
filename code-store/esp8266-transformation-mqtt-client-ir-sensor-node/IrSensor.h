/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/
#ifndef IrSensor_h
#define IrSensor_h

enum BLOCK_STATES {
  UNOCCUPIED,
  OCCUPYING_FROM_START_OF_BLOCK,
  OCCUPYING_FROM_END_OF_BLOCK,
  OCCUPIED,
};

class IrSensor {

  private:

    int _startBlockSensorPin;
    int _endBlockSensorPin;
    int _startBlockSensorVal;
    int _endBlockSensorVal;

    BLOCK_STATES _stateCurrent = UNOCCUPIED;
    BLOCK_STATES _statePrevious = UNOCCUPIED;

    void init();
    void calculateBlockOccupancy();

    BLOCK_STATES unOccupiedBlock(BLOCK_STATES signalState, int startSensor, int endSensor);
    BLOCK_STATES occupiedFromEndOfBlock(BLOCK_STATES signalState, int startSensor, int endSensor);
    BLOCK_STATES occupiedFromStartOfBlock(BLOCK_STATES signalState, int startSensor, int endSensor);
    BLOCK_STATES occupiedBlock(BLOCK_STATES signalState, int startSensor, int endSensor) ;

  public:

    IrSensor() {
      void init();
    }

    IrSensor(int startBlockSensorPin, int endBlockSensorPin): _startBlockSensorPin(startBlockSensorPin), _endBlockSensorPin(endBlockSensorPin) {
      void init();
    }
    
    void setStartAndEndBlockSensorPin(int startBlockSensorPin, int endBlockSensorPin);
    
    bool isBlockOccupied();

    ~IrSensor() {
    }

};

#endif
