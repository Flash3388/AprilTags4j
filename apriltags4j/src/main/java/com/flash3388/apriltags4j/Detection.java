package com.flash3388.apriltags4j;

public class Detection {

    private final long ptr;

    /**
     * The decoded ID of the tag
     */
    public final int id;
    /**
     * How many error bits were corrected? Note: accepting large numbers of
     * corrected errors leads to greatly increased false positive rates.
     * NOTE: As of this implementation, the detector cannot detect tags with
     * a hamming distance greater than 2.
     */
    public final int hamming;
    /**
     * A measure of the quality of the binary decoding process: the
     * average difference between the intensity of a data bit versus
     * the decision threshold. Higher numbers roughly indicate better
     * decodes. This is a reasonable measure of detection accuracy
     * only for very small tags-- not effective for larger tags (where
     * we could have sampled anywhere within a bit cell and still
     * gotten a good detection.)
     */
    public final float decisionMargin;
    /**
     * X Coordinate of the center of the detection in image pixel coordinates.
     */
    public final double centerX;
    /**
     * Y Coordinate of the center of the detection in image pixel coordinates.
     */
    public final double centerY;
    /**
     * The corners of the tag in image pixel coordinates. These always
     * wrap counter-clock wise around the tag.
     */
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
