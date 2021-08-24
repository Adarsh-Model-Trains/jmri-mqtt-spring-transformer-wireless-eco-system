# JMRI MQTT SPRING TRANSFORMER ESP AND ARDUINO WIRELESS ECO SYSTEM 

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
* ALL LIGHTS WILL START FROM 1000 JMRI ADDRESS ONWARDS TILL 9999 
* ALL TURNOUT WILL START FROM 10000 JMRI ADDRESS ONWARDS TILL 19999  
* ALL 2LED(RED,GREEN) SIGNAL WILL START FROM 20000 JMRI ADDRESS ONWARDS TO 29999
* ALL 3LED(RED,YELLOW,GREEN) SIGNAL WILL START FROM 30000 JMRI ADDRESS ONWARDS TILL SYSTEM SUPPORTS
* ALL SENSORS IR BASED OR CT BASED START FROM 10000 JMRI ADDRESS ONWARDS TILL SYSTEM SUPPORTS 
* ESP8266 IS WILL SUSCRIBE LIGHT,TURNOUT & SIGNAL DATA DIRECTLY FROM MQTT OR VIA REST ENDPOINTS HOSTED FROM SPRING APPLICATION (SEPRATE CHANNAL FOR SBUSCRIBING)
* ESP8266 WILL PUBLISH SENSOR DATA DIRECTLY TO MQTT OR VIA REST ENDPOINT HOSTED FROM SPRING APPLICATION (SEPRATE CHANNAL FOR PUBLISHING)
* ARDUINO WILL EXECUTE THE CMD FOR LIGHT, TURNOUT & SIGNALS SEND BY JMRI TO MQTT,TO SPRING APPLCATION FOR TRANSFFORMATION THEN VIA ESP TO ARDUINO 
* ARDUINO WILL GET IR OR CT SENSORS DATA AND SEND TO ESP FOR PUBLISHING.
* ARDUINO WILL BE CONNECTED WITH THE CHAIN OF THE PCA9685 BOARD FOR SERVO TURNOUT, SNAPSWTICH FOR TURNOUT FOR LIGHT AND SINGAL LED 


### CONFIGURATIONS STEPS 
* java 8 runtime installation 
* Mqtt installation and start see [MQTT SETUP GUILDE LINK ](MQTT-SETUP-README.md)
* jmri installation and configured with mqtt see [JMRI MQTT CONNECTION SETUP AND TESTING ](JMRI-MQTT-SETUP-README.md)
* spring data transformation application installation and execution details see [SPRING TRANSFORMATOIN APPLICATION ](spring-jmri-mqtt-data-transformer/README.md)
* servo calibration application for getting open and close range [SERVO CALIBRATION APPLICATION](servo-turnout-calibration/README.md)
* reading data after transformaton see below section 

---

## FOR LIGHT TURNOUT AND SIGNALS 

## BELOW COMBINATION OF IMPLEMENTATION CAN BE USE FOR SIGNAL TURNOUT AND LIGHT 
* Esp code direct mqtt subsciber -> Arduino code servo turnout and led switch 
* Esp code direct mqtt subsciber -> Arduino code relay switch turnout and led switch 
* Esp code rest client subsciber -> Arduino code servo turnout and led switch 
* Esp code rest client subsciber -> Arduino code relay switch turnout and led switch 


### ESP code 

* for reading data directly via mqtt topic using esp8266 
	* [link for configuraiton and deplayment and setup ](esp8266-transformation-mqtt-client/README.md)		
	
* for reading data from the rest service of the spring transformer application 
	* [link for configuraiton and deplayment and setup ](esp8266-transformer-rest-client/README.md)		


### ARDUINO code
* forwarding data to arduino with servo turnout configuration 
	* [link for configuraiton and deplayment and setup ](arduino-slave-node-servoswitch-ledsignal/README.md)	
	* [link for configuration and connnection for PCA9685 board &  arduino ](PCA9685-README.md)	
* forwarding data to arduino with relay switich snap turnout configuraion 
	* [link for configuraiton and deplayment and setup ](arduino-slave-node-snapswitch-ledsignal/README.md)		


## BELOW IMPLEMENTATION CAN BE USE FOR SIGNAL TURNOUT AND LIGHT 
* Esp code direct mqtt subsciber servo turnout and led switch 
* Esp code direct mqtt subsciber relay switch turnout and led switch 

### ESP code 

* for reading data from the rest service of the spring transformer application and executing directly with snap turnout and light  
	* [link for configuraiton and deplayment and setup ](esp8266-transformer-rest-client-snapswitch-signal-node/README.md)	

* for reading data from the rest service of the spring transformer application and executing directly with servo turnout and light  
	* [link for configuraiton and deplayment and setup ](esp8266-transformer-rest-client-servowitch-signal-node/README.md)	

* for reading data from the mqtt topic of the spring transformer application and executing directly with snap turnout and light  
	* [link for configuraiton and deplayment and setup ](esp8266-transformer-mqtt-client-snapswitch-signal-node/README.md)	

* for reading data from the mqtt topic of the spring transformer application and executing directly with servo turnout and light  
	* [link for configuraiton and deplayment and setup ](esp8266-transformer-mqtt-client-servowitch-signal-node/README.md)	

---

## FOR SENSORS | BLOCK OCCUPANCY SENSORS 

## BELOW COMBINATION OF IMPLEMENTATION CAN BE DONE FOR SENSORS 
* Esp code direct mqtt publisher -> Arduino ir sensor
* Esp code direct mqtt publisher -> Arduino ct sensor 
* Esp code rest client publisher -> Arduino ir sensor
* Esp code rest client publisher -> Arduino ct sensor 

### ESP code 
* configuraing the sensros for block occupancy 
	* direclty publishing data to the MQTT topic 
		* [link for configuraiton and deployment and setup ](esp8266-sensors-mqtt-client/README.md)		
	* publishing data to the spring transforer application via rest endpoints 
		* [link for configuraiton and deployment and setup ](esp8266-sensor-rest-client/README.md)		

### ARDUINO code 		
* configuring ir sensor based block decection arduino node 
	* [link for configuraiton and deployment and setup ]()		
* configuring ct sensor based block decection arduino node 		
	* [link for configuraiton and deployment and setup ]()		

----

### [MQTT SETUP GUILDE LINK ](MQTT-SETUP-README.md)

### [JMRI MQTT CONNECTION SETUP AND TESTING LIGHT SIGNAL TURNOUT SENSORS ](JMRI-MQTT-SETUP-README.md)

### [CONNECTION DETAILS FOR ESP AND ARDUINO ](ESP-ARDUINO-CONNECTON-README.md)

### [CONNECTION DETAILS FOR PCA9685 BOARD AND ARDUINO ](PCA9685-README.md)

### [SERVO CALIBRATION APPLICATION](servo-turnout-calibration/README.md)


## SPRING TRANSFORMER APPLICATION 

### [SPRING TRANSFORMATOIN APPLICATION SETUP AND EXECUTION ](spring-jmri-mqtt-data-transformer/README.md)


## FOR SIGNAL LIGHT AND TURNOUT 

### [ESP8266 MQTT SUBSCRIBER CONFIGURATION ](esp8266-transformation-mqtt-client/README.md)		

### [ESP8266 REST CLIENT SUBSCRIBER CONFIGURATION ](esp8266-transformer-rest-client/README.md)	

### [ARDUINO SERVO TURNOUT & SIGNALS NODE CONFIGURATION ](arduino-slave-node-servoswitch-ledsignal/README.md)

### [ARDUINO RELAYSWITCH SNAP TURNOUT & SIGNALS NODE CONFIGURATION ](arduino-slave-node-snapswitch-ledsignal/README.md)	


## FOR SENSORS | BLOCK OCCUPANCY SENSORS 

### [ESP8266 MQTT PUBLISHER CONFIGURATION  ](esp8266-sensors-mqtt-client/README.md)	

### [ESP8266 REST CLIENT PUBLISHER CONFIGURATION ](esp8266-sensor-rest-client/README.md)	

### [ARDUINO IR SENSORS NODE CONFIGURATION  ](arduino-slave-node-ir-sensor-client/README.md)	

### [ARDUINO CT SENSORS NODE CONFIGURATION ](arduino-slave-node-ct-sensor-client/README.md)	
