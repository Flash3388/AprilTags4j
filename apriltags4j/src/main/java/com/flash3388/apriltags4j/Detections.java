package com.flash3388.apriltags4j;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.function.Function;

public class Detections implements AutoCloseable, Iterator<Detection> {

    private final Function<Long, FamilyType> familyFinder;
    private final long ptr;
    private int index;
    private final int size;

    Detections(Function<Long, FamilyType> familyFinder, long ptr) {
        this.familyFinder = familyFinder;
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

        Detection detection = AprilTagsDetectionsJNI.get(ptr, index);
        detection.familyType = familyFinder.apply(detection.familyPtr);
        return detection;
    }

    @Override
    public void close() throws Exception {
        AprilTagsDetectionsJNI.destroy(ptr);
    }
}
