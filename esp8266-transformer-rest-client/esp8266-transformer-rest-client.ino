#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include"Config.h"

ESP8266WiFiMulti WiFiMulti;

String serverResponse;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWROD);
  while ((WiFiMulti.run() == WL_CONNECTED)) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");

}

void loop() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    serverResponse = httpGETRequest(SERVER_URL);
    // todo with the server response
    if (serverResponse != "") {
      pushDataToSlave(serverResponse);
      delay(200);
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

void pushDataToSlave(String value) {
  value = value + "\n";
  Serial.write(value.c_str());
}
