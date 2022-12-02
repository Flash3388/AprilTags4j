package com.flash3388.apriltags4j;

import org.opencv.core.Mat;

public class TagPose {

    public final Mat R;
    public final Mat t;
    public final double error;

    public TagPose(Mat R, Mat t, double error) {
        this.R = R;
        this.t = t;
        this.error = error;
    }
}
