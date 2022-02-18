package com.adarsh.model.trains.service;

import com.adarsh.model.trains.beans.ConfigurationDetails;
import com.adarsh.model.trains.beans.NodeConfigurations;
import com.adarsh.model.trains.exception.InvalidNodeIdException;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Async;
import org.springframework.stereotype.Service;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Optional;

@Slf4j
@Service
public class ConfigurationService {

    @Autowired
    MQTTService mqttService;

    @Autowired
    NodeConfigurations nodeConfigurations;

    public List<ConfigurationDetails> getNodeConfigurationDetails() {
        List<ConfigurationDetails> list = new LinkedList<>();
        nodeConfigurations.getNodes().stream().forEach(e -> list.add(new ConfigurationDetails(e, mqttService)));
        return list;
    }

    public List<ConfigurationDetails> getNodeConfigurationDetails(String nodeId) throws InvalidNodeIdException {
        Optional<NodeConfigurations.Nodes> nodesOptional =
                nodeConfigurations.getNodes().stream().filter(e -> e.getNodeId().equalsIgnoreCase(nodeId)).findFirst();
        return Arrays.asList(new ConfigurationDetails(nodesOptional.orElseThrow(() -> new InvalidNodeIdException("Invalid NodeId " + nodeId)), mqttService));
    }


    @Async
    public void testNodeConfiguration(String nodeId) throws Exception {
        log.debug("ConfigurationService.testNodeConfiguration() nodeId {} ", nodeId);
        Optional<NodeConfigurations.Nodes> nodesOptional =
                nodeConfigurations.getNodes().stream().filter(e -> e.getNodeId().equalsIgnoreCase(nodeId)).findFirst();
        NodeConfigurations.Nodes node = nodesOptional.orElseThrow(() -> new InvalidNodeIdException("Invalid NodeId " + nodeId));
        this.triggerTestForServoTurnout(node);
        this.triggerTestForSnapTurnout(node);
        this.triggerTestFor2LedSignal(node);
        this.triggerTestFor3LedSignal(node);
        this.triggerTestForLight(node);
    }


    void triggerTestForServoTurnout(NodeConfigurations.Nodes node) throws Exception {
        for (int i = node.getTurnoutServoStartAddress() + 1; i <= node.getTurnoutServoStartAddress() + node.getTurnoutServoCount(); i++) {
            Thread.currentThread().sleep(2000);
            log.debug("ConfigurationService.triggerTestForServoTurnout() turnoutServo {} state throw", i);
            this.mqttService.processTurnout(i, MQTTService.THROWN);
            Thread.currentThread().sleep(2000);
            log.debug("ConfigurationService.triggerTestForServoTurnout() turnoutServo {} state close", i);
            this.mqttService.processTurnout(i, MQTTService.CLOSED);
        }
    }

    void triggerTestForSnapTurnout(NodeConfigurations.Nodes node) throws Exception {
        for (int i = node.getTurnoutSnapStartAddress() + 1; i <= node.getTurnoutSnapStartAddress() + node.getTurnoutSnapCount(); i++) {
            Thread.currentThread().sleep(2000);
            log.debug("ConfigurationService.triggerTestForSnapTurnout() turnoutSnap {} state throw", i);
            this.mqttService.processTurnout(i, MQTTService.THROWN);
            Thread.currentThread().sleep(2000);
            log.debug("ConfigurationService.triggerTestForSnapTurnout() turnoutSnap {} state close", i);
            this.mqttService.processTurnout(i, MQTTService.CLOSED);
        }
    }

    void triggerTestForLight(NodeConfigurations.Nodes node) throws Exception {
        for (int i = node.getLightStartAddress() + 1; i <= node.getLightStartAddress() + node.getLightCount(); i++) {
            Thread.currentThread().sleep(2000);
            log.debug("ConfigurationService.triggerTestForLight() light {} state on", i);
            this.mqttService.processLight(i, MQTTService.ON);
            Thread.currentThread().sleep(2000);
            log.debug("ConfigurationService.triggerTestForLight() light {} state off", i);
            this.mqttService.processLight(i, MQTTService.OFF);
        }
    }

    void triggerTestFor2LedSignal(NodeConfigurations.Nodes node) throws Exception {
        for (int i = node.getSignal2LStartAddress() + 1; i <= node.getSignal2LStartAddress() + (node.getSignal2LCount() * 2); i += 2) {
            Thread.currentThread().sleep(2000);
            log.debug("ConfigurationService.triggerTestFor2LedSignal() 2ledSignal {} state on", i);
            this.mqttService.processSignal(i, MQTTService.ON);
            this.mqttService.processSignal(i + 1, MQTTService.ON);
            Thread.currentThread().sleep(2000);
            log.debug("ConfigurationService.triggerTestFor2LedSignal() 2ledSignal {} state off", i);
            this.mqttService.processSignal(i, MQTTService.OFF);
            this.mqttService.processSignal(i + 1, MQTTService.OFF);
            i = i + 1;
        }
    }

    void triggerTestFor3LedSignal(NodeConfigurations.Nodes node) throws Exception {
        for (int i = node.getSignal3LStartAddress() + 1; i <= node.getSignal3LStartAddress() + (node.getSignal3LCount() * 3); i += 3) {
            Thread.currentThread().sleep(2000);
            log.debug("ConfigurationService.triggerTestFor3LedSignal() 3ledSignal {} state on", i);
            this.mqttService.processSignal(i, MQTTService.ON);
            this.mqttService.processSignal(i + 1, MQTTService.ON);
            this.mqttService.processSignal(i + 2, MQTTService.ON);
            Thread.currentThread().sleep(2000);
            log.debug("ConfigurationService.triggerTestFor3LedSignal() 3ledSignal {} state off", i);
            this.mqttService.processSignal(i, MQTTService.OFF);
            this.mqttService.processSignal(i + 1, MQTTService.OFF);
            this.mqttService.processSignal(i + 2, MQTTService.OFF);
            i = i + 2;
        }
    }
}
