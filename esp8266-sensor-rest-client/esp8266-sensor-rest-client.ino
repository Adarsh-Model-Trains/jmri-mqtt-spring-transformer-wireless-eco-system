#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include"Config.h"

ESP8266WiFiMulti WiFiMulti;


String id ;
String val;
String message;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWROD);
  while ((WiFiMulti.run() == WL_CONNECTED)) {
    delay(500);
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
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
