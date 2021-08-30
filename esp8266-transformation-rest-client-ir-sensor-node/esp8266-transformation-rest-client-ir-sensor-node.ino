#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include"Config.h"
#include "IrBlockSensors.h"

ESP8266WiFiMulti WiFiMulti;

int blockNo = 0;
int sensStatus[NO_OF_BLOCKS];
IrBlockSensors blockSensors;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWROD);
  while ((WiFiMulti.run() == WL_CONNECTED)) {
    delay(500);
  }
  Serial.println("");
  Serial.println("Connected to WiFi");

  blockSensors.initBlockSensors(NO_OF_BLOCKS);
  for (int i = 0; i < NO_OF_BLOCKS; i++) {
    blockSensors.setBlockSensorPins(i + 1, sensorPin[i][0], sensorPin[i][1]);
    sensStatus[i] = 0;
  }
}


void loop() {

  if ((WiFiMulti.run() == WL_CONNECTED)) {

    for (blockNo = 1 ; blockNo <= NO_OF_BLOCKS; blockNo++) {
      bool isBlockOccuipied = blockSensors.isSensorBlockOccupied(blockNo);
      if (isBlockOccuipied) {
        if (sensStatus[blockNo - 1] != 1) {
          sensStatus[blockNo - 1] = 1;
          httpPostRequest(PAYLOAD_FROUNT + String(JMRI_SENSOR_START_ADDRESS + blockNo) + PAYLOAD_BACK_ACTIVE);
        }
      } else {
        if (sensStatus[blockNo - 1] != 0) {
          sensStatus[blockNo - 1] = 0;
          httpPostRequest(PAYLOAD_FROUNT + String(JMRI_SENSOR_START_ADDRESS + blockNo)  + PAYLOAD_BACK_INACTIVE);
        }
      }
    }
    delay(DELAY_TIME);
  } else {
    Serial.println("WiFi Disconnected");
  }
}

int httpPostRequest(String payload) {
  WiFiClient client;
  HTTPClient http;
  // Your IP address with path or Domain name with URL path
  http.begin(client, SERVER_URL);
  http.addHeader(CONTENT_TYPE, CONTENT_TYPE_VAL);
  // Send HTTP POST request
  int httpResponseCode = http.POST(payload);
  if (httpResponseCode > 0) {
    Serial.println("Payload " + payload + " Response code: " + String(httpResponseCode) + " Response " + http.getString());
  } else {
    Serial.println("Payload " + payload + " Error code: " + String(httpResponseCode) + " Response " + http.getString());
  }
  http.end();
  return httpResponseCode;
}
