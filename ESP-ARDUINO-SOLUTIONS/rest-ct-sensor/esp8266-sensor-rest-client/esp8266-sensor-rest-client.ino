#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include"Config.h"

String id ;
String val;
String message;
int httpResponseCode ;

HTTPClient http;
WiFiClient client;
ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(BROAD_RATE);
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
    while (Serial.available()) {
      message = Serial.readString(); // 10000:AC or 10000:IN
      if (message != "") {
        id = message.substring(0, 5); // 10000
        val = message.substring(6, 8); // AC | IN
        if (val == ACT) {
          httpPostRequest(PAYLOAD_FROUNT + id + PAYLOAD_BACK_ACTIVE);
        } else {
          httpPostRequest(PAYLOAD_FROUNT + id + PAYLOAD_BACK_INACTIVE);
        }
        message = "";
      }
    }
    delay(DELAY_TIME);
  } else {
    Serial.println("ERROR NOT CONNECTED TO WIFI");
  }
}

int httpPostRequest(String payload) {

  http.addHeader(CONTENT_TYPE, CONTENT_TYPE_VAL);
  httpResponseCode = http.POST(payload);
  if (httpResponseCode > 0) {
    Serial.println("Payload " + payload + " Response code: " + String(httpResponseCode) + " Response " + http.getString());
  } else if (httpResponseCode == -1) {
    Serial.println("ERROR SERVER NOT REACHABLE: " + String(httpResponseCode));
  }  else {
    Serial.println("ERROR Payload " + payload + " Error code: " + String(httpResponseCode) + " Response " + http.getString());
  }
  return httpResponseCode;
}
