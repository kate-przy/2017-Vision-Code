package org.team401.vision.VisionDataStream;

import java.util.HashMap;

/**
 * Created by cameronearle on 1/20/17.
 */

public class VisionData {
    public enum VisionDataType {
        GOAL_DATA,
        GEAR_DATA,
        GOAL_DATA_INVALID,
        GEAR_DATA_INVALID,
        INVALID,
        SHUTDOWN
    }

    public enum Strafe {
        LEFT(-1),
        CENTER(0),
        RIGHT(1),
        INVALID(-2);

        private int value;

        Strafe(int value) {
            this.value = value;
        }
    }

    private VisionDataType type = VisionDataType.INVALID;
    private double distance = 0;
    private double pitch = 0;
    private double yaw = 0;
    private Strafe strafe = null;

    private HashMap<String, String> rawData = new HashMap<>();

    /**
     * "null" constructor, makes an invalid visiondata
     */
    public VisionData() {
        type = VisionDataType.INVALID;
    }

    VisionData(String decodeStr) {
        if (decodeStr != null) {
            String[] headerSplit = decodeStr.split("#"); //Split on the separator for the message identifier
            if (headerSplit.length > 0) { //We have an identifier
                if (headerSplit[0].equals("INVALID")) {
                    type = VisionDataType.INVALID;
                } else if (headerSplit[0].equals("SHUTDOWN")) {
                    type = VisionDataType.SHUTDOWN;
                } else if (headerSplit[0].equals("GOAL_DATA")) {
                    type = VisionDataType.GOAL_DATA;
                } else if (headerSplit[0].equals("GEAR_DATA")) {
                    type = VisionDataType.GEAR_DATA;
                } else if (headerSplit[0].equals("GOAL_DATA_INVALID")) {
                    type = VisionDataType.GOAL_DATA_INVALID;
                } else if (headerSplit[0].equals("GEAR_DATA_INVALID")) {
                    type = VisionDataType.GEAR_DATA_INVALID;
                } else {
                    type = VisionDataType.INVALID;
                }
            }
            if (type.equals(VisionDataType.GOAL_DATA) || type.equals(VisionDataType.GEAR_DATA)) {
                if (headerSplit.length > 1) { //If there is actually data
                    String[] pairs = headerSplit[1].split(","); //Get the data pairs
                    for (String s : pairs) {
                        String[] currentElementPair = s.split(":"); //Split up the current data pair
                        if (currentElementPair.length == 2) { //If there are enough elements for valid data
                            rawData.put(currentElementPair[0], currentElementPair[1]); //Place the pair in the map
                        }
                    }
                    try {
                        distance = Double.parseDouble(rawData.getOrDefault("distance", "0"));
                    } catch (Exception ignored) {
                        distance = 0;
                    }
                    try {
                        pitch = Double.parseDouble(rawData.getOrDefault("pitch", "0"));
                    } catch (Exception ignored) {
                        pitch = 0;
                    }
                    try {
                        yaw = Double.parseDouble(rawData.getOrDefault("yaw", "0"));
                    } catch (Exception ignored) {
                        yaw = 0;
                    }
                    int strafeNum;
                    try {
                        strafeNum = Integer.parseInt(rawData.getOrDefault("strafe", "-2"));
                    } catch (Exception ignored) {
                        strafeNum = -2;
                    }
                    if (strafeNum == -1) {
                        strafe = Strafe.LEFT;
                    } else if (strafeNum == 0) {
                        strafe = Strafe.CENTER;
                    } else if (strafeNum == 1) {
                        strafe = Strafe.RIGHT;
                    } else {
                        strafe = Strafe.INVALID;
                    }
                }
            }
        } else {
            type = VisionDataType.INVALID;
        }
    }

    public VisionData(double distance, double pitch, double yaw) {
        type = VisionDataType.GOAL_DATA;
        this.distance = distance;
        this.pitch = pitch;
        this.yaw = yaw;
    }

    public VisionData(double distance, double yaw, Strafe strafe) {
        type = VisionDataType.GEAR_DATA;
        this.distance = distance;
        this.yaw = yaw;
        this.strafe = strafe;
    }

    public VisionDataType getType() {
        return type;
    }

    public boolean isValid() {
        return !(type.equals(VisionDataType.INVALID) || type.equals(VisionDataType.GOAL_DATA_INVALID)|| type.equals(VisionDataType.GEAR_DATA_INVALID));
    }

    public double getDistance() {
        return distance;
    }

    public double getPitch() {
        return pitch;
    }

    public double getYaw() {
        return yaw;
    }

    public Strafe getStrafe() {
        return strafe;
    }
}

