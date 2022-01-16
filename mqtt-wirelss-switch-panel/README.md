# mqtt-wirelss-switch-panel

----

## Testing 

### snap turnout 
* mosquitto_pub -h localhost -u adarsh -P password -t /trains/track/turnout/40001 -r -m "THROWN"
* mosquitto_pub -h localhost -u adarsh -P password -t /trains/track/turnout/40001 -r -m "CLOSED"

### servo turnout 
* mosquitto_pub -h localhost -u adarsh -P password -t /trains/track/turnout/50001 -r -m "THROWN"
* mosquitto_pub -h localhost -u adarsh -P password -t /trains/track/turnout/50001 -r -m "CLOSED"


