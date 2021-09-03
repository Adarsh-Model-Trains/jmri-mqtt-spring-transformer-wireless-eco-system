package com.adarsh.model.trains.service;

import com.adarsh.model.trains.beans.ConfigurationDetails;
import com.adarsh.model.trains.beans.NodeConfigurations;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
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

    public List<ConfigurationDetails> getNodeConfigurationDetails(String nodeId) {
        Optional<NodeConfigurations.Nodes> nodesOptional =
                nodeConfigurations.getNodes().stream().filter(e -> e.getNodeId().equalsIgnoreCase(nodeId)).findFirst();
        return Arrays.asList(new ConfigurationDetails(nodesOptional.get(), mqttService));
    }
}
