
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

// Enables the ESP8266 to connect to the local network (via WiFi)
#include <ESP8266WiFi.h>
// Allows us to connect to, and publish to the MQTT broker
#include "PubSubClient.h"
#include"Config.h"
#include "Pca9685BoardManager.h"

int pinId;
int i = 0;
String id;
String val;
String jId;
String bId;
String pId;
int boardId;
int jmriId;
String topic;
String message;
char type = '-';
String inputVal;
String messageText;
String mqttTopicValue;


// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;

// 1883 is the listener port for the Broker
PubSubClient client(MQTT_SERVER, 1883, wifiClient);

Pca9685BoardManager pcaBoardManager;



void subscribeMqttMessage(char* topic, byte* payload, unsigned int length) {

  mqttTopicValue = getMessage(payload, length);

  processCall(mqttTopicValue.c_str());

  mqttTopicValue = "";
}

/*
   converting message from mqtt bytes to string
*/
String getMessage(byte* message, int length) {
  messageText = "";
  for ( i = 0; i < length; i++) {
    messageText += (char)message[i];
  }
  return messageText + "\n";
}

/*
   pushing the sensor data to the mqtt for jmri
*/
void publishSensorData(String sensorNo, String state) {
  topic = JMRI_MQTT_TOPIC + sensorNo;
  Serial.print(topic + " " + state);
  Serial.println();
  client.publish(topic.c_str(), state.c_str());
}


bool mqttConnect() {
  // Connect to MQTT Server and subscribe to the topic
  if (client.connect(CLIENT_ID, MQTT_USER, MQTT_PWD)) {
    client.subscribe(MQTT_TOPIC);
    return true;
  } else {
    return false;
  }
}


void setup() {

  // Begin Serial on 115200
  Serial.begin(BROAD_RATE);

  Serial.print("CONNECTING TO WIFI ");
  Serial.println(WIFI_SSID);

  // Connect to the WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWROD);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(WIFI_RECONNECT_DELAY_TIME);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println();
  Serial.print("CONNECTED TO WIFI ");
  Serial.print(WiFi.SSID());
  Serial.print(" ");
  Serial.println(WiFi.localIP());
  
  client.setCallback(subscribeMqttMessage);
  
  // Connect to MQTT Broker
  if (mqttConnect()) {
    Serial.println("CONNNECTED TO MQTT  ");
  } else {
    Serial.println("NOT CONNNECTED TO MQTT  ");
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

  while (Serial.available()) {
    message = Serial.readString();
    if (message != "") {
      id = message.substring(0, 5); // 40000                  // 40000:CL
      val = message.substring(6, 8); // TH | CL         // 40000:TH
      if (val == TH) {
        publishSensorData(id, THROWN);
      } else {
        publishSensorData(id, CLOSED);
      }
      id = "";
      val = "";
      message = "";
    }
  }
  delay(DELAY_TIME);
}

void processCall(String msg) {

  Serial.println(" Message " + msg);
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
  }

  type = '-';
}

void doExecute(String msg , char type) {
  inputVal = msg.substring(0, MSG_SIZE);
  jId = inputVal.substring(0, 5);
  bId = inputVal.substring(6, 8);
  pId = inputVal.substring(9, 11);
  val = inputVal.substring(12, MSG_SIZE);

  boardId = atoi(bId.c_str());
  pinId = atoi(pId.c_str());

  doPrint(inputVal, jId, bId, pId, val);
  if (boardId <= NO_OF_TOTAL_BOARDS) {
    if ( type == S) {
      if (val == ON) {
        pcaBoardManager.switchOnSignal(boardId, pinId);
      } else {
        pcaBoardManager.switchOffSignal( boardId, pinId);
      }
    }
  } else {
    Serial.println(BOARDS_CONFIG);
  }
}

void doPrint(String input, String jmriId, String boardId, String pinId, String state) {
  Serial.println("Input " + input + " Number " + jmriId + " Board Number " + boardId + " Pin Number " + pinId + " Value " + state);
}
