# JMRI MQTT WIRELESS ECO SYSTEM 


## [YOUTUBE HELP LINK ](doc/YOUTUBE-README.md)	

![img](image/implementation.png)

> Jmri will push the data to the mqtt topic \
> spring transformer application configured with nodes and its details like no of turnout, no of signals, no of light in the node \
> every nodes has PCA9685 boards configured in series for turnout light and signals \
> transformer application will read the data from mqtt topics which is pushed by jmri and transform that data node wise  \
> and push back to the mqtt for specific nodes, also store data in end points cache if enabled for serving data via rest endpoints  \
> node wise topics for each esp8266 node will have only relevant data\
> this will reduce the processing on the esp8266 so that it can handle node specific data properly. \
> esp8266 will read data from mqtt nodewise topic or can direclty make http rest endpoint call to spring application and get the data \
> esp8266 will pass the data to the arduino uno or mega via serial line and arduino will do the rest for signals, turnouts, or lights 


### GUIDELINES & ASSUMPTIONS 
* N NUMBER UNIQUE ID NODE CAN BE CONFIGURED WHICH CAN HAVE LIGHT TURNOUT AND SINGALS 
* SENSORS DOESN'T BELONGS TO ANY NODES IT DIRECTLY PUBLISH SENSORS DATA TO JMRI VIA MQTT TOPICS OR VIA REST API
* ALL LIGHTS WILL START FROM 10000 JMRI ADDRESS ONWARDS TILL 9999 
* ALL 2LED(RED,GREEN) SIGNAL WILL START FROM 20000 JMRI ADDRESS ONWARDS TO 29999
* ALL 3LED(RED,YELLOW,GREEN) SIGNAL WILL START FROM 30000 JMRI ADDRESS ONWARDS TO 39999
* ALL SERVO TURNOUT WILL START FROM 40000 JMRI ADDRESS ONWARDS TILL 49999
* ALL SNAP TURNOUT WILL START FROM 50000 JMRI ADDRESS ONWARDS TILL 59999  
* ALL SENSORS IR BASED OR CT BASED START FROM 10000 JMRI ADDRESS ONWARDS TILL SYSTEM SUPPORTS 
* ESP8266 IS WILL SUSCRIBE LIGHT,TURNOUT & SIGNAL DATA DIRECTLY FROM MQTT OR VIA REST ENDPOINTS HOSTED FROM SPRING APPLICATION (SEPRATE CHANNAL FOR SBUSCRIBING)
* ESP8266 WILL PUBLISH SENSOR DATA DIRECTLY TO MQTT OR VIA REST ENDPOINT HOSTED FROM SPRING APPLICATION (SEPRATE CHANNAL FOR PUBLISHING)
* ARDUINO WILL EXECUTE THE CMD FOR LIGHT, TURNOUT & SIGNALS SEND BY JMRI TO MQTT,TO SPRING APPLCATION FOR TRANSFFORMATION THEN VIA ESP TO ARDUINO 
* ARDUINO WILL GET IR OR CT SENSORS DATA AND SEND TO ESP FOR PUBLISHING.
* ARDUINO WILL BE CONNECTED WITH THE CHAIN OF THE PCA9685 BOARD FOR SERVO TURNOUT, SNAPSWTICH FOR TURNOUT FOR LIGHT AND SINGAL LED 
* PCA9685 BOARDS WILL BE IN ORDER OF FIRST N BOARD WILL BE FOR SERVO TURNOUT OR SNAP TURNOUT THEN FOLLOWED BY SIGNAL AND LIGHTS 

### CONFIGURATIONS STEPS 
* java 8 runtime installation 
* Mqtt installation and start see [MQTT SETUP GUILDE LINK ](doc/MQTT-SETUP-README.md)
* jmri installation and configured with mqtt see [JMRI MQTT CONNECTION SETUP AND TESTING ](doc/JMRI-MQTT-SETUP-README.md)
* spring data transformation application installation and execution details see [SPRING TRANSFORMATOIN APPLICATION ](spring-jmri-mqtt-data-transformer/README.md)
* servo calibration application for getting open and close range [SERVO CALIBRATION APPLICATION](ESP-SOLUTIONS/servo-turnout-calibration/README.md)
* reading data after transformaton see below section 

---

# Implementation types 

## rest and mqtt based implementations nodes 
![img](image/nodes-mqtt-rest.png)

## SPRING TRANSFORMER DATA FLOW 
![img](image/spring-mqtt-spring-transformer.png)

## mqtt based implementations
![img](image/mqtt.png)

## rest based implementations
![img](image/rest.png)

## Data flow 
### Downstream data 
	jmri -> mqtt -> springtransformer -> mqtt -> esp -> arduino -> pca9685 -> ledsignal|servoturnout|relayswitch snapturnout 
### Upstream data 
	ct sensor | irsensor -> arduino -> esp -> mqtt -> jmri 
![img](image/dig1.png)

## Data flow 
### Downstream data 
	jmri -> mqtt -> springtransformer -> restapi -> esp -> arduino -> pca9685 -> ledsignal|servoturnout|relayswitch snapturnout 
### Upstream data 
	ct sensor | irsensor -> arduino -> esp -> restapi -> spring transformer -> mqtt -> jmri 
![img](image/dig3.png)

## Data flow 
### Downstream data 
	jmri -> mqtt -> springtransformer -> mqtt -> esp -> pca9685 -> ledsignal|servoturnout|relayswitch snapturnout 
### Upstream data
	ct sensor | irsensor ->  esp -> mqtt -> jmri 
![img](image/dig2.png)

## Data flow 
### Downstream data 
	jmri -> mqtt -> springtransformer -> restapi -> esp -> pca9685 -> ledsignal|servoturnout|relayswitch snapturnout 
### Upstream data
	ct sensor | irsensor -> esp -> restapi -> spring transformer -> mqtt -> jmri 
![img](image/dig4.png)

---

### [MQTT SETUP GUILDE LINK ](doc/MQTT-SETUP-README.md)

### [JMRI MQTT CONNECTION SETUP AND TESTING LIGHT SIGNAL TURNOUT SENSORS ](doc/JMRI-MQTT-SETUP-README.md)

### [CONNECTION DETAILS FOR ESP AND ARDUINO ](doc/ESP-ARDUINO-CONNECTON-README.md)

### [CONNECTION DETAILS FOR PCA9685 BOARD AND ARDUINO ](doc/PCA9685-README.md)

### [SERVO CALIBRATION APPLICATION](servo-turnout-calibration/README.md)

---

## CODE IMPLEMENATIONS 

### [SPRING TRANSFORMATOIN APPLICATION SETUP AND EXECUTION ](spring-jmri-mqtt-data-transformer/README.md)

### [FOR ESP8266 BASED MQTT,REST  BASED BLOCK DETECTION, SIGNALS, LIGHT AND TURNOUT CONTROLES ](ESP-SOLUTIONS/)

### [FOR ESP8266 & ARDUINO BASED MQTT,REST  BASED BLOCK DETECTION, SIGNALS, LIGHT AND TURNOUT CONTROLES ](ESP-ARDUINO-SOLUTIONS/)


