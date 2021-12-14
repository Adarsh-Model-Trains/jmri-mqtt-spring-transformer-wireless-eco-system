
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#include "Config.h"
#include "IrSensor.h"


int blockNo = 0;
bool isBlockOccuipied;
int sensStatus[NO_OF_BLOCKS];
int sendThreashold[NO_OF_BLOCKS];
IrSensor irSensor;

void setup() {
  Serial.begin(BROAD_RATE);
  Serial.flush();
  for (blockNo = 0; blockNo < NO_OF_BLOCKS; blockNo++) {
    sensStatus[blockNo] = 0;
    sendThreashold[blockNo] = 0;
  }
}

void loop() {

  for (blockNo = 1 ; blockNo <= NO_OF_BLOCKS; blockNo++) {

    isBlockOccuipied = irSensor.isBlockOccupied(blockNo);
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
        if (sendThreashold[blockNo - 1] < SEND_THRESHOLD) {
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
