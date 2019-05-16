package org.tmt.aps.ics.sidetector.api;

import java.util.ArrayList;
import java.util.List;


public class ImageSizeInfo {

    int serLen;
    int parLen;
    int is16;
    int nSerCCD;
    int nParCCD;
    int nSerSect;
    int nParSect;


    public ImageSizeInfo(int[] cppReturnArray) {

        serLen = cppReturnArray[0];
        parLen = cppReturnArray[1];
        is16 = cppReturnArray[2];
        nSerCCD = cppReturnArray[3];
        nParCCD = cppReturnArray[4];
        nSerSect = cppReturnArray[5];
        nParSect = cppReturnArray[6];

    }


    public int getSerLen() {
        return serLen;
    }

    public int getParLen() {
        return parLen;
    }

    public int getIs16() {
        return is16;
    }

    public int getnSerCCD() {
        return nSerCCD;
    }

    public int getnParCCD() {
        return nParCCD;
    }

    public int getnSerSect() {
        return nSerSect;
    }

    public int getnParSect() {
        return nParSect;
    }


    @Override
    public String toString() {
        return "ImageSizeInfo{" +
                "serLen=" + serLen +
                ", parLen=" + parLen +
                ", is16=" + is16 +
                ", nSerCCD=" + nSerCCD +
                ", nParCCD=" + nParCCD +
                ", nSerSect=" + nSerSect +
                ", nParSect=" + nParSect +
                '}';
    }

}