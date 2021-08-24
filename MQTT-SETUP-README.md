# MQTT SETUP GUIDE

----

# [mosquitto mqtt offical site and documentation ](https://mosquitto.org/)

## To install brew 
$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

## To install mosquitto
$ brew install mosquitto


## doucmentation 
* [documentation](https://mosquitto.org/man/mosquitto-8.html)

---

## To Create custom mosquitto.conf
### [for help ](https://mosquitto.org/man/mosquitto-conf-5.html)
* vi mosquitto.conf
* press i for insert then copy paste below content 
```
log_type all                 #Equivalent to setting -v (verbose mode)
listener 1883                #To ensure listening on the appropriate port
allow_anonymous true         #Allows JMRI to subscribe without an ID or password
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 

---

## To Create User and pwd 
* create a file passwordfile.txt 
```
adarsh:password
```
* $ mosquitto_passwd -U passwordfile.txt 
* this will convert the plane pwd into the encrypted into the passwordfile.txt file 

### Example 
```
$ vi passwordfile.txt
$ cat passwordfile.txt 

adarsh:endless

$ mosquitto_passwd -U passwordfile.txt
$ cat passwordfile.txt 

adarsh:$7$101$wwBOuczh60K8AdjY$w9xVRzB02kNu64+cof8BNeBv/vbjQM9m+ey9G1B6TIxQmYZxrKwnR9L4v6e87bL4SwMgl/L98Qg8mnef9GKhhw==
```


### creating new pwd file pwd will be prompt once cmd is executed 
* $ mosquitto_passwd -c passwordfile.txt user_name 
```
$ Password:
$ Reenter password:
```

### appending into the exisisting pwd file 
* $ mosquitto_passwd -b passwordfile.txt user_name password 
* $ cat passwordfile.txt


## Configuring the user and pwd in to the mosquitto.conf file 
* $ vi mosquitto.conf
* press i for insert then copy paste below content
```
log_type all                 #Equivalent to setting -v (verbose mode)
listener 1883                #To ensure listening on the appropriate port
allow_anonymous false         #Allows JMRI to subscribe without an ID or password
password_file ./passwordfile.txt

```
* esc //to stop inserting text to file
* :w+q // to save and exit the file


### Example 
```
$ mkdir mos-config
$ cd mos-config/

$ vi passwordfile.txt
$ cat passwordfile.txt 

adarsh:endless

$ mosquitto_passwd -U passwordfile.txt
$ cat passwordfile.txt 

adarsh:$7$101$wwBOuczh60K8AdjY$w9xVRzB02kNu64+cof8BNeBv/vbjQM9m+ey9G1B6TIxQmYZxrKwnR9L4v6e87bL4SwMgl/L98Qg8mnef9GKhhw==

$  vi mosquitto.conf
-----------------------------------------------------------------------
log_type all                 #Equivalent to setting -v (verbose mode)
listener 1883                #To ensure listening on the appropriate port
allow_anonymous false         #Allows JMRI to subscribe without an ID or password
password_file ./passwordfile.txt
-----------------------------------------------------------------------


$ vi start-pwd-mos.py
-----------------------
import subprocess

subprocess.call('/usr/local/sbin/mosquitto -c ./mosquitto.conf',shell=True)
-----------------------

$ python start-pwd-mos.py

or 

$ /usr/local/sbin/mosquitto -c mosquitto.conf
```

---


## Start with Configuration  
* To Run with Default Configuration 
	* $ /usr/local/sbin/mosquitto -c /usr/local/etc/mosquitto/mosquitto.conf
* To Run with Custom Configuration 
	* $ /usr/local/sbin/mosquitto -c ./mosquitto.conf

## To subscribe data on mqtt 
### open a new terminal window 
* mosquitto_sub -h localhost -v -t '/trains/#'

### with the User name and pwd 
* mosquitto_sub -h localhost -u username -P password -v -t '/trains/#'

### create python executable  
* $ vi sub.py
```
import subprocess

subprocess.call('mosquitto_sub -h localhost -u adarsh -P password -v -t /trains/#',shell=True)
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 
* to run the script 
  * python sub.py 

## To publish Data on mqtt 
### open a new terminal window 
* mosquitto_pub -h localhost -t /trains/track/turnout/123 -r -m "CLOSED"
* mosquitto_pub -h localhost -t /trains/track/turnout/123 -r -m "THROWN" 

### with the User name and pwd 
* mosquitto_pub -h localhost -u username -P password -t /trains/track/turnout/1 -r -m "CLOSED"
* mosquitto_pub -h localhost -u username -P password -t /trains/track/turnout/1 -r -m "THROWN"  


## python script for start and stop the mosquitto
### Start script with default configuration 
* vi start-mos.py
```
import subprocess

subprocess.call('/usr/local/sbin/mosquitto -c /usr/local/etc/mosquitto/mosquitto.conf',shell=True)
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 
* to run the script 
	* python start-mos.py 

### Start script with custom configuration 
* vi start-cust-mos.py
```
import subprocess

subprocess.call('/usr/local/sbin/mosquitto -c ./mosquitto.conf',shell=True)
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 
* to run the script 
	* python start-cust-mos.py


### Stop script 
* vi stop-mos.py
```
import subprocess

subprocess.call('killall mosquitto',shell=True)
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 
* to run the script 
	* python stop-mos.py 

----