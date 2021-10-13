# ESP8266 SPRING TRANSFORMER REST CLIENT PUBLISHER

---

![img](../image/dig15.png)
![img](../image/dig16.png)

> esp will conect to spring transformation application via wifi network 
> wifi credentials will be configured in Config.h file 
```
const char* ssid = "adarsh_radha_2G"; // ESP8266 do not support 5G wifi connection
const char* wifi_password = "*******";

```

> spring transformation rest service url configured in Config.h file 
* "http://localhost:8090/amt/node/<NODE_ID>";
```
const char* SERVER_URL = "http://192.168.0.188:8090/amt/node/1";
```

### TO POST THE SENSOR INFO TO  MQTT  VIA END POINTS 
> curl --header "Content-Type: application/json" --request POST --data '{"topic":"xyz","data":"xyz"}' http://localhost:8090/amt/node/[nodeId]
* curl --header "Content-Type: application/json" \
  --request POST \
  --data '{"topic":"/trains/track/sensor/1","data":"INACTIVE"}' \
  http://localhost:8090/amt/node/1
  
* curl --header "Content-Type: application/json" \
  --request POST \
  --data '{"topic":"/trains/track/sensor/1","data":"ACTIVE"}' \
  http://localhost:8090/amt/node/1



### jmri configuration 
* all sensors will start from 10000 to limit 


## To Open Two arduino sperate ide on mac 
* $ open -n -a Arduino
* -n = open new instance even when one is already running
* -a xxx = open application xxx


### Connection details 
```
conect the gnd from arduino to the -ve line of the breadboard 
take nodemcu/esp8266 connect the gnd/-ve from breadboard to the gnd of the nodemcu/esp8266
take the tx pin of the nodemcu/esp8266 and connect to the rx pin of the arduino 
take the rx pin of the nodemcu/esp8266 and connect to the tx pin of the arduino 

```


![img](../image/con.JPG)
