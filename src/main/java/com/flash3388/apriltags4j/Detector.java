package com.flash3388.apriltags4j;

import org.opencv.core.Mat;

public class Detector implements AutoCloseable {
    
    private final long ptr;

    public Detector() {
        this.ptr = AprilTagsDetectorJNI.createDetector();
    }

    public void addFamily(Family family) {
        AprilTagsDetectorJNI.addFamily(ptr, family.nativePtr());
    }

    public Detections detect(Mat mat) {
        long dPtr = AprilTagsDetectorJNI.detect(ptr, mat.nativeObj);
        return new Detections(dPtr);
    }

    @Override
    public void close() {
        AprilTagsDetectorJNI.destroyDetector(ptr);
    }
}
