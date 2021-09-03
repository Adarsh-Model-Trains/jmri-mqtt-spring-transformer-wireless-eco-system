package com.adarsh.model.trains;

import com.adarsh.model.trains.beans.NodeConfigurations;

import static com.adarsh.model.trains.service.MQTTService.*;


public class ApplicationTest {


    private String findBoardPin(NodeConfigurations.Nodes node, Integer pinNo, String state) {
        String data = "";
        int pin = pinNo - 1;
        int board = (pin / 16);
        if (board <= node.getTurnoutBoardCount() + node.getLightBoardCount()
                && pin <= (node.getTurnoutBoardCount() + node.getLightBoardCount()) * 16) {
            int totalPins = (board * 16);
            pin = (pin - totalPins);
            pin = (pin == -1) ? 0 : pin;
            data = (board < 10 ? ZERO + board : board) + COLLEN + (pin < 10 ? ZERO + pin : pin) + COLLEN + state;
        }
        return data;
    }


    public String nodeWiseDataGenerated(String type, NodeConfigurations.Nodes node, Integer jmriId, String state) {
        if (type.equals(TURNOUT)) {
            jmriId = (jmriId - node.getTurnoutSnapStartAddress());
            jmriId = (jmriId * 2);
            if (state.equals(TH)) {
                jmriId = jmriId - 1;
            }
            //  find board and pin for the turnout based on configuration
            return this.findBoardPin(node, jmriId, state);
        } else if (type.equals(SIGNAL)) {
            if (jmriId >= node.getSignal3LStartAddress()) {
                jmriId = (jmriId - node.getSignal3LStartAddress()) + (node.getTurnoutBoardCount() * 16);
            } else {
                jmriId = (jmriId - node.getSignal2LStartAddress()) + (node.getTurnoutBoardCount() * 16);
            }
            //  find board and pin for the signal based on configuration
            return this.findBoardPin(node, jmriId, state);
        } else if (type.equals(LIGHT)) {
            jmriId = (jmriId - node.getLightStartAddress())
                    + (node.getTurnoutBoardCount() * 16)
                    + node.getSignal2LCount() + node.getSignal3LCount();
            //  find board and pin for the light based on configuration
            return this.findBoardPin(node, jmriId, state);
        }
        return null;
    }

    public static void main1(String[] args) throws Exception {
        ApplicationTest applicationTest = new ApplicationTest();
        NodeConfigurations.Nodes node = new NodeConfigurations.Nodes();
        node.setTurnoutBoardCount(2);
        node.setTurnoutSnapCount((node.getTurnoutBoardCount() * 16) / 2);

        node.setLightBoardCount(5);
        node.setSignal2LCount(5);
        node.setSignal3LCount(7);
        node.setLightCount((node.getLightBoardCount() * 16) - (node.getSignal3LCount() + node.getSignal2LCount()));
        node.setLightStartAddress(10000);
        node.setSignal2LStartAddress(20000);
        node.setSignal3LStartAddress(30000);
        node.setTurnoutSnapStartAddress(40000);

        int pins = (node.getTurnoutBoardCount() + node.getLightBoardCount()) * 16;
        int totalTurnoutsLimit = node.getTurnoutSnapCount();
        int total2LSignalLimit = node.getSignal2LCount() + totalTurnoutsLimit;
        int total3LSignalLimit = total2LSignalLimit + node.getSignal3LCount();
        int totalLightLimit = total3LSignalLimit + node.getLightCount();
        for (int i = 1; i <= pins; i++) {
            if (i <= totalTurnoutsLimit) {
                System.out.println("TURNOUT " + applicationTest.nodeWiseDataGenerated(TURNOUT, node, i + node.getTurnoutSnapStartAddress(), TH));
                System.out.println("TURNOUT " + applicationTest.nodeWiseDataGenerated(TURNOUT, node, i + node.getTurnoutSnapStartAddress(), CL));
            } else if ((i <= total2LSignalLimit)) {
                System.out.println("2L SIGNAL " + applicationTest.nodeWiseDataGenerated(SIGNAL, node, (i + node.getSignal2LStartAddress() - node.getTurnoutSnapCount()), ON));
                System.out.println("2L SIGNAL " + applicationTest.nodeWiseDataGenerated(SIGNAL, node, (i + node.getSignal2LStartAddress() - node.getTurnoutSnapCount()), OFF));
            } else if ((i <= total3LSignalLimit)) {
                System.out.println("3L SIGNAL " + applicationTest.nodeWiseDataGenerated(SIGNAL, node, (i + node.getSignal3LStartAddress() - node.getTurnoutSnapCount()), ON));
                System.out.println("3L SIGNAL " + applicationTest.nodeWiseDataGenerated(SIGNAL, node, (i + node.getSignal3LStartAddress() - node.getTurnoutSnapCount()), OFF));
            } else if (i <= totalLightLimit) {
                if (i == total3LSignalLimit + 1) {
                    i = (totalTurnoutsLimit * 2) + total3LSignalLimit + 1;
                }
                System.out.println("LIGHT " + applicationTest.nodeWiseDataGenerated(LIGHT, node, ((i - ((totalTurnoutsLimit * 2) + total3LSignalLimit))) + node.getLightStartAddress(), ON));
                System.out.println("LIGHT " + applicationTest.nodeWiseDataGenerated(LIGHT, node, ((i - ((totalTurnoutsLimit * 2) + total3LSignalLimit))) + node.getLightStartAddress(), OFF));
            }
        }
    }

    public static void boardAndPinCal() {
        for (int i = 0; i < (16 * 64); i++) {
            if (i > 0) {
                int totalServoTurnoutPins = i;
                System.out.print("total pins " + totalServoTurnoutPins);
                totalServoTurnoutPins -= 1;
                totalServoTurnoutPins = (totalServoTurnoutPins / 16) + 1;
                System.out.print(" total boards " + totalServoTurnoutPins);
                totalServoTurnoutPins = totalServoTurnoutPins * 16;
                System.out.print(" total pins " + totalServoTurnoutPins);
                System.out.println();
            }
        }
    }

    public static void main(String[] args) {
        for (int i = 0; i < (16 * 64); i++) {
            if (i > 0) {

            }
        }
    }
}

