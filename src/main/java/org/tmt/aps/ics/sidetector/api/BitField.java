package org.tmt.aps.ics.sidetector.api;

import java.util.ArrayList;
import java.util.List;

public class BitField {

    String displayName;
    int bitPos;


    public BitField(String displayName, int bitPos) {

        this.displayName = displayName;
        this.bitPos = bitPos;

    }

    public String getDisplayName() {
        return displayName;
    }

    public int getBitPos() {
        return bitPos;
    }


    public static List<BitField> generateBitFieldList(String displayNames, String bitMaskStr) {

        String[] displayNameArray = displayNames.split("\\s*,\\s*");
        int bitMask = new Integer(bitMaskStr);

        ArrayList<BitField> bitFieldList = new ArrayList<BitField>();

        int pos = 0;
        for (String displayName : displayNameArray) {

            while ((bitMask & 1) == 0) {
                bitMask = bitMask>>>1;  // shift to right
                pos++; // increment
            }
            bitFieldList.add(new BitField(displayName, pos));
            bitMask = bitMask>>>1;
            pos++;
        }

        return bitFieldList;
    }

    public String toString() {
        return displayName + "," + bitPos;
    }

}