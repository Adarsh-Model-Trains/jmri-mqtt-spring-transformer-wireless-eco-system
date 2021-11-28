package com.adarsh.model.trains.handler;

import com.adarsh.model.trains.exception.InvalidNodeIdException;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.HashMap;
import java.util.Map;

@Slf4j
@ControllerAdvice
public class TransformerExceptionHandler {

    @ExceptionHandler(InvalidNodeIdException.class)
    public @ResponseBody
    Map<String, String> respondInvalidNodeIdException(InvalidNodeIdException invalidNodeIdException) {
        log.error("TransformerExceptionHandler::respondInvalidNodeIdException() {}", invalidNodeIdException.getMessage());
        return new HashMap<String, String>() {
            {
                put("message", invalidNodeIdException.getMessage());
            }
        };
    }

    @ExceptionHandler(Exception.class)
    public @ResponseBody
    Map<String, String> respondException(Exception exception) {
        log.error("TransformerExceptionHandler::respondException() {}", exception.getMessage());
        return new HashMap<String, String>() {
            {
                put("message", exception.getMessage());
            }
        };
    }
}
