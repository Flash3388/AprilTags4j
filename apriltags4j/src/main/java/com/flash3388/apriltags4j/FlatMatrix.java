package com.flash3388.apriltags4j;

public class FlatMatrix {

    public double[] data;
    public int rowCount;
    public int colCount;

    public FlatMatrix(double[] data, int rowCount, int colCount) {
        this.data = data;
        this.rowCount = rowCount;
        this.colCount = colCount;
    }
}
