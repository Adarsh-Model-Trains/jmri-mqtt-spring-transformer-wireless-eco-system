package com.adarsh.model.trains.web;

import com.adarsh.model.trains.beans.RequestBean;
import com.adarsh.model.trains.service.MQTTService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import javax.servlet.http.HttpServletResponse;
import javax.validation.Valid;
import static com.adarsh.model.trains.service.MQTTService.DEFAULT_BLOCK_RESULT;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */

@Slf4j
@RestController
public class JMRIMQTTDataController {

    private static final String PROCESSED_FAILED = "PROCESSED-FAILED";
    private static final String PROCESSED_SUCCESS = "PROCESSED-SUCCESS";

    @Autowired
    MQTTService mqttService;

    @GetMapping("/node/{nodeId}")
    public String getNodeData(@PathVariable("nodeId") String nodeId, HttpServletResponse response) throws Exception {
        response.setHeader("Content-Length", "16");
        if (MQTTService.activeNodeCache.containsKey(nodeId)) {
            return MQTTService.getData(nodeId);
        } else {
            return DEFAULT_BLOCK_RESULT;
        }
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