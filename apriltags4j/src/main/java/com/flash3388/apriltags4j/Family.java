package com.flash3388.apriltags4j;

public class Family implements AutoCloseable {

    private final FamilyType type;
    private final long ptr;

    public Family(FamilyType type) {
        this.type = type;
        this.ptr = AprilTagsFamilyJNI.create(type);
    }

    long nativePtr() {
        return ptr;
    }

    FamilyType type() {
        return type;
    }

    @Override
    public void close() throws Exception {
        AprilTagsFamilyJNI.destroy(type, ptr);
    }
}
