package com.adarsh.model.trains.beans;

import lombok.Data;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;
import org.springframework.validation.annotation.Validated;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import java.util.List;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */
@Data
@Component
@Validated
@ConfigurationProperties("node.configurations")
public class NodeConfigurations {

    public List<Nodes> nodes;
    @NotNull(message = "lightStartingAddress is mandatory properties in configuration ")
    Integer lightStartingAddress = 0;
    @NotNull(message = "turnoutStartingAddress is mandatory properties in configuration ")
    Integer turnoutStartingAddress = 0;
    @NotNull(message = "signal2LStartingAddress is mandatory properties in configuration ")
    Integer signal2LStartingAddress = 0;
    @NotNull(message = "signal3LStartingAddress is mandatory properties in configuration ")
    Integer signal3LStartingAddress = 0;
    @NotNull(message = "signalCacheClearingTime is mandatory properties in configuration ")
    Integer signalCacheClearingTime = 0;


    @Data
    public static class Nodes {
        String nodeId;
        Boolean enableNode;
        Boolean enablePublishing;
        Boolean enableRestApi;
        Integer lightStartAddress;
        Integer lightCount;
        Integer turnoutStartAddress;
        Integer turnoutCount;
        Integer signal2LStartAddress;
        Integer signal2LCount;
        Integer signal3LStartAddress;
        Integer signal3LCount;
        Integer turnoutBoardCount;
        Integer lightBoardCount;
        String nodeSubscriptionTopic;
        Integer apiEndpointCacheSize;
    }
}
