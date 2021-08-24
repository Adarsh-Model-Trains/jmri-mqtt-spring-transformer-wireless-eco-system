
import subprocess 

subprocess.call('mosquitto_sub -h localhost -u adarsh -P password -v -t /trains/#',shell=True)
