package com.flash3388.apriltags4j;

public class DetectorConfiguration {

    /**
     * How many threads should be used?
     */
    public int nthreads;
    /**
     * detection of quads can be done on a lower-resolution image,
     * improving speed at a cost of pose accuracy and a slight
     * decrease in detection rate. Decoding the binary payload is
     * still done at full resolution. .
     */
    public float quadDecimate;
    /**
     * What Gaussian blur should be applied to the segmented image
     * (used for quad detection?)  Parameter is the standard deviation
     * in pixels.  Very noisy images benefit from non-zero values
     * (e.g. 0.8).
     */
    public float quadSigma;
    /**
     * When true, the edges of the each quad are adjusted to "snap
     * to" strong gradients nearby. This is useful when decimation is
     * employed, as it can increase the quality of the initial quad
     * estimate substantially. Generally recommended to be on (true).
     *     //
     * Very computationally inexpensive. Option is ignored if
     * quad_decimate = 1.
     */
    public boolean refineEdges;
    /**
     * How much sharpening should be done to decoded images? This
     * can help decode small tags but may or may not help in odd
     * lighting conditions or low light conditions.
     *     //
     * The default value is 0.25.
     */
    public double decodeSharpening;
    /**
     * When true, write a variety of debugging images to the
     * current working directory at various stages through the
     * detection process. (Somewhat slow).
     */
    public boolean debug;
    public QuadThreshParams quadThreshParams;

    public static class QuadThreshParams {

        /**
         * reject quads containing too few pixels
         */
        public int minClusterPixels;
        /**
         * how many corner candidates to consider when segmenting a group
         * of pixels into a quad.
         */
        public int maxNmaxima;
        /**
         * Reject quads where pairs of edges have angles that are close to
         * straight or close to 180 degrees. Zero means that no quads are
         * rejected. (In radians).
         */
        public float criticalRad;
        public float cosCriticalRad;
        /**
         * When fitting lines to the contours, what is the maximum mean
         * squared error allowed?  This is useful in rejecting contours
         * that are far from being quad shaped; rejecting these quads "early"
         * saves expensive decoding processing.
         */
        public float maxLineFitMse;
        /**
         * When we build our model of black & white pixels, we add an
         * extra check that the white model must be (overall) brighter
         * than the black model.  How much brighter? (in pixel values,
         * [0,255]). .
         */
        public int minWhiteBlackDiff;
        /**
         * should the thresholded image be deglitched? Only useful for
         * very noisy images
         */
        public int deglitch;
    }
}
