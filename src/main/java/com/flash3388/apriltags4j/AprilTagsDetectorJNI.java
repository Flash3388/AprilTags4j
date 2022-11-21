package com.flash3388.apriltags4j;

public class AprilTagsDetectorJNI {

    public static native long createDetector();
    public static native void destroyDetector(long ptr);
    public static native void addFamily(long ptr, long familyPtr);
    public static native void removeFamily(long ptr, long familyPtr);
    public static native void clearFamilies(long ptr);
    public static native long detect(long ptr, long matPtr);
}
