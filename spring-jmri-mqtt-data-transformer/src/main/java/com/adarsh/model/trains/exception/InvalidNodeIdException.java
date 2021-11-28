package com.adarsh.model.trains.exception;

public class InvalidNodeIdException extends Exception {
    String message;

    public InvalidNodeIdException() {
    }

    public InvalidNodeIdException(String message) {
        super(message);
        this.message = message;
    }

    public InvalidNodeIdException(String message, Throwable cause) {
        super(message, cause);
        this.message = message;
    }
}
