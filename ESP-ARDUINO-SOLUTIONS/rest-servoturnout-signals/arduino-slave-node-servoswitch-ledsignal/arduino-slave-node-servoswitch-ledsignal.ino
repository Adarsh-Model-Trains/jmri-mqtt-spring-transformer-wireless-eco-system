/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#include "Config.h"
#include "Pca9685BoardManager.h"

String inputVal;
String jId;
String bId;
String pId;
String val;
int jmriId;
int boardId;
int pinId;
char type;
String message;

Pca9685BoardManager pcaBoardManager;

void setup() {
  Serial.begin(BROAD_RATE);
  Serial.flush();
  pcaBoardManager.initPca9685Boards();
}

void loop() {
  // Monitor serial communication
  while (Serial.available()) {
    message = Serial.readString();
    if (message != "") {
      processCall(message);
      message = "";
    }
  }

  delay(DELAY_TIME);
}


void processCall(String msg) {

  Serial.println("Message " + msg);
  type = msg.charAt(0);

  if (type == S) {
    msg = msg.substring(2);
    doExecute(msg, S);
    msg = msg.substring(15);

    if (msg.length() >= MSG_SIZE) {

      doExecute(msg, S);
      msg = msg.substring(15);

      if (msg.length() >= MSG_SIZE) {

        doExecute(msg, S);

      }
    }
  } else if (type == T) {
    msg = msg.substring(2);
    doExecute(msg, T);

  } else if (type == L) {
    msg = msg.substring(2);
    doExecute(msg, L);

  }  else if (type == E) {

    Serial.println(NO_DATA_AVALIABLE);

  }  else if (type == O) {

    Serial.println(REST_API_DISABLED);
  }
  type = '-';
}

void doExecute(String msg , char type) {
  inputVal = msg.substring(0, MSG_SIZE);
  jId = inputVal.substring(0, 5);
  bId = inputVal.substring(6, 8);
  pId = inputVal.substring(9, 11);
  val = inputVal.substring(12, MSG_SIZE);

  boardId = atoi(bId.c_str());
  pinId = atoi(pId.c_str());

  doPrint(inputVal, jId, bId, pId, val);
  if (boardId <= NO_OF_TOTAL_BOARDS) {
    if (type == T ) {
      if (val == THROWN) {
        pcaBoardManager.switchThrow(boardId, pinId);
      } else {
        pcaBoardManager.switchClose( boardId, pinId);
      }
    }  else if ( type == S) {
      if (val == ON) {
        pcaBoardManager.switchOnSignal(boardId, pinId);
      } else {
        pcaBoardManager.switchOffSignal( boardId, pinId);
      }
    } else if ( type == L ) {
      if (val == ON) {
        pcaBoardManager.switchOnLight(boardId, pinId);
      } else {
        pcaBoardManager.switchOffLight( boardId, pinId);
      }
    }
  } else {
    Serial.println(BOARDS_CONFIG);
  }
}

void doPrint(String input, String jmriId, String boardId, String pinId, String state) {
  Serial.println("Input " + input + " Number " + jmriId + " Board Number " + boardId + " Pin Number " + pinId + " Value " + state);
}
