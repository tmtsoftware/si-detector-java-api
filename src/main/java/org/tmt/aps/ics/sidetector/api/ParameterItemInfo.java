package org.tmt.aps.ics.sidetector.api;

import java.util.ArrayList;
import java.util.List;

public class ParameterItemInfo {

    String displayName;
    String valStr;
    String maxStr;
    String minStr;
    String unitStr;
    int unitType;
    String stepStr;
    boolean writeable;

    List<PulldownItem> pulldownItemList;
    List<BitField> bitFieldList;
    String postName;

    public ParameterItemInfo(String displayName, String[] cppRetString) throws Exception {

        valStr =  cppRetString[1];
        minStr =  cppRetString[2];
        maxStr =  cppRetString[3];
        unitStr = cppRetString[4];
        stepStr = cppRetString[5];
        unitType = new Integer(cppRetString[6]);

        this.displayName = displayName;

    }
    public ParameterItemInfo(String displayName, String postName, String[] cppRetString) throws Exception {
        this(displayName, cppRetString);
        this.postName = postName;
    }

    public String getDisplayName() {
        return displayName;
    }

    public String getPostName() {
        return postName;
    }

    public String getValStr() {
        return valStr;
    }

    public String getMaxStr() {
        return maxStr;
    }

    public String getMinStr() {
        return minStr;
    }

    public String getUnitStr() {
        return unitStr;
    }

    public int getUnitType() {
        return unitType;
    }

    public int getMax() {
        return new Integer(maxStr);
    }

    public boolean isWriteable() {
        return writeable;
    }

    public void setWriteable(boolean writeable) {
        this.writeable = writeable;
    }

    public String getStepStr() {
        return stepStr;
    }

    public List<PulldownItem> getPulldownItemList() {
        return pulldownItemList;
    }

    public void setPulldownItemList(List<PulldownItem> pulldownItemList) {
        this.pulldownItemList = pulldownItemList;
    }

    public List<BitField> getBitFieldList() {
        return bitFieldList;
    }

    public void setBitFieldList(List<BitField> bitFieldList) {
        this.bitFieldList = bitFieldList;
    }

    public String toString() {

        StringBuffer buf = new StringBuffer();
        buf.append("\ndisplayName = " + displayName +
                ", valStr = " + valStr +
                ", minStr = " + minStr +
                ", maxStr = " + maxStr +
                ", unitStr = " + unitStr +
                ", unitType = " + unitType +
                ", stepStr = " + stepStr);
        if (pulldownItemList != null) {
            buf.append("\npulldown items: ");
            for (PulldownItem pulldownItem : pulldownItemList) {
                buf.append(pulldownItem);
            }
        }
        return buf.toString();




    }

}