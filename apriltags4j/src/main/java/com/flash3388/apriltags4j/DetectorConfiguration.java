package com.flash3388.apriltags4j;

public class DetectorConfiguration {

    public int nthreads;
    public float quadDecimate;
    public float quadSigma;
    public boolean refineEdges;
    public double decodeSharpening;
    public boolean debug;
    public QuadThreshParams quadThreshParams;

    public static class QuadThreshParams {

        public int minClusterPixels;
        public int maxNmaxima;
        public float criticalRad;
        public float cosCriticalRad;
        public float maxLineFitMse;
        public int minWhiteBlackDiff;
        public int deglitch;
    }
}
