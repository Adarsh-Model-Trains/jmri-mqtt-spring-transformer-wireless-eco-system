# JMRI MQTT DATA TRANSFORMER NODE SELECTOR APPLICATION

### [click to download jar](https://github.com/adarshkumarsingh83/jmri-cmri/raw/main/DOCUMENTS/JMRI-MOSQUITTO-MQTT/jmri-mqtt-spring-transformer-wireless-eco-system/spring-jmri-mqtt-data-transformer/doc/spring-jmri-mqtt-data-transformer.jar)

### [click to download application config file](https://github.com/adarshkumarsingh83/jmri-cmri/raw/main/DOCUMENTS/JMRI-MOSQUITTO-MQTT/jmri-mqtt-spring-transformer-wireless-eco-system/spring-jmri-mqtt-data-transformer/doc/application.config.file.zip)

## Min Requirement 
* java runtime 8 
* mosquitto mqtt server 
* yaml editor to edit configuration files 

### To Run Executable jar of application with default configuration with default profile  
* $ java -jar spring-jmri-mqtt-data-transformer.jar

### To pass the customized configuration file 
> for production profile with external configuration file passed from cmd line \
> NOTE COPY THE application.yaml and application.properties file from doc directory of this application \
> in the same directory where jar file is present then execute the below cmd 
* java -jar -Dspring.profiles.active=prod spring-jmri-mqtt-data-transformer.jar --spring.config.name=application
* or
* java -jar -Dspring.profiles.active=prod spring-jmri-mqtt-data-transformer.jar --spring.config.location=./


### TO ACCESS THE MQTT DATA VIA END POINTS
> NOTE: IF RESULT IS 0:0000:00:00:00 THAT MEAN NODE IS NOT ENABLED FOR APIS \
> curl -X GET http://localhost:8090/amt/node/[nodeId]
* curl -X GET http://localhost:8090/amt/node/1

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



### TO CONFIGURE THE MQTT FOR THE APPLICATION 
```
# Custom property mqtt configuration
mqtt-properties:
  host: tcp://localhost:1883                        #mqtt host and port 
  clientId: adarsh-model-trains-transformer-        #client id for the application for mqtt 
  username: adarsh                                  #mqtt username
  password: password                                #mqtt password
  topicSub: /trains/track/#                         #mqtt jmri root topic to subscribe  
  lightTopic: /trains/track/light/                  #mqtt jmri light topic to subscribe  
  turnoutTopic: /trains/track/turnout/              #mqtt jmri turnout topic to subscribe  
  signalTopic: /trains/track/signalhead/            #mqtt jmri signalhead topic to subscribe
  cleanSession: true                                #session clearing config 
  connectionTimeout: 300                            #connection timeout config 
  keepAliveInterval: 60                             #connection keepalive config 
  automaticReconnect: true                          #connection automatic reconnected when disconnected if true 

```

## TO CONFIGURING THE NODES DATA ON APPLICATION
> CONFIGURE THE VALUES in  src/main/resources/application.yaml
```
node:
  configurations:
    lightStartingAddress: 1000                      #starting address of the light in whole layout its mandatory value 
    turnoutStartingAddress: 10000                   #starting address of the turnout in whole layout its mandatory value 
    signal2LStartingAddress: 20000                  #starting address of the 2 light signal in whole layout its mandatory value 
    signal3LStartingAddress: 30000                  #starting address of the 3 light signal in whole layout its mandatory value 
    signalCacheClearingTime: 5000                   #2Led 3Led signal cache clearence time in case some things is stuck it will flush to topic 
    nodes:
      -
        nodeId: 1                                   # node id/name publish topic will be formed with this id only
        enableNode: true                            # enable the node to processing for jmri data
        enablePublishing: true                      # enable the node to publishing process data to the mqtt topic
        enableRestApi: false                        # to enable the rest service for the node
        apiEndpointCacheSize: 10                    # cache for rest api to hold the data for service call        
        turnoutBoardCount: 3                        # total number of pca9685 configured for turnouts in arduino node
        lightBoardCount: 6                          # total number of pca9685 configured for signal and lights in arduino node
        nodeSubscriptionTopic: /amt/node/1/data/    # topic for every node for reading data from spring transformation application
        lightStartAddress: 1000                     # starting address of the light in node 1 ,if not configured then configure with 0 value 
        lightCount: 10                              # no of light configured in node 1 ,if not configured then configure with 0 value 
        turnoutStartAddress: 10000                  # starting address of the turnout in node 1 ,if not configured then configure with 0 value 
        turnoutCount: 15                            # no of turnout configured in node 1 ,if not configured then configure with 0 value 
        signal2LStartAddress: 20000                 # starting address of the 2 light signal in node 1 ,if not configured then configure with 0 value
        signal2LCount: 64                           # no of signal configured in node 1 ,if not configured then configure with 0 value  
        signal3LStartAddress: 30000                 # starting address of the 3 light signal in node 1 ,if not configured then configure with 0 value 
        signal3LCount: 37                           # no of signal configured in node 1 ,if not configured then configure with 0 value  
                                                    # every light address in jmri for particular node that is the count 
                                                    # every led in signal is having one count so if 3 led in signal count is 3
                                                    # if signal is having 2 light red and green then 2 will be count for signal 
```
## samples which is configured by default
```

# Custom property for nodes configuration
node:
  configurations:
    lightStartingAddress: 1000                    #starting address of the light in whole layout its mandatory value
    turnoutStartingAddress: 10000                 #starting address of the turnout in whole layout its mandatory value
    signal2LStartingAddress: 20000                #starting address of the 2 light signal in whole layout its mandatory value
    signal3LStartingAddress: 30000                #starting address of the 3 light signal in whole layout its mandatory value
    signalCacheClearingTime: 8000                 # after every 5 sec job will clean the cache if its not updated for last 8 sec and if any stale data in cache for specific node
    nodes:
      -
        nodeId: 1                                 # node id/name publish topic will be formed with this id only
        enableNode: true                          # enable the node to process for jmri data
        enablePublishing: true                    # enable the node to publish process data to the mqtt topic
        enableRestApi: false                      # to enable the rest service for the node
        apiEndpointCacheSize: 10                  # cache for rest api to hold the data for service call
        lightStartAddress: 1000
        lightCount: 5                             # 1 pin for each light on the pca9685 board
        turnoutStartAddress: 10000
        turnoutCount: 16                          # 2 pins for each turnout on the pca9685 board (16 * 2) /16 => 16
        signal2LStartAddress: 20000
        signal2LCount: 64                         # 2 pins for each signal light on the pca9685 board  total 16 turnout and every turnout has 2 splitter track (16 * 2 * 2) => 64
        signal3LStartAddress: 30000
        signal3LCount: 30                         # 3 pins for each signal on the pca9685 board  (10 * 3) => 30
        turnoutBoardCount: 2                      # (turnoutCount * 2)/16 :=>  (16 * 2) / 16 => 2
        lightBoardCount: 9                        # (lightCount + signal2LCount + signal3LCount) /16 :=>  (5+32+30)/16 =>  5
        nodeSubscriptionTopic: /amt/node/1/data/  # topic for every node for reading data from spring transformation application
      -
        nodeId: 2
        enableNode: true
        enablePublishing: true
        enableRestApi: false
        lightStartAddress: 1100
        lightCount: 5
        turnoutStartAddress: 10100
        turnoutCount: 15
        signal2LStartAddress: 20100
        signal2LCount: 60
        signal3LStartAddress: 30100
        signal3LCount: 30
        turnoutBoardCount: 2
        lightBoardCount: 7
        nodeSubscriptionTopic: /amt/node/2/data/
        apiEndpointCacheSize: 10
      -
        nodeId: 3
        enableNode: true
        enablePublishing: true
        enableRestApi: false
        lightStartAddress: 1200
        lightCount: 7
        turnoutStartAddress: 10200
        turnoutCount: 15
        signal2LStartAddress: 20200
        signal2LCount: 60
        signal3LStartAddress: 30200
        signal3LCount: 18
        turnoutBoardCount: 2
        lightBoardCount: 6
        nodeSubscriptionTopic: /amt/node/3/data/
        apiEndpointCacheSize: 10
      -
        nodeId: 4
        enableNode: true
        enablePublishing: true
        enableRestApi: false
        lightStartAddress: 1300
        lightCount: 23
        turnoutStartAddress: 10300
        turnoutCount: 10
        signal2LStartAddress: 20300
        signal2LCount: 10
        signal3LStartAddress: 30300
        signal3LCount: 24
        turnoutBoardCount: 2
        lightBoardCount: 3
        nodeSubscriptionTopic: /amt/node/4/data/
        apiEndpointCacheSize: 10
      -
        nodeId: 5
        enableNode: true
        enablePublishing: true
        enableRestApi: false
        lightStartAddress: 1400
        lightCount: 45
        turnoutStartAddress: 10400
        turnoutCount: 10
        signal2LStartAddress: 20400
        signal2LCount: 10
        signal3LStartAddress: 30400
        signal3LCount: 80
        turnoutBoardCount: 10
        lightBoardCount: 8
        nodeSubscriptionTopic: /amt/node/5/data/
        apiEndpointCacheSize: 10
      -
        nodeId: 6
        enableNode: true
        enablePublishing: true
        enableRestApi: false
        lightStartAddress: 1500
        lightCount: 10
        turnoutStartAddress: 10500
        turnoutCount: 15
        signal2LStartAddress: 20500
        signal2LCount: 10
        signal3LStartAddress: 30500
        signal3LCount: 45
        turnoutBoardCount: 2
        lightBoardCount: 4
        nodeSubscriptionTopic: /amt/node/6/data/
        apiEndpointCacheSize: 10
      -
        nodeId: 7
        enableNode: true
        enablePublishing: true
        enableRestApi: false
        lightStartAddress: 1600
        lightCount: 12
        turnoutStartAddress: 10600
        turnoutCount: 48
        signal2LStartAddress: 20600
        signal2LCount: 10
        signal3LStartAddress: 30600
        signal3LCount: 80
        turnoutBoardCount: 6
        lightBoardCount: 6
        nodeSubscriptionTopic: /amt/node/7/data/
        apiEndpointCacheSize: 10
      -
        nodeId: 8
        enableNode: true
        enablePublishing: true
        enableRestApi: false
        lightStartAddress: 1700
        lightCount: 7
        turnoutStartAddress: 10700
        turnoutCount: 21
        signal2LStartAddress: 20700
        signal2LCount: 10
        signal3LStartAddress: 30700
        signal3LCount: 87
        turnoutBoardCount: 3
        lightBoardCount: 6
        nodeSubscriptionTopic: /amt/node/8/data/
        apiEndpointCacheSize: 10
      -
        nodeId: 9
        enableNode: true
        enablePublishing: true
        enableRestApi: false
        lightStartAddress: 1800
        lightCount: 23
        turnoutStartAddress: 10800
        turnoutCount: 10
        signal2LStartAddress: 20800
        signal2LCount: 10
        signal3LStartAddress: 30800
        signal3LCount: 24
        turnoutBoardCount: 3
        lightBoardCount: 3
        nodeSubscriptionTopic: /amt/node/9/data/
        apiEndpointCacheSize: 10
      -
        nodeId: 10
        enableNode: true
        enablePublishing: true
        enableRestApi: false
        lightStartAddress: 1900
        lightCount: 45
        turnoutStartAddress: 10900
        turnoutCount: 23
        signal2LStartAddress: 20900
        signal2LCount: 10
        signal3LStartAddress: 30900
        signal3LCount: 80
        turnoutBoardCount: 3
        lightBoardCount: 8
        nodeSubscriptionTopic: /amt/node/10/data/
        apiEndpointCacheSize: 10
```
### To subscribe the mqtt jmri topic with original jmri messages  
* $  mosquitto_sub -h localhost -u adarsh -P password -v -t '/trains/track/#'

### To subscribe the mqtt application error topic 
* $ mosquitto_sub -h localhost -u adarsh -P password -v -t '/amt/errors/#'

### To subscribe the spring transformer connection  error topic 
* $ mosquitto_sub -h localhost -u adarsh -P password -v -t '/amt/transformer/#'

### To subscribe the mqtt topic where application will publish data after transformation  
* $ mosquitto_sub -h localhost -u adarsh -P password -v -t '/amt/node/#'
```
/amt/node/1/light/ L:1001:05:04:ON
/amt/node/1/light/ L:1001:05:04:OF

/amt/node/1/turnout/ T:10001:00:00:TH
/amt/node/1/turnout/ T:10001:00:01:CL

/amt/node/1/signal/ S:20004:03:02:ON|20005:03:01:OF
/amt/node/1/signal/ S:20004:03:02:OF|20005:03:01:ON
/amt/node/1/signal/ S:20004:03:02:OF|20005:03:01:OF

/amt/node/1/signal/ S:30003:03:02:ON|30002:03:01:OF|30001:03:00:OF
/amt/node/1/signal/ S:30003:03:02:OF|30002:03:01:ON|30001:03:00:OF
/amt/node/1/signal/ S:30003:03:02:OF|30002:03:01:OF|30001:03:00:ON
/amt/node/1/signal/ S:30003:03:02:OF|30002:03:01:OF|30001:03:00:OF

```