
#include"Config.h"
#include "IrSensor.h"

int blockNo;
IrSensor irSensor;
bool isBlockOccuipied;

void setup() {

  Serial.begin(BROAD_RATE);
  irSensor.init();
  Serial.println("UNOCCUPIED " + String(UNOCCUPIED));
  Serial.println("OCCUPYING_FROM_START_OF_BLOCK " + String(OCCUPYING_FROM_START_OF_BLOCK));
  Serial.println("OCCUPYING_FROM_END_OF_BLOCK " + String(OCCUPYING_FROM_END_OF_BLOCK));
  Serial.println("UNOCCUPIED " + String(OCCUPIED));
}

void loop() {

  for (blockNo = 1 ; blockNo <= NO_OF_BLOCKS; blockNo++) {
    isBlockOccuipied = irSensor.isBlockOccupied(blockNo);

    if (isBlockOccuipied) {
       Serial.println("Block is occupied " + String(blockNo));
    } else {
       Serial.println("Block is unoccupied " + String(blockNo));
    }
  }
  delay(DELAY_TIME);
}
