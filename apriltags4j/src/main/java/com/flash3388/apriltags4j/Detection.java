package com.flash3388.apriltags4j;

public class Detection {

    private final long ptr;

    public final int id;
    public final int hamming;
    public final float decisionMargin;
    public final double centerX;
    public final double centerY;
    public final double[][] corners;

    public Detection(long ptr, int id, int hamming, float decisionMargin,
                     double centerX, double centerY,
                     double[][] corners) {
        this.ptr = ptr;
        this.id = id;
        this.hamming = hamming;
        this.decisionMargin = decisionMargin;
        this.centerX = centerX;
        this.centerY = centerY;
        this.corners = corners;
    }

    public TagPose estimatePose(DetectionInfo info) {
        return AprilTagsDetectionsJNI.estimatePose(ptr, info);
    }
}
