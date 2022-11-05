package com.flash3388.apriltags4j;

public class AprilTagDetection {
    public long familyPtr;
    public int id;
    public int hamming;
    public float decisionMargin;
    public double centerX;
    public double centerY;

    public AprilTagDetection
    (long familyPtr,int id, int hamming, float decisionMargin, double centerX, double centerY) {
        this.familyPtr = familyPtr;
        this.id = id;
        this.hamming = hamming;
        this.decisionMargin = decisionMargin;
        this.centerX = centerX;
        this.centerY = centerY;
    }
}