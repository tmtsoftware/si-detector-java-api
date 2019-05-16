package org.tmt.aps.ics.sidetector.api;

import java.util.ArrayList;
import java.util.List;
import java.io.*;

public class StatusItemInfo {

    String displayStr;
    String valStr;
    String unitStr;
    int unitType;
    String stepStr;
    boolean writeable;

    List<BitField> bitFieldList;

    public StatusItemInfo(String displayStr, String[] cppRetString) throws Exception {

        valStr =  cppRetString[1];
        unitStr = cppRetString[2];
        stepStr = cppRetString[3];
        unitType = new Integer(cppRetString[4]);


        this.displayStr = displayStr;
    }


    public String getValStr() {
        return valStr;
    }

    public String getUnitStr() {
        return unitStr;
    }

    public int getUnitType() {
        return unitType;
    }

    public String getStepStr() {
        return stepStr;
    }

    public String getDisplayStr() {
        return displayStr;
    }

    public boolean isWriteable() {
        return writeable;
    }

    public void setWriteable(boolean writeable) {
        this.writeable = writeable;
    }

    public List<BitField> getBitFieldList() {
        return bitFieldList;
    }

    public void setBitFieldList(List<BitField> bitFieldList) {
        this.bitFieldList = bitFieldList;
    }

    public String toString() {

        StringBuffer buf = new StringBuffer();
        buf.append("\ndisplayStr = " + displayStr +
                ", valStr = " + valStr +
                ", unitStr = " + unitStr +
                ", unitType = " + unitType +
                ", stepStr = " + stepStr);
        if (bitFieldList != null) {
            for (BitField bitField : bitFieldList) {
                buf.append("\n bitfield = " + bitField);
            }
        }
        return buf.toString();
    }

}