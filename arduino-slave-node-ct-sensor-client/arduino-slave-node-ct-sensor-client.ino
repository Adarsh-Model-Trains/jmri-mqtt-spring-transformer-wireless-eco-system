
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#include "Config.h"
#include "CtSensor.h"

bool flag = true;
int address = 1;

int blockNo = 0;
CtSensor ctSensor;

void setup() {
  Serial.begin(BROAD_RATE);
  Serial.flush();
  ctSensor.initCtSensor(NO_OF_BLOCKS);
  for (int i = 0; i < NO_OF_BLOCKS; i++) {
    ctSensor.setSensorPin(i + 1, sensorPin[i]);
  }
}

void loop() {
  if (flag) {
    sendData(String(JMRI_SENSOR_START_ADDRESS + address) + ACTIVE);
    flag = false;
  } else {
    sendData(String(JMRI_SENSOR_START_ADDRESS + address) + INACTIVE);
    flag = true;
  }

  for (blockNo = 1 ; blockNo <= NO_OF_BLOCKS; blockNo++) {
    bool isBlockOccuipied = ctSensor.isSensorActive(blockNo);
    if (isBlockOccuipied) {
      sendData(String(JMRI_SENSOR_START_ADDRESS + blockNo) + ACTIVE);
    } else {
      sendData(String(JMRI_SENSOR_START_ADDRESS + blockNo) + INACTIVE);
    }
  }
  delay(DELAY_TIME);
}

void sendData(String data) {
  Serial.write(data.c_str());
  data = "";
}
