package com.adarsh.model.trains.util;

import com.adarsh.model.trains.beans.NodeConfigurations;
import com.adarsh.model.trains.service.MQTTService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

import static com.adarsh.model.trains.service.MQTTService.*;

@Slf4j
@Component
public class CacheMonitorEvectionJob {

    @Autowired
    NodeConfigurations nodeConfigurations;

    @Autowired
    MQTTService mqttService;

    @Scheduled(cron = "*/5 * * * * *")
    public void clearCache() {
        nodeConfigurations.getNodes().stream().forEach(node -> {
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
                log.error("Exception CacheMonitorEvectionJob.clearCache() ={}", e.getLocalizedMessage());
            }
        });
    }
}