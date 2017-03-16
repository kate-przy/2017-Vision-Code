package org.team401.vision.controller;

/**
 * Created by cameronearle on 3/12/17.
 */
public class Filter {

    /**
     * Replaces toString() methods and filters out "invalid" characters/sequences from entering a networkData
     * @param o The object to filter
     * @return The filtered string
     */
    public static String filter(Object o) {
        if (o instanceof Boolean) {
            if (((Boolean) o).booleanValue()) {
                return "1";
            } else {
                return "0";
            }
        }
        return o.toString();
    }
}
