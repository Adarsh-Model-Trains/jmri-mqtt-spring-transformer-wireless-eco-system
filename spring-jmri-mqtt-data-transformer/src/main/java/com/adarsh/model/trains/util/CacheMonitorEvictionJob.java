package com.adarsh.model.trains.util;

import com.adarsh.model.trains.beans.NodeConfigurations;
import com.adarsh.model.trains.service.MQTTService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

import static com.adarsh.model.trains.service.MQTTService.*;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */

@Slf4j
@Component
public class CacheMonitorEvictionJob {

    @Autowired
    NodeConfigurations nodeConfigurations;


    @Autowired
    MQTTService mqttService;

    @Scheduled(cron = "*/5 * * * * *")
    public void clearCache() {
        nodeConfigurations.getNodes().stream().forEach(node -> {
            if (node.getEnableNode() && node.getEnableRestApi()) {
                try {
                    if (cache2LedTime.get(node.getNodeId())
                            + nodeConfigurations.getSignalCacheClearingTime() < System.currentTimeMillis()
                            && !cache2Led.get(node.getNodeId()).isEmpty()) {
                        this.mqttService.flushCache(node, cache2Led);
                    }

                    if (cache3LedTime.get(node.getNodeId())
                            + nodeConfigurations.getSignalCacheClearingTime() < System.currentTimeMillis()
                            && !cache3Led.get(node.getNodeId()).isEmpty()) {
                        this.mqttService.flushCache(node, cache3Led);
                    }
                } catch (Exception e) {
                    log.error("Exception CacheMonitorEvictionJob.clearCache() ={}", e.getLocalizedMessage());
                }
            }
        });
    }
}