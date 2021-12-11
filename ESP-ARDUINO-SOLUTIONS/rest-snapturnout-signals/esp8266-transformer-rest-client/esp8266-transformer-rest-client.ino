#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include"Config.h"


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
  // Your IP address with path or Domain name with URL path
  http.begin(client, SERVER_URL);
}

void loop() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
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

  httpResponseCode = http.GET();
  payload = "";
  if (httpResponseCode > 0) {
    payload = http.getString();
  } else if (httpResponseCode == -1) {
    Serial.println("ERROR SERVER NOT REACHABLE: " + String(httpResponseCode));
  } else {
    Serial.println("ERROR CODE: " + String(httpResponseCode));
  }
  return payload;
}

void pushDataToSlave(String value) {
  value = value + "\n";
  Serial.write(value.c_str());
}
