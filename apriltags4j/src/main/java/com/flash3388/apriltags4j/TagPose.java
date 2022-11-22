package com.flash3388.apriltags4j;

public class TagPose {

    public final FlatMatrix orientation;
    public final FlatMatrix position;
    public final double error;

    public TagPose(FlatMatrix orientation, FlatMatrix position, double error) {
        this.orientation = orientation;
        this.position = position;
        this.error = error;
    }
}
