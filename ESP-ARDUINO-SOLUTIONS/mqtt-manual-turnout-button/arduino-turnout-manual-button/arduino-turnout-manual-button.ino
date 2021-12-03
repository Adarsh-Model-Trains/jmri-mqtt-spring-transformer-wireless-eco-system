
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#include"Config.h"

int index = 0;

void setup() {
  Serial.begin(BROAD_RATE);
  Serial.flush();

  for (index = 0 ; index < NO_OF_TURNOUT; index++) {
    pinMode(swtichs[index][0], INPUT);
    pinMode(swtichs[index][1], INPUT);
  }
}

void loop() {
  for (index = 0 ; index < NO_OF_TURNOUT; index++) {
    if (digitalRead(swtichs[index][0]) == HIGH) {
      sendData(String(swtichs[index][1] + THROWN));
    } else if (digitalRead(swtichs[index][1]) == HIGH) {
      sendData(String(swtichs[index][1] + CLOSED));
    }
  }
  delay(DELAY_TIME);
}

void sendData(String data) {
  Serial.write(data.c_str());
}
