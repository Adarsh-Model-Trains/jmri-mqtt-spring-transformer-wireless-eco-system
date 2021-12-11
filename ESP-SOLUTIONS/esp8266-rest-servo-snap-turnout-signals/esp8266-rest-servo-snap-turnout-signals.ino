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
char type = '-';
String serverResponse;
int httpResponseCode = -1;
String payload = "";
const uint32_t connectTimeoutMs = 5000;

HTTPClient http;
WiFiClient client;
ESP8266WiFiMulti wifiMulti;
Pca9685BoardManager pcaBoardManager;

void setup() {
  Serial.begin(BROAD_RATE);
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWROD);
  while (wifiMulti.run(connectTimeoutMs) != WL_CONNECTED) {
    delay(WIFI_RECONNECT_DELAY_TIME);
    Serial.print(".");
  }
  // Debugging - Output the IP Address of the ESP8266
  Serial.println();
  Serial.print("CONNECTED TO WIFI ");
  Serial.print(WiFi.SSID());
  Serial.print(" ");
  Serial.println(WiFi.localIP());
  pcaBoardManager.initPca9685Boards();

  // Your IP address with path or Domain name with URL path
  http.begin(client, SERVER_URL);
}

void loop() {
  if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED) {
    serverResponse = httpGETRequest();
    // todo with the server response
    if (serverResponse != "") {
      processCall(serverResponse);
      delay(DELAY_TIME);
    }
  } else {
    Serial.println(" NOT CONNECTED TO WIFI ");
  }
}

String httpGETRequest() {
  httpResponseCode = http.GET();
  payload = "";

  if (httpResponseCode > 0) {
    Serial.println("HTTP RESPONSE CODE: " + String(httpResponseCode));
    payload = http.getString();
  } else if (httpResponseCode == -1) {
    Serial.println("ERROR SERVER NOT REACHABLE: " + String(httpResponseCode));
  } else {
    Serial.println("ERROR CODE: " + String(httpResponseCode));
  }
  return payload;
}

void processCall(String msg) {

  Serial.println("Message " + msg);
  type = msg.charAt(0);
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

 }  else if (type == E) {

    Serial.println(NO_DATA_AVALIABLE);

  }  else if (type == O) {

    Serial.println(REST_API_DISABLED);
  }
  type = '-';
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
    Serial.println(BOARDS_CONFIG);
  }
}

void doPrint(String input, String jmriId, String boardId, String pinId, String state) {
  Serial.println("Input " + input + " Number " + jmriId + " Board Number " + boardId + " Pin Number " + pinId + " Value " + state);
}
