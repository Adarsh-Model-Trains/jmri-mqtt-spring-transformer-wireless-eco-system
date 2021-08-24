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

#include "Pca9685BoardManager.h"

String light;
String jId ;
String bId ;
String pId ;
String val;
int jmriId ;
int boardId ;
int pinId ;

String mqttTopicValue;
String messageText;

Pca9685BoardManager pcaBoardManager;

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;

// 1883 is the listener port for the Broker
PubSubClient client(MQTT_SERVER, 1883, wifiClient);

void subscribeMqttMessage(char* topic, byte* payload, unsigned int length) {

  mqttTopicValue = getMessage(payload, length);

  processCall(mqttTopicValue.c_str());

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
  if (client.connect(CLIENT_ID, MQTT_USERNAME, MQTT_PASSORD)) {
    client.subscribe(MQTT_TOPIC);
    return true;
  } else {
    return false;
  }
}

void setup() {

  // Begin Serial on 115200
  Serial.begin(BROAD_RATE);

  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  // Connect to the WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWROD);

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

  pcaBoardManager.initPca9685Boards();
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
  light = msg.substring(0, MSG_SIZE);
  jId = light.substring(0, 5);
  bId = light.substring(6, 8);
  pId = light.substring(9, 11);
  val = light.substring(12, MSG_SIZE);

  boardId = atoi(bId.c_str());
  pinId = atoi(pId.c_str());

  doPrint(light, jId, bId, pId, val);
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
