
#include"Config.h"
#include "IrSensor.h"

int blockNo;
IrSensor irSensor;
bool isBlockOccuipied;

void setup() {
  Serial.begin(BROAD_RATE);
}

void loop() {

  for (blockNo = 1 ; blockNo <= NO_OF_BLOCKS; blockNo++) {
    isBlockOccuipied = irSensor.isBlockOccupied(blockNo);

    if (isBlockOccuipied) {
      Serial.println("Block is occupied " + String(blockNo));
    } else {
      Serial.println("Block is occupied " + String(blockNo));
    }
  }
  delay(DELAY_TIME);
}
