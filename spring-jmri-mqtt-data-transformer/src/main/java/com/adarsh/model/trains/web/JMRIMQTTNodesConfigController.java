package com.adarsh.model.trains.web;

import com.adarsh.model.trains.beans.ConfigurationDetails;
import com.adarsh.model.trains.exception.InvalidNodeIdException;
import com.adarsh.model.trains.service.ConfigurationService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

import static com.adarsh.model.trains.service.MQTTService.DEFAULT_BLOCK_RESULT;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */

@Slf4j
@RestController
public class JMRIMQTTNodesConfigController {

    @Autowired
    ConfigurationService configurationService;

    @GetMapping("/test/node/config/{nodeId}")
    public String testNodeConfiguration(@PathVariable("nodeId") String nodeId) throws Exception {
        log.debug("JMRIMQTTNodesConfigController.testNodeConfiguration() {}", nodeId);
        configurationService.testNodeConfiguration(nodeId);
        return "STARTED THE CONFIGURATION TESTING FOR NODE " + nodeId;
    }

    @GetMapping("/description/node")
    public List<ConfigurationDetails> getNodesConfigurationData() throws Exception {
        log.debug("JMRIMQTTNodesConfigController.getNodesConfigurationData() ");
        return this.configurationService.getNodeConfigurationDetails();
    }

    @GetMapping("/description/node/{nodeId}")
    public List<ConfigurationDetails> getNodeConfigurationData(@PathVariable("nodeId") String nodeId) throws Exception {
        log.debug("JMRIMQTTNodesConfigController.getNodeConfigurationData() {}", nodeId);
        return this.configurationService.getNodeConfigurationDetails(nodeId);
    }
}
