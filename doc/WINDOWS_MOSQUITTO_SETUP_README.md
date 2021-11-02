
# [mosquitto mqtt offical site and documentation ](https://mosquitto.org/)

### SET THE MOSQUITTO_HOME 
* System Properties -> Advance -> Enviorment Variable -> new 
* Variable Name 
```
MOSQUITTO_HOME
```
* Variable Value 
```
C:\Program Files\Mosquitto
```

* Add the MOSQUITTO_HOME to the Path Variable
```
%MOSQUITTO_HOME%
```

### disable the autostart of mosquitto from windows services and change it to manual mode and resrat 

### To create the config file with basic info 
* mosquitto.config
```
log_type all                 #Equivalent to setting -v (verbose mode)
listener 1883                #To ensure listening on the appropriate port
allow_anonymous true         #Allows JMRI to subscribe without an ID or password
```

### To start the mosquitto with config 
* mosquitto -c mosquitto.conf

### To subscribe the mosquitto topic 
* mosquitto_sub -h localhost -v -t /trains/#

### To publish to the mosquitto topic 
* mosquitto_pub -h localhost -t /trains/info -r -m "on"
* mosquitto_pub -h localhost -t /trains/info -r -m "off"


### to create the config with the user name and pwd 
* create a password file with name password.txt 
```
user:password
```
* mosquitto_passwd -U password.txt
```
user:$7$101$wTgP5RJhZ/FwqGd0$791uUt2VkgDi6me7LkX7EGECbxy+FGkCyiQR5hMr6eJGw3drxraJH4rVnTgfy9vV98Wb8/T8KwpF1XOBOcJT+Q==
```
* create a config file with name "mosquitto.config"  in the MOSQUITTO_HOME dir 
```
log_type all                 #Equivalent to setting -v (verbose mode)
listener 1883                #To ensure listening on the appropriate port
allow_anonymous false         #Allows JMRI to subscribe without an ID or password
password_file ./passwordfile.txt
```

### To start the mosquitto with config 
* mosquitto -c mosquitto.conf

### To subscribe the mosquitto topic 
* mosquitto_sub -h localhost -u user -P password -v -t /trains/#

### To publish to the mosquitto topic 
* mosquitto_pub -h localhost -u user -P password -t /trains/info -r -m "on"
* mosquitto_pub -h localhost -u user -P password -t /trains/info -r -m "off"

### cmd flag 
```
-r  Sets retain flag
-n  Sends Null message useful for clearing retain message.
-p – Set Port number Default is 1883
-u – Provide a username
-P – Provide a password
-i – Provide client name
-I – Provide a client id prefix- Used when testing client restrictions using prefix security.
```
