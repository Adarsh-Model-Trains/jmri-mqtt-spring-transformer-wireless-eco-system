
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


int i = 0;
String id;
String val;
String topic;
String message;
String messageText;
String turnoutNumber;
String turnoutState;

Pca9685BoardManager pcaBoardManager;

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;

// 1883 is the listener port for the Broker
PubSubClient client(MQTT_SERVER, 1883, wifiClient);


void subscribeMqttMessage(char* topic, byte* payload, unsigned int length) {

  turnoutNumber = String(topic).substring(22);
  turnoutState = getMessage(payload, length);
  turnoutState.trim();
  processCall(turnoutNumber.toInt(), turnoutState);
  turnoutNumber = "";
  turnoutState = "";
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
void publishSensorData(String turnoutNo, String state) {
  topic = JMRI_MQTT_PUBLISHING_TOPIC + turnoutNo + " ";
  Serial.print(topic + " " + state);
  Serial.println();
  client.publish(topic.c_str(), state.c_str());
}


bool mqttConnect() {
  // Connect to MQTT Server and subscribe to the topic
  if (client.connect(CLIENT_ID, MQTT_USER, MQTT_PWD)) {
    client.subscribe(JMRI_MQTT_SUBSCRIBING_TOPIC);
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
      id = message.substring(0, 5);                     // 40000                  // 40000:CL
      val = message.substring(6, 8);                    // TH | CL                // 40000:TH
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

void processCall(int turnoutNo, String state) {

  Serial.println("TurnoutNo " + String(turnoutNo) + " TurnoutState " + state);

  if (turnoutNo >= SNAP_TURNOUT_START_ADDRESS) {
    turnoutNo = turnoutNo - SNAP_TURNOUT_START_ADDRESS;
    turnoutNo = turnoutNo + TOTOAL_SERVO_TURNOUT;
    turnoutNo = turnoutNo * 2;
    if (state == THROWN) {
      turnoutNo = turnoutNo - 1;
    }
    findBoardPinAndExecute(turnoutNo, state) ;
  } else if (turnoutNo >= SERVO_TURNOUT_START_ADDRESS) {
    turnoutNo = turnoutNo - SERVO_TURNOUT_START_ADDRESS;
    turnoutNo = turnoutNo * 2;
    if (state == THROWN) {
      turnoutNo = turnoutNo - 1;
    }
    findBoardPinAndExecute(turnoutNo, state) ;
  } else {
    Serial.println("Invalid Turnout Number" + String(turnoutNo));
  }
}


void findBoardPinAndExecute(int pinNo, String state) {
  pinNo = pinNo - 1;
  int board = (pinNo / TOTAL_BOARD_PIN);
  if (board <= NO_OF_TOTAL_BOARDS && pinNo <= (NO_OF_TOTAL_BOARDS * TOTAL_BOARD_PIN)) {
    int totalPins = (board * TOTAL_BOARD_PIN);
    int pin = (pinNo - totalPins);
    pin = (pin == -1) ? 0 : pin;
    //doPrint(board, pin, state);
    if (state == THROWN) {
      pcaBoardManager.switchOnSignal(board, pin);
      pcaBoardManager.switchOffSignal( board, pin + 1);
    } else {
      pcaBoardManager.switchOnSignal( board, pin);
      pcaBoardManager.switchOffSignal(board, pin - 1);
    }
  }
}


void doPrint( int boardId, int pinId, String state) {
  Serial.println(" Board Number " + String(boardId) + " Pin Number " + String(pinId) + " Value " + state);
}
