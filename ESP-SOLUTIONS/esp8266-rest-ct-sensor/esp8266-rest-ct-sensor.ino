#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include"Config.h"
#include "CtSensor.h"

int blockNo = 0;
int httpResponseCode;
bool isBlockOccuipied;
int sensStatus[NO_OF_BLOCKS];
int sendThreashold[NO_OF_BLOCKS];

CtSensor ctSensor;
HTTPClient http;
WiFiClient client;
ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWROD);
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    delay(WIFI_RECONNECT_DELAY_TIME);
    Serial.print(".");
  }
  // Debugging - Output the IP Address of the ESP8266
  Serial.println();
  Serial.print(" CONNECTED TO WIFI ");
  Serial.print(WiFi.SSID());
  Serial.print(" ");
  Serial.println(WiFi.localIP());

  ctSensor.initCtSensor(NO_OF_BLOCKS);
  for (blockNo = 0; blockNo < NO_OF_BLOCKS; blockNo++) {
    ctSensor.setSensorPin(blockNo + 1, sensorPin[blockNo]);
    sensStatus[blockNo] = 0;
    sendThreashold[blockNo] = 0;
  }
}


void loop() {

  if ((WiFiMulti.run() == WL_CONNECTED)) {

    for (blockNo = 1 ; blockNo <= NO_OF_BLOCKS; blockNo++) {
      isBlockOccuipied = ctSensor.isSensorActive(blockNo);
      if (isBlockOccuipied) {
        if (sensStatus[blockNo - 1] != 1) {
          if (sendThreashold[blockNo - 1] < SEND_THRESHOLD) {
            sendThreashold[blockNo - 1] = sendThreashold[blockNo - 1] + 1;
            httpPostRequest(PAYLOAD_FROUNT + String(JMRI_SENSOR_START_ADDRESS + blockNo) + PAYLOAD_BACK_ACTIVE);
          } else {
            sensStatus[blockNo - 1] = 1;
            sendThreashold[blockNo - 1] = 0;
          }
        }
      } else {
        if (sensStatus[blockNo - 1] != 0) {
          if (sendThreashold[blockNo - 1] < SEND_THRESHOLD) {
            sendThreashold[blockNo - 1] = sendThreashold[blockNo - 1] + 1;
            httpPostRequest(PAYLOAD_FROUNT + String(JMRI_SENSOR_START_ADDRESS + blockNo)  + PAYLOAD_BACK_INACTIVE);
          } else {
            sendThreashold[blockNo - 1] = 0;
            sensStatus[blockNo - 1] = 0;
          }
        }
      }
    }
    delay(DELAY_TIME);
  } else {
    Serial.println(WIFI_MSG_F);
  }
}

int httpPostRequest(String payload) {
  http.begin(client, SERVER_URL);
  http.addHeader(CONTENT_TYPE, CONTENT_TYPE_VAL);
  // Send HTTP POST request
  httpResponseCode = http.POST(payload);
  if (httpResponseCode > 0) {
    Serial.println(" RESPONSE Payload " + payload + " Response code: " + String(httpResponseCode) + " Response " + http.getString());
  } else if (httpResponseCode == -1) {
    Serial.println(" ERROR SERVER NOT REACHABLE: " + String(httpResponseCode));
  } else {
    Serial.println(" ERROR Payload " + payload + " Error code: " + String(httpResponseCode) + " Response " + http.getString());
  }
  http.end();
  return httpResponseCode;
}
