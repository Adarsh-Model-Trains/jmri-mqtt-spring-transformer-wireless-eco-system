/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/
#ifndef CtSensor_h
#define CtSensor_h

class CtSensor {

  private:
    int _sensorsCount;
    int * _sensorsPins;

  public:
    CtSensor() {
    }

    void initCtSensor(int sensorsCount);

    void setSensorPin(int sensorNo, int pinNo);

    bool isSensorActive(int sensorNo);

    void displayPins();

    ~CtSensor() {
      delete[] _sensorsPins;
    }

};

#endif;
