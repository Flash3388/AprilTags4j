package com.flash3388.apriltags4j;

import org.opencv.core.Mat;

public class DetectionInfo {

    public double tagSizeMeters;
    public double focalLengthX;
    public double focalLengthY;
    public double focalCenterX;
    public double focalCenterY;

    public DetectionInfo(double tagSizeMeters,
                         double focalLengthX, double focalLengthY,
                         double focalCenterX, double focalCenterY) {
        this.tagSizeMeters = tagSizeMeters;
        this.focalLengthX = focalLengthX;
        this.focalLengthY = focalLengthY;
        this.focalCenterX = focalCenterX;
        this.focalCenterY = focalCenterY;
    }

    public DetectionInfo(double tagSizeMeters, Mat cameraMatrix) {
        this.tagSizeMeters = tagSizeMeters;
        fillFromCameraMatrix(cameraMatrix);
    }

    public DetectionInfo() {
    }

    public void fillFromCameraMatrix(Mat mat) {
        assert mat.rows() == 3;
        assert mat.cols() == 3;
        assert mat.channels() == 1;

        focalCenterX = mat.get(0, 2)[0];
        focalCenterY = mat.get(1, 2)[0];
        focalLengthX = mat.get(0, 0)[0];
        focalLengthY = mat.get(1, 1)[0];
    }
}
