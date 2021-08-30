
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#include "Config.h"
#include "IrBlockSensors.h"

bool flag = true;
int address = 1;

int blockNo = 0;
int sensStatus[NO_OF_BLOCKS];
IrBlockSensors blockSensors;

void setup() {
  Serial.begin(BROAD_RATE);
  Serial.flush();
  blockSensors.initBlockSensors(NO_OF_BLOCKS);
  for (int i = 0; i < NO_OF_BLOCKS; i++) {
    blockSensors.setBlockSensorPins(i + 1, sensorPin[i][0], sensorPin[i][1]);
    sensStatus[i] = 0;
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
    bool isBlockOccuipied = blockSensors.isSensorBlockOccupied(blockNo);
    if (isBlockOccuipied) {
      if (sensStatus[blockNo - 1] != 1) {
        sensStatus[blockNo - 1] = 1;
        sendData(String(JMRI_SENSOR_START_ADDRESS + blockNo) + ACTIVE);
      }
    } else {
      if (sensStatus[blockNo - 1] != 0) {
        sensStatus[blockNo - 1] = 0;
        sendData(String(JMRI_SENSOR_START_ADDRESS + blockNo) + INACTIVE);
      }
    }
  }
  delay(DELAY_TIME);
}

void sendData(String data) {
  Serial.write(data.c_str());
  data = "";
}
