package com.flash3388.apriltags4j;

import org.opencv.calib3d.Calib3d;
import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.MatOfDouble;
import org.opencv.core.MatOfPoint2f;
import org.opencv.core.MatOfPoint3f;
import org.opencv.core.Point;
import org.opencv.core.Scalar;
import org.opencv.imgproc.Imgproc;

public class TagPose {

    public final Mat R;
    public final Mat t;
    public final double error;

    public TagPose(Mat R, Mat t, double error) {
        this.R = R;
        this.t = t;
        this.error = error;
    }

    public void drawBoundingBox(Mat img,
                               Mat intrinsicMatrix,
                               MatOfDouble distortionsCuff,
                               double tagSize,
                               Scalar color) {
        Mat opoints = new Mat(8, 1, CvType.CV_32FC3);
        opoints.put(0, 0,
                -1, -1, 0,
                1, -1, 0,
                1, 1, 0,
                -1, 1, 0,
                -1, -1, -2,
                1, -1, -2,
                1, 1, -2,
                -1, 1, -2);
        MatOfPoint3f objectPoints = new MatOfPoint3f();
        Core.multiply(opoints, Scalar.all(0.5 * tagSize), objectPoints);

        MatOfPoint2f imagePoints = new MatOfPoint2f();
        Calib3d.projectPoints(objectPoints, R, t, intrinsicMatrix, distortionsCuff, imagePoints);
        drawBoxes(img, imagePoints.toArray(), color);
    }

    private static void drawBoxes(Mat img, Point[] points, Scalar color) {
        assert points.length == 8;

        Imgproc.line(img, points[0], points[1], color, 1);
        Imgproc.line(img, points[1], points[2], color, 1);
        Imgproc.line(img, points[2], points[3], color, 1);
        Imgproc.line(img, points[3], points[0], color, 1);

        Imgproc.line(img, points[4], points[5], color, 1);
        Imgproc.line(img, points[5], points[6], color, 1);
        Imgproc.line(img, points[6], points[7], color, 1);
        Imgproc.line(img, points[7], points[4], color, 1);

        Imgproc.line(img, points[0], points[4], color, 1);
        Imgproc.line(img, points[1], points[5], color, 1);
        Imgproc.line(img, points[2], points[6], color, 1);
        Imgproc.line(img, points[3], points[7], color, 1);
    }
}
