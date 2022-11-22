package com.flash3388.apriltags4j;

public class AprilTagsFamilyJNI {

    public static native long create(FamilyType type);
    public static native void destroy(FamilyType type, long ptr);
}
