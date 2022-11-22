package com.flash3388.apriltags4j;

public class JNIException extends RuntimeException {

    public JNIException(int errorCode) {
        super(String.valueOf(errorCode));
    }
}
