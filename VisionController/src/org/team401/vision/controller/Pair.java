package org.team401.vision.controller;

/**
 * Class to hold two elements, used for varargs constructor
 */
public class Pair {
    private String key;
    private String value;

    public Pair(String key, Object value) {
        this.key = key;
        this.value = Filter.filter(value);
    }

    public String getKey() {
        return key;
    }

    public String getValue() {
        return value;
    }
}