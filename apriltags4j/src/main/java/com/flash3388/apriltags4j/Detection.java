package com.flash3388.apriltags4j;

public class Detection {

    private final long ptr;

    public final int id;
    public final int hamming;
    public final float decisionMargin;
    public final double centerX;
    public final double centerY;
    public final double[][] corners;

    final long familyPtr;
    FamilyType familyType = null;

    public Detection(long ptr, int id, int hamming, float decisionMargin,
                     double centerX, double centerY,
                     double[][] corners, long familyPtr) {
        this.ptr = ptr;
        this.id = id;
        this.hamming = hamming;
        this.decisionMargin = decisionMargin;
        this.centerX = centerX;
        this.centerY = centerY;
        this.corners = corners;
        this.familyPtr = familyPtr;
    }

    public FamilyType getFamilyType() {
        if (familyType == null) {
            throw new IllegalStateException("family not found");
        }

        return familyType;
    }

    public TagPose estimatePose(DetectionInfo info) {
        return AprilTagsDetectionsJNI.estimatePose(ptr, info);
    }
}
