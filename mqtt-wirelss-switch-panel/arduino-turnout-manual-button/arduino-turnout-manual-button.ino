
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#include"Config.h"

int indexCount = 0;

void setup() {
  Serial.begin(BROAD_RATE);
  Serial.flush();
  for (indexCount = 0 ; indexCount < NO_OF_TURNOUT; indexCount++) {
    pinMode(swtichs[indexCount][THROW_PIN], INPUT);
    pinMode(swtichs[indexCount][CLOSE_PIN], INPUT);
  }
}

void loop() {
  for (indexCount = 0 ; indexCount < NO_OF_TURNOUT; indexCount++) {
    if (digitalRead(swtichs[indexCount][THROW_PIN]) == HIGH) {
      if (swtichs[indexCount][THROW_STATE] == 0) {
        sendData(String(swtichs[indexCount][JMRIADDRESS] + THROWN));
        if (swtichs[indexCount][THROW_SEND_STATUS] < SEND_THRESHOLD) {
          swtichs[indexCount][THROW_SEND_STATUS] = swtichs[indexCount][THROW_SEND_STATUS] + 1;
        } else {
          swtichs[indexCount][THROW_SEND_STATUS] = 0;
          swtichs[indexCount][THROW_STATE] = 1;
          swtichs[indexCount][CLOSE_STATE] = 0;
        }
      }
    } else if (digitalRead(swtichs[indexCount][CLOSE_PIN]) == HIGH) {
      if (swtichs[indexCount][CLOSE_STATE] == 0) {
        sendData(String(swtichs[indexCount][JMRIADDRESS] + CLOSED));
        if (swtichs[indexCount][CLOSE_SEND_STATUS] < SEND_THRESHOLD) {
          swtichs[indexCount][CLOSE_SEND_STATUS] = swtichs[indexCount][CLOSE_SEND_STATUS] + 1;
        } else {
          swtichs[indexCount][CLOSE_SEND_STATUS] = 0;
          swtichs[indexCount][CLOSE_STATE] = 1;
          swtichs[indexCount][THROW_STATE] = 0;
        }
      }
    } else if (digitalRead(swtichs[indexCount][0]) == LOW && digitalRead(swtichs[indexCount][1]) == LOW) {
      swtichs[indexCount][THROW_STATE] = 0;
      swtichs[indexCount][CLOSE_STATE] = 0;
      swtichs[indexCount][THROW_SEND_STATUS] = 0;
      swtichs[indexCount][CLOSE_SEND_STATUS] = 0;
    }
  }
  delay(DELAY_TIME);
}

void sendData(String data) {
  Serial.write(data.c_str());
}
