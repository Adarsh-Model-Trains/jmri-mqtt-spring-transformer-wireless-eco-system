
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
#include "IrSensor.h"

int blockNo;
String topic;
bool isBlockOccuipied;
int sensStatus[NO_OF_BLOCKS];
int sendThreashold[NO_OF_BLOCKS];
IrSensor irSensor;

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;

// 1883 is the listener port for the Broker
PubSubClient client(MQTT_SERVER, 1883, wifiClient);

/*
   pushing the sensor data to the mqtt for jmri
*/
void publishSensorData(String sensorNo, String state) {
  topic = JMRI_MQTT_SENSOR_TOPIC + sensorNo;
  Serial.print(topic + " " + state);
  Serial.println();
  client.publish(topic.c_str(), state.c_str());
}


bool mqttConnect() {
  // Connect to MQTT Server and subscribe to the topic
  if (client.connect(CLIENT_ID, MQTT_USERNAME, MQTT_PASSORD)) {
    client.subscribe(JMRI_MQTT_TOPIC);
    return true;
  } else {
    return false;
  }
}


void setup() {

  // Begin Serial on 115200
  Serial.begin(BROAD_RATE);
  irSensor.init();
  Serial.print(" CONNECTING TO WIFI ");
  Serial.println(WIFI_SSID);

  // Connect to the WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWROD);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(WIFI_RECONNECT_DELAY_TIME);
    Serial.print(".");
  }

  Serial.println();
  Serial.print(" CONNECTED TO WIFI ");
  Serial.print(WiFi.SSID());
  Serial.print(" ");
  Serial.println(WiFi.localIP());

  if (mqttConnect()) {
    Serial.println(" CONNNECTED TO MQTT ");
  } else {
    Serial.println(" ERROR NOT CONNNECTED TO MQTT ");
  }

  for (blockNo = 0; blockNo < NO_OF_BLOCKS; blockNo++) {
    sensStatus[blockNo] = 0;
    sendThreashold[blockNo] = 0;
  }
}

void loop() {
  if (!client.connected()) {
    mqttConnect();
  }
  client.loop();

  for (blockNo = 1 ; blockNo <= NO_OF_BLOCKS; blockNo++) {
    isBlockOccuipied = irSensor.isBlockOccupied(blockNo);
    if (isBlockOccuipied) {
      if (sensStatus[blockNo - 1] != 1) {
        if (sendThreashold[blockNo - 1] < SEND_THRESHOLD) {
          sendThreashold[blockNo - 1] = sendThreashold[blockNo - 1] + 1;
          publishSensorData(String(JMRI_SENSOR_START_ADDRESS + blockNo) , ACTIVE);
        } else {
          sensStatus[blockNo - 1] = 1;
          sendThreashold[blockNo - 1] = 0;
        }
      }

    } else {
      if (sensStatus[blockNo - 1] != 0) {
        if (sendThreashold[blockNo - 1] < SEND_THRESHOLD) {
          sendThreashold[blockNo - 1] = sendThreashold[blockNo - 1] + 1;
          publishSensorData(String(JMRI_SENSOR_START_ADDRESS + blockNo) , INACTIVE);
        } else {
          sendThreashold[blockNo - 1] = 0;
          sensStatus[blockNo - 1] = 0;
        }
      }
    }
  }
  delay(DELAY_TIME);
}
