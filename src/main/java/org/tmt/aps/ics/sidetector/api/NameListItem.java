package org.tmt.aps.ics.sidetector.api;

import java.util.ArrayList;
import java.util.List;


public class NameListItem {

    String listName;
    String displayName;
    boolean writeable;


    public NameListItem(String inputString) {

        String[] splitString = inputString.split("\\s*,\\s*");

        listName = splitString[0];
        displayName = splitString[1];
        writeable = splitString[2].equals("rw");

    }

    public String getListName() {
        return listName;
    }

    public String getDisplayName() {
        return displayName;
    }

    public boolean isWriteable() {
        return writeable;
    }

    public static List<NameListItem> generateList(String cppRetString) {
        ArrayList<NameListItem> list = new ArrayList<NameListItem>();

        // read each line from the string
        String[] stringArray = cppRetString.split("[\\n]");

        for (String input : stringArray) {
            NameListItem nameListItem = new NameListItem(input);
            list.add(nameListItem);
        }
        return list;
    }



    public String toString() {
        return listName + "," + displayName + "," + writeable;
    }

}