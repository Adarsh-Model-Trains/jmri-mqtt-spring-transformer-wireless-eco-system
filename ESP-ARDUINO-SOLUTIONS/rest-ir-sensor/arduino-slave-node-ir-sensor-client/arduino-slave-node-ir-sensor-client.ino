
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#include "Config.h"
#include "IrBlockSensors.h"


int blockNo = 0;
bool isBlockOccuipied;
int sensStatus[NO_OF_BLOCKS];
int sendThreashold[NO_OF_BLOCKS];
IrBlockSensors blockSensors;

void setup() {
  Serial.begin(BROAD_RATE);
  Serial.flush();
  blockSensors.initBlockSensors(NO_OF_BLOCKS);
  for (blockNo = 0; blockNo < NO_OF_BLOCKS; blockNo++) {
    blockSensors.setBlockSensorPins(blockNo + 1, sensorPin[blockNo][0], sensorPin[blockNo][1]);
    sensStatus[blockNo] = 0;
    sendThreashold[blockNo] = 0;
  }
}

void loop() {

  for (blockNo = 1 ; blockNo <= NO_OF_BLOCKS; blockNo++) {
    isBlockOccuipied = blockSensors.isSensorBlockOccupied(blockNo);
    if (isBlockOccuipied) {
      if (sensStatus[blockNo - 1] != 1) {
        if (sendThreashold[blockNo - 1] < SEND_THRESHOLD) {
          sendThreashold[blockNo - 1] = sendThreashold[blockNo - 1] + 1;
          sendData(String(JMRI_SENSOR_START_ADDRESS + blockNo) + ACTIVE);
        } else {
          sensStatus[blockNo - 1] = 1;
          sendThreashold[blockNo - 1] = 0;
        }
      }
    } else {
      if (sensStatus[blockNo - 1] != 0) {
        if (sendThreashold[blockNo - 1] < SEND_THRESHOLD ) {
          sendThreashold[blockNo - 1] = sendThreashold[blockNo - 1] + 1;
          sendData(String(JMRI_SENSOR_START_ADDRESS + blockNo) + INACTIVE);
        } else {
          sendThreashold[blockNo - 1] = 0;
          sensStatus[blockNo - 1] = 0;
        }
      }
    }
  }
  delay(DELAY_TIME);
}

void sendData(String data) {
  Serial.write(data.c_str());
  data = "";
}
