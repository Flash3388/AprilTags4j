package com.flash3388.apriltags4j;

public class Detector implements AutoCloseable {
    
    private final long ptr;

    public Detector() {
        this.ptr = AprilTags.createDetector();
    }

    @Override
    public void close() {
        AprilTags.destroyDetector(ptr);
    }
}
