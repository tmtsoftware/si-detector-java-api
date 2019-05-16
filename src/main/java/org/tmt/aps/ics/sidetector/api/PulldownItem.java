package org.tmt.aps.ics.sidetector.api;

import java.util.ArrayList;
import java.util.List;

public class PulldownItem {

    String pulldownItemValue;
    String pulldownItemName;


    public PulldownItem(String pulldownItemName, String pulldownItemValue) {

        this.pulldownItemName = pulldownItemName;
        this.pulldownItemValue = pulldownItemValue;

    }

    public String getPulldownItemValue() {
        return pulldownItemValue;
    }

    public String getPulldownItemName() {
        return pulldownItemName;
    }

    public String toString() {

        return "\n" + pulldownItemName + "," + pulldownItemValue;
    }

}