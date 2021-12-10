
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
      if (swtichs[index][3] == 0) {
        sendData(String(swtichs[index][2] + THROWN));
        swtichs[index][3] = 1;
        swtichs[index][4] = 0;
      }
    } else if (digitalRead(swtichs[index][1]) == HIGH) {
      if (swtichs[index][4] == 0) {
        sendData(String(swtichs[index][2] + CLOSED));
        swtichs[index][4] = 1;
        swtichs[index][3] = 0;
      }
    } else if (digitalRead(swtichs[index][0]) == LOW && digitalRead(swtichs[index][1]) == LOW) {
      swtichs[index][3] = 0;
      swtichs[index][4] = 0;
    }
  }
  delay(DELAY_TIME);
}

void sendData(String data) {
  Serial.write(data.c_str());
}
