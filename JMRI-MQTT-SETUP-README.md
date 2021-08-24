

# JMRI WITH MQTT MOSQUITTO
* [JMRI DOC LINK ](https://www.jmri.org/help/en/html/hardware/mqtt/index.shtml)

----

## JMRI WILL CREATE FOLOWING CHANNEL IN MQTT
* /trains/track/light/[LIGHT_NO] [STATUS] ON|OFF
* /trains/track/turnout/[TURNOUT_NO] [STATUS] THROW|CLOSE
* /trains/track/sensor/[SENSOR_NO] [STATUS] ACTIVE|INACTIVE

```
$ python start-mos.py

$ mosquitto_sub -h localhost -v -t '/trains/track/#'
/trains/track/light/3 OFF
/trains/track/light/3 ON
/trains/track/turnout/1 THROW
/trains/track/turnout/1 CLOSED
/trains/track/sensor/1 INACTIVE
/trains/track/sensor/1 ACTIVE

$ python stop-mos.py

```



### start the mqtt server and connect the jmri to the mqtt server 
```
* $ python start-mos.py

* panel pro -> preferences -> Connections 

System Manufacturer => MQTT
System connection => MQTT 
Settings 
   hostname : localhost
   connection prefix : M 
   Connection Name : MQTT 
   check on additional connection setings 


 save the connection it will be saved and connected to the mqtt server 


```
### WITHOUT USERNAME AND PASSWORD 

![img](image/1.png)

![img](image/2.png)


### WITH USERNAME AND PASSWORD 

![img](image/16.png)


### CREATING TURNOUT LIGHTS AND SENSORS IN PANELPRO 

![img](image/3.png)

![img](image/4.png)

### create a turnout  
```
Panel pro -> tools -> tables -> turnout -> 
click on add button 

 System Connection : MQTT 
 Hardware ADdress : 1 
 User Name : T1 

 Click on Create button 
 NOTE : Light and Turnout will share the same output address slots so don't use same for light and turnout 
 NOTE : do it for the number of turnout we want to create 

```
![img](image/5.png)

### create a Light  
```
Panel pro -> tools -> tables -> Light -> 
click on add button 

 System Connection : MQTT 
 Hardware ADdress : 3 
 User Name : L3 

 Click on Create button 
 NOTE : Light and Turnout will share the same output address slots so don't use same for light and turnout 
 NOTE : do it for the number of Light we want to create 


```

![img](image/6.png)

![img](image/7.png)

### Testing Turnout with MQTT 
```
start the terminal mqtt client to see the output of the jmri cmd executed behind the turnout and light button 

$ mosquitto_sub -h localhost -v -t '/trains/track/#'

and click on the T1 and T2 turnout button throw and close and see the output of them in the console of mqtt client 

```
![img](image/8.png)

### Testing Light with MQTT 
```
start the terminal mqtt client to see the output of the jmri cmd executed behind the turnout and light button 

$ mosquitto_sub -h localhost -v -t '/trains/track/#'

and click on the L3 and L4 light button on and off and see the output of them in the console of mqtt client 

```
![img](image/9.png)


### Testing Signalhead with MQTT 
[SIGNALHEADS TYPES DETAILS LINK](https://www.jmri.org/help/en/package/jmri/jmrit/beantable/SignalAddEdit.shtml)



## Sensor Testing 

![img](image/20.png)

![img](image/21.png)

### Active to Inactive 
### Subscribing to the Sensor topic 
* $ mosquitto_sub -h localhost -u adarsh -P password -v -t '/trains/#'
```
/trains/track/sensor/1 ACTIVE
/trains/track/sensor/1 INACTIVE
```

### Publishing to the Sensor topic 
* $ mosquitto_pub -h localhost -u adarsh -P password -t /trains/track/sensor/1 -r -m "INACTIVE"


![img](image/19.png)


### InActive to Active
### Subscribing to the Sensor topic 
* $ mosquitto_sub -h localhost -u adarsh -P password -v -t '/trains/#'
```
/trains/track/sensor/1 INACTIVE
/trains/track/sensor/1 ACTIVE
```

### Publishing to the Sensor topic 
* $ mosquitto_pub -h localhost -u adarsh -P password -t /trains/track/sensor/1 -r -m "ACTIVE"

![img](image/18.png)
