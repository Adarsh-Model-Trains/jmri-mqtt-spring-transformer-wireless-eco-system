package com.adarsh.model.trains.beans;

import com.adarsh.model.trains.service.MQTTService;
import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.Data;

import java.util.LinkedHashMap;
import java.util.List;

import static com.adarsh.model.trains.service.MQTTService.*;

@Data
public class ConfigurationDetails extends NodeConfigurations.Nodes {

    Integer totalLightPins;
    Integer totalSignal2LedPins;
    Integer totalSignal3LedPins;
    Integer totalServoTurnoutPins;
    Integer totalSnapTurnoutPins;
    String totalBoardRequired;
    LinkedHashMap<String, String> jmriAddressTurnoutServo;
    LinkedHashMap<String, String> jmriAddressTurnoutSnap;
    LinkedHashMap<String, String> jmriAddressLight;
    LinkedHashMap<String, LinkedHashMap<String, String>> jmriAddressSignal2Led;
    LinkedHashMap<String, LinkedHashMap<String, String>> jmriAddressSignal3Led;

    public ConfigurationDetails(NodeConfigurations.Nodes node, MQTTService mqttService) {
        super.setNodeId(node.getNodeId());
        super.setEnableNode(node.getEnableNode());
        super.setEnablePublishing(node.getEnablePublishing());
        super.setEnableRestApi(node.getEnableRestApi());
        super.setLightStartAddress(node.getLightStartAddress());
        super.setLightCount(node.getLightCount());
        super.setSignal2LStartAddress(node.getSignal2LStartAddress());
        super.setSignal2LCount(node.getSignal2LCount());
        super.setSignal3LStartAddress(node.getSignal3LStartAddress());
        super.setSignal3LCount(node.getSignal3LCount());
        super.setTurnoutServoStartAddress(node.getTurnoutServoStartAddress());
        super.setTurnoutServoCount(node.getTurnoutServoCount());
        super.setTurnoutSnapStartAddress(node.getTurnoutSnapStartAddress());
        super.setTurnoutSnapCount(node.getTurnoutSnapCount());
        super.setTurnoutBoardCount(node.getTurnoutBoardCount());
        super.setLightBoardCount(node.getLightBoardCount());
        super.setNodeSubscriptionTopic(node.getNodeSubscriptionTopic());
        super.setApiEndpointCacheSize(node.getApiEndpointCacheSize());
        this.setTotalLightPins(node.getLightCount());
        this.setTotalSignal2LedPins(node.getSignal2LCount() * 2);
        this.setTotalSignal3LedPins(node.getSignal3LCount() * 3);
        this.setTotalServoTurnoutPins(node.getTurnoutServoCount());
        this.setTotalSnapTurnoutPins(node.getTurnoutSnapCount() * 2);
        this.totalBoardRequiredCalculation(node);
        this.calculateJmriAddressForTurnoutServo(node, mqttService);
        this.calculateJmriAddressForTurnoutSnap(node, mqttService);
        this.calculateJmriAddressForLight(node, mqttService);
        this.calculateJmriAddressFor2LedSignal(node, mqttService);
        this.calculateJmriAddressFor3LedSignal(node, mqttService);
    }

    @JsonIgnore
    void totalBoardRequiredCalculation(NodeConfigurations.Nodes node) {
        int totalBoard = 0;
        if (node.getTurnoutServoCount() > 0) {
            int servo = node.getTurnoutServoCount();
            servo -= 1;
            totalBoard += (servo / 16) + 1;
        }
        totalBoardRequired = " Total Servo TurnoutBoard Required is " + totalBoard;
        totalBoard = 0;
        if (node.getTurnoutSnapCount() > 0) {
            int snap = node.getTurnoutSnapCount() * 2;
            snap -= 1;
            totalBoard += (snap / 16) + 1;
        }
        totalBoardRequired += ", Total Snap TurnoutBoard Required is " + totalBoard;
        int totalLights = node.getLightCount() + (node.getSignal2LCount() * 2) + (node.getSignal3LCount() * 3);
        if (totalLights > 0) {
            totalLights -= 1;
            totalBoard += (totalLights / 16) + 1;
        }
        totalBoardRequired += ", Total Light & Signal Boards Required is " + totalBoard;
    }

    @JsonIgnore
    void calculateJmriAddressForTurnoutServo(NodeConfigurations.Nodes node, MQTTService mqttService) {
        jmriAddressTurnoutServo = new LinkedHashMap<>();
        int servoNumber = 1;
        String data = "";
        for (int i = node.getTurnoutServoStartAddress() + 1; i <= node.getTurnoutServoStartAddress() + node.getTurnoutServoCount(); i++) {
            data = mqttService.nodeWiseDataGenerated(TURNOUT, node, i, TH);
            data = data + " - " + mqttService.nodeWiseDataGenerated(TURNOUT, node, i, CL);
            jmriAddressTurnoutServo.put(" Servo Number " + servoNumber, " Jmri Address " + i + ", BoardNo:PinNo:Status => " + data);
            servoNumber++;
            data = "";
        }
    }

    @JsonIgnore
    void calculateJmriAddressForTurnoutSnap(NodeConfigurations.Nodes node, MQTTService mqttService) {
        jmriAddressTurnoutSnap = new LinkedHashMap<>();
        int snapNumber = 1;
        String data = "";
        for (int i = node.getTurnoutSnapStartAddress() + 1; i <= node.getTurnoutSnapStartAddress() + node.getTurnoutSnapCount(); i++) {
            data = mqttService.nodeWiseDataGenerated(TURNOUT, node, i, TH);
            data = data + " - " + mqttService.nodeWiseDataGenerated(TURNOUT, node, i, CL);
            jmriAddressTurnoutSnap.put(" Snap Number " + snapNumber, " Jmri Address " + i + ", BoardNo:PinNo:Status => " + data);
            snapNumber++;
            data = "";
        }
    }

    @JsonIgnore
    void calculateJmriAddressForLight(NodeConfigurations.Nodes node, MQTTService mqttService) {
        jmriAddressLight = new LinkedHashMap<>();
        int lightNumber = 1;
        String data = "";
        for (int i = node.getLightStartAddress() + 1; i <= node.getLightStartAddress() + node.getLightCount(); i++) {
            data = mqttService.nodeWiseDataGenerated(LIGHT, node, i, ON);
            data = data + " - " + mqttService.nodeWiseDataGenerated(LIGHT, node, i, OFF);
            jmriAddressLight.put(" Light Number " + lightNumber, "Jmri Address " + i + ", BoardNo:PinNo:Status => " + data);
            lightNumber++;
            data = "";
        }
    }

    @JsonIgnore
    void calculateJmriAddressFor2LedSignal(NodeConfigurations.Nodes node, MQTTService mqttService) {
        jmriAddressSignal2Led = new LinkedHashMap<>();
        int signal2LedNumber = 1;
        String data = "";
        for (int i = node.getSignal2LStartAddress() + 1; i <= node.getSignal2LStartAddress() + (node.getSignal2LCount() * 2); i += 2) {
            LinkedHashMap<String, String> signal = new LinkedHashMap<>();
            data = mqttService.nodeWiseDataGenerated(SIGNAL, node, i, ON);
            data = data + " - " + mqttService.nodeWiseDataGenerated(SIGNAL, node, i, OFF);
            signal.put("RED   2Led Signal Number " + signal2LedNumber, " Jmri Address " + i + ", BoardNo:PinNo:Status => " + data);
            data = "";
            data = mqttService.nodeWiseDataGenerated(SIGNAL, node, i + 1, ON);
            data = data + " - " + mqttService.nodeWiseDataGenerated(SIGNAL, node, i + 1, OFF);
            signal.put("GREEN 2Led Signal Number " + signal2LedNumber, " Jmri Address " + (i + 1) + ", BoardNo:PinNo:Status => " + data);
            jmriAddressSignal2Led.put(signal2LedNumber + "", signal);
            signal2LedNumber++;
            data = "";
        }
    }

    @JsonIgnore
    void calculateJmriAddressFor3LedSignal(NodeConfigurations.Nodes node, MQTTService mqttService) {
        jmriAddressSignal3Led = new LinkedHashMap<>();
        int signal3LedNumber = 1;
        String data = "";
        for (int i = node.getSignal3LStartAddress() + 1; i <= node.getSignal3LStartAddress() + (node.getSignal3LCount() * 3); i += 3) {
            LinkedHashMap<String, String> signal = new LinkedHashMap<>();
            data = mqttService.nodeWiseDataGenerated(SIGNAL, node, i, ON);
            data = data + " - " + mqttService.nodeWiseDataGenerated(SIGNAL, node, i, OFF);
            signal.put("RED    3Led Signal Number " + signal3LedNumber, " Jmri Address " + i + ", BoardNo:PinNo:Status => " + data);
            data = "";
            data = mqttService.nodeWiseDataGenerated(SIGNAL, node, i + 1, ON);
            data = data + " - " + mqttService.nodeWiseDataGenerated(SIGNAL, node, i + 1, OFF);
            signal.put("GREEN  3Led Signal Number " + signal3LedNumber, " Jmri Address " + (i + 1) + ", BoardNo:PinNo:Status => " + data);
            data = "";
            data = mqttService.nodeWiseDataGenerated(SIGNAL, node, i + 2, ON);
            data = data + " - " + mqttService.nodeWiseDataGenerated(SIGNAL, node, i + 2, OFF);
            signal.put("YELLOW 3Led Signal Number " + signal3LedNumber, " Jmri Address " + (i + 2) + ", BoardNo:PinNo:Status => " + data);
            jmriAddressSignal3Led.put(signal3LedNumber + "", signal);
            signal3LedNumber++;
            data = "";
        }
    }

}
