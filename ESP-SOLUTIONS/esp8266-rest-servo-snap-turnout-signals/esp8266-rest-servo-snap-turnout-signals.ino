#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include"Config.h"
#include "Pca9685BoardManager.h"

String inputVal;
String jId ;
String bId ;
String pId ;
String val;
int jmriId ;
int boardId ;
int pinId ;
char type = '-';
String serverResponse;
int httpResponseCode = -1;
String payload = "";

HTTPClient http;
WiFiClient client;
ESP8266WiFiMulti wifiMulti;
Pca9685BoardManager pcaBoardManager;

void setup() {
  Serial.begin(BROAD_RATE);
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWROD);
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(WIFI_RECONNECT_DELAY_TIME);
    Serial.print(".");
  }
<<<<<<< HEAD
  // Debugging - Output the IP Address of the ESP8266
  Serial.println();
  Serial.print("WiFi connected: ");
=======

  Serial.println();
  Serial.print(" CONNECTED TO WIFI ");
>>>>>>> b0bdd94e83148b2d3bca7f78d25c39ff43ada173
  Serial.print(WiFi.SSID());
  Serial.print(" ");
  Serial.println(WiFi.localIP());
  pcaBoardManager.initPca9685Boards();
}

void loop() {
  if (wifiMulti.run() == WL_CONNECTED) {
    serverResponse = httpGETRequest();
    if (serverResponse != "") {
      processCall(serverResponse);
      delay(DELAY_TIME);
    }
  } else {
    Serial.println(" ERROR NOT CONNECTED TO WIFI ");
  }
}

String httpGETRequest() {
  http.begin(client, SERVER_URL);
  http.addHeader(HEADER_NAME, HEADER_VALUE);
  httpResponseCode = http.GET();
  payload = "";
  if (httpResponseCode > 0) {
    Serial.println("HTTP RESPONSE CODE: " + String(httpResponseCode));
    payload = http.getString();
  } else if (httpResponseCode == -1) {
    Serial.println(" ERROR SERVER NOT REACHABLE: " + String(httpResponseCode));
  } else {
    Serial.println(" ERROR CODE: " + String(httpResponseCode));
  }
  http.end();
  return payload;
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
    } else if ( type == S) {
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
