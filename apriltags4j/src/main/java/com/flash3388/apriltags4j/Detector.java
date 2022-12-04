package com.flash3388.apriltags4j;

import org.opencv.core.Mat;

import java.util.LinkedList;
import java.util.List;

public class Detector implements AutoCloseable {
    
    private final long ptr;
    private final List<Family> addedFamilies;

    public Detector() {
        this.ptr = AprilTagsDetectorJNI.createDetector();
        this.addedFamilies = new LinkedList<>();
    }

    public DetectorConfiguration getConfiguration() {
        return AprilTagsDetectorJNI.getConfiguration(ptr);
    }

    public void setConfiguration(DetectorConfiguration configuration) {
        AprilTagsDetectorJNI.setConfiguration(ptr, configuration);
    }

    public void addFamily(Family family) {
        AprilTagsDetectorJNI.addFamily(ptr, family.nativePtr());
        addedFamilies.add(family);
    }

    public void removeFamily(Family family) {
        AprilTagsDetectorJNI.removeFamily(ptr, family.nativePtr());
        addedFamilies.remove(family);
    }

    public void clearFamilies() {
        AprilTagsDetectorJNI.clearFamilies(ptr);
        addedFamilies.clear();
    }

    public Detections detect(Mat mat) {
        long dPtr = AprilTagsDetectorJNI.detect(ptr, mat.nativeObj);
        return new Detections(this::findFamily, dPtr);
    }

    @Override
    public void close() {
        AprilTagsDetectorJNI.destroyDetector(ptr);
    }

    private FamilyType findFamily(long familyPtr) {
        for (Family family : addedFamilies) {
            if (family.nativePtr() == familyPtr) {
                return family.type();
            }
        }

        throw new IllegalArgumentException("No such family in detector");
    }
}
