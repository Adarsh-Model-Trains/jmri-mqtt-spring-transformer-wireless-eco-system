
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
#include "CtSensor.h"

int address = 1;
int blockNo = 0;
int sensStatus[NO_OF_BLOCKS];
CtSensor ctSensor;

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;

// 1883 is the listener port for the Broker
PubSubClient client(MQTT_SERVER, 1883, wifiClient);


/*
   pushing the sensor data to the mqtt for jmri
*/
void publishSensorData(String sensorNo, String state) {
  String topic = JMRI_MQTT_SENSOR_TOPIC + sensorNo;
  Serial.print(topic + " " + state);
  Serial.println();
  client.publish(topic.c_str(), state.c_str());
}


bool mqttConnect() {
  // Connect to MQTT Server and subscribe to the topic
  if (client.connect(CLIENT_ID, MQTT_USER, MQTT_PWD)) {
    client.subscribe(JMRI_MQTT_TOPIC);
    return true;
  } else {
    return false;
  }
}


void setup() {

  // Begin Serial on 115200
  Serial.begin(BROAD_RATE);

  Serial.print("Connecting to ");
  Serial.println(SS_ID);

  // Connect to the WiFi
  WiFi.begin(SS_ID, WIFI_PWD);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  if (mqttConnect()) {
    Serial.println("Connected Successfully to MQTT Broker!");
  } else {
    Serial.println("Connection Failed!");
  }

  ctSensor.initCtSensor(NO_OF_BLOCKS);
  for (int i = 0; i < NO_OF_BLOCKS; i++) {
    ctSensor.setSensorPin(i + 1, sensorPin[i]);
    sensStatus[i] = 0;
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

  for (blockNo = 1 ; blockNo <= NO_OF_BLOCKS; blockNo++) {
    bool isBlockOccuipied = ctSensor.isSensorActive(blockNo);
    if (isBlockOccuipied) {
      if (sensStatus[blockNo - 1] != 1) {
        sensStatus[blockNo - 1] = 1;
        publishSensorData(String(JMRI_SENSOR_START_ADDRESS + blockNo) , ACTIVE);
      }
    } else {
      if (sensStatus[blockNo - 1] != 0) {
        sensStatus[blockNo - 1] = 0;
        publishSensorData(String(JMRI_SENSOR_START_ADDRESS + blockNo) , INACTIVE);
      }
    }
  }
  delay(DELAY_TIME);
}
