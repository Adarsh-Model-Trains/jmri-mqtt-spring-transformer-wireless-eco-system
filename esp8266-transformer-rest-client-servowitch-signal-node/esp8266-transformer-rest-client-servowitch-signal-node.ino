#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include"Config.h"
#include "Pca9685BoardManager.h"

String comp;
String jId ;
String bId ;
String pId ;
String val;
int jmriId ;
int boardId ;
int pinId ;
String serverResponse;

Pca9685BoardManager pcaBoardManager;
ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(BROAD_RATE);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWROD);
  while ((WiFiMulti.run() == WL_CONNECTED)) {
    delay(DELAY_TIME + DELAY_TIME);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");

  pcaBoardManager.initPca9685Boards();
}

void loop() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    serverResponse = httpGETRequest(SERVER_URL);
    // todo with the server response
    if (serverResponse != "") {
      processCall(serverResponse);
      delay(DELAY_TIME);
    }

  } else {
    Serial.println("WiFi Disconnected");
  }
}

String httpGETRequest(const char* serverName) {

  WiFiClient client;
  HTTPClient http;

  // Your IP address with path or Domain name with URL path
  http.begin(client, serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();
  String payload = "";

  if (httpResponseCode > 0) {
    //Serial.println("HTTP Response code: " + String(httpResponseCode));
    payload = http.getString();
  }
  else {
    Serial.println("Error code: " + String(httpResponseCode));
  }
  // Free resources
  http.end();
  return payload;
}

void processCall(String msg) {

  Serial.println("Message " + msg);
  char type = msg.charAt(0);
  msg = msg.substring(2);

  if (type == S) {

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

    doExecute(msg, T);

  } else if (type == L) {

    doExecute(msg, L);

  }
}

void doExecute(String msg , char type) {
  comp = msg.substring(0, MSG_SIZE);
  jId = comp.substring(0, 5);
  bId = comp.substring(6, 8);
  pId = comp.substring(9, 11);
  val = comp.substring(12, MSG_SIZE);

  boardId = atoi(bId.c_str());
  pinId = atoi(pId.c_str());

  doPrint(comp, jId, bId, pId, val);
  if (boardId <= NO_OF_TOTAL_BOARDS) {
    if (type == T ) {
      if (val == THROWN) {
        pcaBoardManager.switchThrow(boardId, pinId);
      } else {
        pcaBoardManager.switchClose( boardId, pinId);
      }
    } else if ( type == L || type == S) {
      if (val == ON) {
        pcaBoardManager.switchOn(boardId, pinId);
      } else {
        pcaBoardManager.switchOff( boardId, pinId);
      }
    }
  } else {
    Serial.println("BOARD NUMBER EXCEEDED THE NO OF BOARD CONFIGURED ");
  }
}

void doPrint(String input, String jmriId, String boardId, String pinId, String state) {
  Serial.println("Input " + input + " Number " + jmriId + " Board Number " + boardId + " Pin Number " + pinId + " Value " + state);
}
