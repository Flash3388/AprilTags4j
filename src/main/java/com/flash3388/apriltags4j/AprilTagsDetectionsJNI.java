package com.flash3388.apriltags4j;

public class AprilTagsDetectionsJNI {

    public static native int size(long ptr);
    public static native Detection get(long ptr, int index);
    public static native void destroy(long ptr);
}
