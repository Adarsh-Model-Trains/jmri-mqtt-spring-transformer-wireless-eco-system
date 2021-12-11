package com.adarsh.model.trains.handler;

import com.adarsh.model.trains.service.MQTTService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.Message;
import org.springframework.messaging.MessageHandler;
import org.springframework.messaging.MessagingException;
import org.springframework.stereotype.Component;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */

@Slf4j
@Component
public class MQTTMessageHandler implements MessageHandler {

    private final static String TOPIC_HEADER_NAME = "mqtt_receivedTopic";

    @Autowired
    MQTTService mqttService;

    @Override
    public void handleMessage(Message<?> message) throws MessagingException {
        try {
            log.info("Message Received on Mqtt topic={} with Data={} "
                    , message.getHeaders().get(TOPIC_HEADER_NAME) + ""
                    , message.getPayload().toString());
            // implementation to put back to the proper topic back in mqtt
            this.mqttService.transformData(message.getHeaders().get(TOPIC_HEADER_NAME) + ""
                    , message.getPayload().toString());

        } catch (Exception e) {
            log.error("Exception while handle message in Mqtt Handler ", e.getMessage());
        }
    }
}
