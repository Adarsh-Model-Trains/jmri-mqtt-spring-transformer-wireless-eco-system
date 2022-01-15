#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include"Config.h"

int requestCounter = -1;
String payload = "";
String serverResponse;
int httpResponseCode;

HTTPClient http;
WiFiClient client;
ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(BROAD_RATE);
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWROD);
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    delay(WIFI_RECONNECT_DELAY_TIME);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("CONNECTED TO WIFI ");
  Serial.print(WiFi.SSID());
  Serial.print(" ");
  Serial.println(WiFi.localIP());
  restGetHttpCall();
}

void loop() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    
    if (COUNTER_THRESHHOLD == requestCounter) {
      restGetHttpCall();
      requestCounter = 0;
    } else {
      requestCounter++;
    }
    
    serverResponse = httpGETRequest();
    if (serverResponse != "") {
      pushDataToSlave(serverResponse);
      delay(DELAY_TIME);
      serverResponse = "";
    }
  } else {
    Serial.println("ERROR NOT CONNECTED TO WIFI ");
  }
}

String httpGETRequest() {
  http.begin(client, SERVER_URL);
  http.addHeader(HEADER_NAME, HEADER_VALUE);
  http.addHeader(HEADER_COUNT_NAME, String(requestCounter));
  httpResponseCode = http.GET();
  payload = "";
  if (httpResponseCode > 0) {
    payload = http.getString();
  } else if (httpResponseCode == -1) {
    Serial.println("ERROR SERVER NOT REACHABLE: " + String(httpResponseCode));
  } else {
    //Serial.println("ERROR CODE: " + String(httpResponseCode));
  }
  http.end();
  return payload;
}

void restGetHttpCall() {
  http.begin(client, SERVER_URL + "/reset");
  http.addHeader(HEADER_NAME, HEADER_VALUE);
  httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    requestCounter = 0;
  } else if (httpResponseCode == -1) {
    Serial.println("ERROR SERVER NOT REACHABLE: " + String(httpResponseCode));
  }
  http.end();
}

void pushDataToSlave(String value) {
  value = value + "\n";
  Serial.write(value.c_str());
}
