# ESP8266 MQTT PUBLISHER CLIENT FOR CT SENSORS 

---
## Lib installtion 

### search for "ESP8266WiFi" lib and install it before compiling 
### or install the wifi lib for esp8266 [esp8266wifi lib](https://github.com/Adarsh-Model-Trains/jmri-mqtt-spring-transformer-wireless-eco-system/raw/main/lib/ESP8266WiFi.zip)


## Code Download 
### [esp8266-mqtt-ct-sensor](https://github.com/Adarsh-Model-Trains/jmri-mqtt-spring-transformer-wireless-eco-system/raw/v1.production/ESP-SOLUTIONS/zip/esp8266-mqtt-ct-sensor.zip)


![img](../../image/dig11.png)

> esp will conect to mqtt via wifi network 
> wifi credentials will be configured in Config.h file 
```
// ESP8266 do not support 5G wifi connection
#define WIFI_SSID "adarsh-model-trains"
#define WIFI_PASSWROD "adarsh@model@trains"
```
> mqtt configuration and credentail will be configured in Config.h file 
```
#define MQTT_SERVER "192.168.0.188"
#define MQTT_USERNAME "adarsh"
#define MQTT_PASSORD "password"
```

> esp client id is configure in Config.h 
```
#define CLIENT_ID  "JMRI_NODE_ESP8266_PUBLISHING_1"

```

### Configuration of the number of sensors 
> msut match in the jmri sensors configuration  
```
#define JMRI_SENSOR_START_ADDRESS 10000
#define NO_OF_BLOCKS 2
#define ENABLE_PULLUP true
```

### sensors pins config
```
const int sensorPin[NO_OF_BLOCKS] = {
  7, 6
};
```


### jmri configuration 
* all sensors will start from 10000 to limit 

## To Open Two arduino sperate ide on mac 
* $ open -n -a Arduino
* -n = open new instance even when one is already running
* -a xxx = open application xxx

