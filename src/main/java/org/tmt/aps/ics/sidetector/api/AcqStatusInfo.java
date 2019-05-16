package org.tmt.aps.ics.sidetector.api;

public class AcqStatusInfo {

    int percentRead;
    int currentFrame;
    int bufferFlags;


    public AcqStatusInfo(int[] cppRetString) throws Exception {

        percentRead = cppRetString[0];
        currentFrame = cppRetString[1];
        bufferFlags = cppRetString[2];

    }


    public int getPercentRead() {
        return percentRead;
    }

    public int getCurrentFrame() {
        return currentFrame;
    }

    public int getBufferFlags() {
        return bufferFlags;
    }

    @Override
    public String toString() {
        return "AcqStatusInfo{" +
                "percentRead=" + percentRead +
                ", currentFrame=" + currentFrame +
                ", bufferFlags=" + bufferFlags +
                '}';
    }
}