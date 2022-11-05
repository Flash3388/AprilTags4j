package com.flash3388.apriltags4j;

public class AprilTags {
    
    public static native long createDetector();
    public static native void destroyDetector(long detectorPtr);
    public static native void detectorAddFamilyBits(long detectorPtr, long familyPtr, int bitsCorrected);
    public static native void detectorAddFamily(long detectorPtr, long familyPtr);
    public static native void detectorRemoveFamily(long detectorPtr, long familyPtr);
    public static native void detectorClearFamilies(long detectorPtr);
    public static native AprilTagDetection[] detectorDetect(long detectorPtr, int imageWidth, int imageHeight, int imageStride, byte[] imageBuffer);
    public static native void detectionDestroy(long detection_t_ptr);
    public static native void detectionDestroyZarray_t(long zarray_t_detection_ptr);
    public static native long apriltagToImage(long apriltagFamily_t_ptr, int idx);
}
