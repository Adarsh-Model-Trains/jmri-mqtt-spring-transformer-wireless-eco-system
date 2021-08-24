package com.adarsh.model.trains;

import lombok.extern.slf4j.Slf4j;
import org.springframework.boot.Banner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.core.env.Environment;
import org.springframework.integration.annotation.IntegrationComponentScan;
import org.springframework.util.ResourceUtils;

import java.io.IOException;
import java.io.PrintStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */

@Slf4j
@IntegrationComponentScan
@SpringBootApplication
public class MqttJmriTransformerApplication {

    public static void main(String[] args) {
        SpringApplication application = new SpringApplication(MqttJmriTransformerApplication.class);
        application.setBanner(new Banner() {
            @Override
            public void printBanner(Environment environment, Class<?> sourceClass, PrintStream out) {
                String banner = readBanner();
                out.print(banner);
            }
        });
        application.run(args);
    }

    private static String readBanner() {
        try {
            String banner = new String(Files.readAllBytes(
                    Paths.get(ResourceUtils.getFile("classpath:amt-banner.txt").toURI())), StandardCharsets.UTF_8);
            return banner;
        } catch (IOException ex) {
            return "  Developed by: Adarsh kumar\n" +
                    " For Support: adarshmodeltrains@gmail.com\n\n\n";
        }
    }
}
