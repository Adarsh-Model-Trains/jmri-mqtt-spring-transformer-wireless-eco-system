
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
    pinMode(swtichs[indexCount][0], INPUT);
    pinMode(swtichs[indexCount][1], INPUT);
  }
}

void loop() {
  for (indexCount = 0 ; indexCount < NO_OF_TURNOUT; indexCount++) {
    if (digitalRead(swtichs[indexCount][0]) == HIGH) {
      if (swtichs[indexCount][3] == 0) {
        sendData(String(swtichs[indexCount][2] + THROWN));
        if (sendThreashold[indexCount] < SEND_THRESHOLD) {
          sendThreashold[indexCount] = sendThreashold[indexCount] + 1;
        } else {
          sendThreashold[indexCount] = 0;
          swtichs[indexCount][3] = 1;
          swtichs[indexCount][4] = 0;
        }
      }
    } else if (digitalRead(swtichs[indexCount][1]) == HIGH) {
      if (swtichs[indexCount][4] == 0) {
        sendData(String(swtichs[indexCount][2] + CLOSED));
        if (sendThreashold[indexCount] < SEND_THRESHOLD) {
          sendThreashold[indexCount] = sendThreashold[indexCount] + 1;
        } else {
          sendThreashold[indexCount] = 0;
          swtichs[indexCount][4] = 1;
          swtichs[indexCount][3] = 0;
        }
      }
    } else if (digitalRead(swtichs[indexCount][0]) == LOW && digitalRead(swtichs[indexCount][1]) == LOW) {
      swtichs[indexCount][3] = 0;
      swtichs[indexCount][4] = 0;
    }
  }
  delay(DELAY_TIME);
}

void sendData(String data) {
  Serial.write(data.c_str());
}
