# Arduino Uno/mega client for ir sensors based node 

---

![img](../image/dig8.png)
![img](../image/dig16.png)

> arduino client will connect to the esp via seraila Rx/Tx pins 
> gnd will be common in both the devices 


### Configuration of the number of sensors 
> msut match in the jmri sensors configuration  
```
#define JMRI_SENSOR_START_ADDRESS 10000
#define BROAD_RATE 115200
#define DELAY_TIME 5000
#define NO_OF_BLOCKS 3
```

## IR Sensors pins configuration for arduino in Config.h
```
// IR SENSORS PIN CONFIGURATION 
  const int sensorPin[NO_OF_BLOCKS][PINS] = {
  {BLOCK_1_END_PIN, BLOCK_1_START_PIN },
  {BLOCK_2_END_PIN, BLOCK_2_START_PIN },
  ..........
  {BLOCK_N_END_PIN, BLOCK_N_START_PIN }
  };
```

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

