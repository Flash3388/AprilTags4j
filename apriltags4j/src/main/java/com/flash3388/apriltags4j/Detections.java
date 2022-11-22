package com.flash3388.apriltags4j;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class Detections implements AutoCloseable, Iterator<Detection> {

    private final long ptr;
    private int index;
    private final int size;

    Detections(long ptr) {
        this.ptr = ptr;
        this.index = -1;
        this.size = AprilTagsDetectionsJNI.size(ptr);
    }

    @Override
    public boolean hasNext() {
        return index < size - 1;
    }

    @Override
    public Detection next() {
        index++;
        if (index >= size) {
            throw new NoSuchElementException();
        }

        return AprilTagsDetectionsJNI.get(ptr, index);
    }

    @Override
    public void close() throws Exception {
        AprilTagsDetectionsJNI.destroy(ptr);
    }
}
