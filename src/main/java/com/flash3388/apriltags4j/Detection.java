package com.flash3388.apriltags4j;

public class Detection {

    public final int id;
    public final int hamming;
    public final float decisionMargin;
    public final double centerX;
    public final double centerY;

    public Detection(int id, int hamming, float decisionMargin, double centerX, double centerY) {
        this.id = id;
        this.hamming = hamming;
        this.decisionMargin = decisionMargin;
        this.centerX = centerX;
        this.centerY = centerY;
    };
}
