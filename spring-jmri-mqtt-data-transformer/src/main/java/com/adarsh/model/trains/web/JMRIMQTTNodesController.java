package com.adarsh.model.trains.web;

import com.adarsh.model.trains.beans.ConfigurationDetails;
import com.adarsh.model.trains.beans.RequestBean;
import com.adarsh.model.trains.service.ConfigurationService;
import com.adarsh.model.trains.service.MQTTService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.List;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */

@Slf4j
@RestController
public class JMRIMQTTNodesController {

    private static final String PROCESSED_FAILED = "PROCESSED-FAILED";
    private static final String PROCESSED_SUCCESS = "PROCESSED-SUCCESS";

    @Autowired
    MQTTService mqttService;

    @Autowired
    ConfigurationService configurationService;

    @GetMapping("/node/{nodeId}")
    public String getNodeData(@PathVariable("nodeId") String nodeId) throws Exception {
        return this.mqttService.getData(nodeId);
    }

    @GetMapping("/description/node")
    public List<ConfigurationDetails> getNodesConfigurationData() throws Exception {
        return this.configurationService.getNodeConfigurationDetails();
    }

    @GetMapping("/description/node/{nodeId}")
    public List<ConfigurationDetails> getNodeConfigurationData(@PathVariable("nodeId") String nodeId) throws Exception {
        return this.configurationService.getNodeConfigurationDetails(nodeId);
    }

    @PostMapping("/node/{nodeId}")
    public String postNodeData(@PathVariable("nodeId") String nodeId, @Valid @RequestBody RequestBean data) throws Exception {
        try {
            this.mqttService.publish(data.getTopic(), data.getData(), 1, false);
        } catch (Exception e) {
            log.error("Exception e={}", e.getMessage());
            return PROCESSED_FAILED;
        }
        return PROCESSED_SUCCESS;
    }
}
