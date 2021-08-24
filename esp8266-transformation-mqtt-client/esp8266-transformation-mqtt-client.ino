/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

// Enables the ESP8266 to connect to the local network (via WiFi)
#include <ESP8266WiFi.h>
// Allows us to connect to, and publish to the MQTT broker
#include <PubSubClient.h>
#include"Config.h"

String mqttTopicValue;
String messageText;

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;

// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient);

void subscribeMqttMessage(char* topic, byte* payload, unsigned int length) {

  mqttTopicValue = getMessage(payload, length);

  Serial.write(mqttTopicValue.c_str());

  mqttTopicValue = "";
}

/*
   converting message from mqtt bytes to string
*/
String getMessage(byte* message, unsigned int length) {
  messageText = "";
  for (int i = 0; i < length; i++) {
    messageText += (char)message[i];
  }
  return messageText + "\n";
}

bool mqttConnect() {
  // Connect to MQTT Server and subscribe to the topic
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    client.subscribe(mqtt_topic);
    return true;
  } else {
    return false;
  }
}

void setup() {

  // Begin Serial on 115200
  Serial.begin(BROAD_RATE);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // setCallback sets the function to be called when a message is received.
  client.setCallback(subscribeMqttMessage);
  if (mqttConnect()) {
    Serial.println("Connected Successfully to MQTT Broker!");
  } else {
    Serial.println("Connection Failed!");
  }
}


void loop() {
  // If the connection is lost, try to connect again
  if (!client.connected()) {
    mqttConnect();
  }
  // client.loop() just tells the MQTT client code to do what it needs to do itself (i.e. check for messages, etc.)
  client.loop();
  // Once it has done all it needs to do for this cycle, go back to checking if we are still connected.
  delay(DELAY_TIME);
}
