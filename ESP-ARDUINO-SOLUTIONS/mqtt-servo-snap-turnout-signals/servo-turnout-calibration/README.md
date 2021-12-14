# Servo Moter Calibration 

---

> connect the pca9685 board to the arduino in sda and scl pins 


###[servo calibration code download link ](https://github.com/Adarsh-Model-Trains/jmri-mqtt-spring-transformer-wireless-eco-system/raw/v1.production/ESP-SOLUTIONS/zip/servo-turnout-calibration.zip)


### Configuration of the number of boards based on the turnout light and 2 and 3 led signals 
> msut match in node configuraiton in transformer 
```

#define BROAD_RATE 115200
#define DELAY_TIME 10
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

//pin number on the board 
uint8_t servoNumber = 0;   

// change the number of board in the chain sequence and it will pick address automatically 
const int boardInChain = 0;
```