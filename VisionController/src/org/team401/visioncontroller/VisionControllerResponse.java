package org.team401.visioncontroller;

import java.util.HashMap;

/**
 * Created by cameronearle on 2/21/17.
 */
public class VisionControllerResponse {
    private static boolean boolFromCStr(String s) throws Exception {
        if (s.equals("1")) {
            return true;
        } else if (s.equals("0")) {
            return false;
        } else {
            throw new Exception();
        }
    }

    private int goalProcDeviceNumber;
    private int gearProcDeviceNumber;
    private int goalProcFOV;
    private int gearProcFOV;
    private int streamDeviceNumber;
    private int networkBasePort;
    private boolean showDebugWindows;
    private boolean showDebugText;
    private boolean runDebugFunctions;

    private int streamCompression;

    private int goalProcHBase;
    private int goalProcSBase;
    private int goalProcVBase;
    private int goalProcHRange;
    private int goalProcSRange;
    private int goalProcVRange;

    private int gearProcHBase;
    private int gearProcSBase;
    private int gearProcVBase;
    private int gearProcHRange;
    private int gearProcSRange;
    private int gearProcVRange;

    private double goalProcAspect;
    private double gearProcAspect;
    private double goalProcAspectRange;
    private double gearProcAspectRange;

    private int goalProcCameraBrightness;
    private int goalProcCameraContrast;
    private int goalProcCameraSaturation;
    private int goalProcCameraHue;
    private boolean goalProcCameraAutoWB;
    private int goalProcCameraExposure;
    private boolean goalProcCameraAutoGain;
    private int goalProcCameraGain;
    private boolean goalProcCameraVFlip;
    private boolean goalProcCameraHFlip;
    private boolean goalProcCameraManualExposure;

    private int gearProcCameraBrightness;
    private int gearProcCameraContrast;
    private int gearProcCameraSaturation;
    private int gearProcCameraHue;
    private boolean gearProcCameraAutoWB;
    private int gearProcCameraExposure;
    private boolean gearProcCameraAutoGain;
    private int gearProcCameraGain;
    private boolean gearProcCameraVFlip;
    private boolean gearProcCameraHFlip;
    private boolean gearProcCameraManualExposure;

    private int goalStreamCameraBrightness;
    private int goalStreamCameraContrast;
    private int goalStreamCameraSaturation;
    private int goalStreamCameraHue;
    private boolean goalStreamCameraAutoWB;
    private int goalStreamCameraExposure;
    private boolean goalStreamCameraAutoGain;
    private int goalStreamCameraGain;
    private boolean goalStreamCameraVFlip;
    private boolean goalStreamCameraHFlip;
    private boolean goalStreamCameraManualExposure;

    private int gearStreamCameraBrightness;
    private int gearStreamCameraContrast;
    private int gearStreamCameraSaturation;
    private int gearStreamCameraHue;
    private boolean gearStreamCameraAutoWB;
    private int gearStreamCameraExposure;
    private boolean gearStreamCameraAutoGain;
    private int gearStreamCameraGain;
    private boolean gearStreamCameraVFlip;
    private boolean gearStreamCameraHFlip;
    private boolean gearStreamCameraManualExposure;

    public VisionControllerResponse(int goalProcDeviceNumber, int gearProcDeviceNumber, int goalProcFOV, int gearProcFOV, int streamDeviceNumber, int networkBasePort, boolean showDebugWindows, boolean showDebugText, boolean runDebugFunctions, int streamCompression, int goalProcHBase, int goalProcSBase, int goalProcVBase, int goalProcHRange, int goalProcSRange, int goalProcVRange, int gearProcHBase, int gearProcSBase, int gearProcVBase, int gearProcHRange, int gearProcSRange, int gearProcVRange, double goalProcAspect, double gearProcAspect, double goalProcAspectRange, double gearProcAspectRange, int goalProcCameraBrightness, int goalProcCameraContrast, int goalProcCameraSaturation, int goalProcCameraHue, boolean goalProcCameraAutoWB, int goalProcCameraExposure, boolean goalProcCameraAutoGain, int goalProcCameraGain, boolean goalProcCameraVFlip, boolean goalProcCameraHFlip, boolean goalProcCameraManualExposure, int gearProcCameraBrightness, int gearProcCameraContrast, int gearProcCameraSaturation, int gearProcCameraHue, boolean gearProcCameraAutoWB, int gearProcCameraExposure, boolean gearProcCameraAutoGain, int gearProcCameraGain, boolean gearProcCameraVFlip, boolean gearProcCameraHFlip, boolean gearProcCameraManualExposure, int goalStreamCameraBrightness, int goalStreamCameraContrast, int goalStreamCameraSaturation, int goalStreamCameraHue, boolean goalStreamCameraAutoWB, int goalStreamCameraExposure, boolean goalStreamCameraAutoGain, int goalStreamCameraGain, boolean goalStreamCameraVFlip, boolean goalStreamCameraHFlip, boolean goalStreamCameraManualExposure, int gearStreamCameraBrightness, int gearStreamCameraContrast, int gearStreamCameraSaturation, int gearStreamCameraHue, boolean gearStreamCameraAutoWB, int gearStreamCameraExposure, boolean gearStreamCameraAutoGain, int gearStreamCameraGain, boolean gearStreamCameraVFlip, boolean gearStreamCameraHFlip, boolean gearStreamCameraManualExposure) {
        this.goalProcDeviceNumber = goalProcDeviceNumber;
        this.gearProcDeviceNumber = gearProcDeviceNumber;
        this.goalProcFOV = goalProcFOV;
        this.gearProcFOV = gearProcFOV;
        this.streamDeviceNumber = streamDeviceNumber;
        this.networkBasePort = networkBasePort;
        this.showDebugWindows = showDebugWindows;
        this.showDebugText = showDebugText;
        this.runDebugFunctions = runDebugFunctions;
        this.streamCompression = streamCompression;
        this.goalProcHBase = goalProcHBase;
        this.goalProcSBase = goalProcSBase;
        this.goalProcVBase = goalProcVBase;
        this.goalProcHRange = goalProcHRange;
        this.goalProcSRange = goalProcSRange;
        this.goalProcVRange = goalProcVRange;
        this.gearProcHBase = gearProcHBase;
        this.gearProcSBase = gearProcSBase;
        this.gearProcVBase = gearProcVBase;
        this.gearProcHRange = gearProcHRange;
        this.gearProcSRange = gearProcSRange;
        this.gearProcVRange = gearProcVRange;
        this.goalProcAspect = goalProcAspect;
        this.gearProcAspect = gearProcAspect;
        this.goalProcAspectRange = goalProcAspectRange;
        this.gearProcAspectRange = gearProcAspectRange;
        this.goalProcCameraBrightness = goalProcCameraBrightness;
        this.goalProcCameraContrast = goalProcCameraContrast;
        this.goalProcCameraSaturation = goalProcCameraSaturation;
        this.goalProcCameraHue = goalProcCameraHue;
        this.goalProcCameraAutoWB = goalProcCameraAutoWB;
        this.goalProcCameraExposure = goalProcCameraExposure;
        this.goalProcCameraAutoGain = goalProcCameraAutoGain;
        this.goalProcCameraGain = goalProcCameraGain;
        this.goalProcCameraVFlip = goalProcCameraVFlip;
        this.goalProcCameraHFlip = goalProcCameraHFlip;
        this.goalProcCameraManualExposure = goalProcCameraManualExposure;
        this.gearProcCameraBrightness = gearProcCameraBrightness;
        this.gearProcCameraContrast = gearProcCameraContrast;
        this.gearProcCameraSaturation = gearProcCameraSaturation;
        this.gearProcCameraHue = gearProcCameraHue;
        this.gearProcCameraAutoWB = gearProcCameraAutoWB;
        this.gearProcCameraExposure = gearProcCameraExposure;
        this.gearProcCameraAutoGain = gearProcCameraAutoGain;
        this.gearProcCameraGain = gearProcCameraGain;
        this.gearProcCameraVFlip = gearProcCameraVFlip;
        this.gearProcCameraHFlip = gearProcCameraHFlip;
        this.gearProcCameraManualExposure = gearProcCameraManualExposure;
        this.goalStreamCameraBrightness = goalStreamCameraBrightness;
        this.goalStreamCameraContrast = goalStreamCameraContrast;
        this.goalStreamCameraSaturation = goalStreamCameraSaturation;
        this.goalStreamCameraHue = goalStreamCameraHue;
        this.goalStreamCameraAutoWB = goalStreamCameraAutoWB;
        this.goalStreamCameraExposure = goalStreamCameraExposure;
        this.goalStreamCameraAutoGain = goalStreamCameraAutoGain;
        this.goalStreamCameraGain = goalStreamCameraGain;
        this.goalStreamCameraVFlip = goalStreamCameraVFlip;
        this.goalStreamCameraHFlip = goalStreamCameraHFlip;
        this.goalStreamCameraManualExposure = goalStreamCameraManualExposure;
        this.gearStreamCameraBrightness = gearStreamCameraBrightness;
        this.gearStreamCameraContrast = gearStreamCameraContrast;
        this.gearStreamCameraSaturation = gearStreamCameraSaturation;
        this.gearStreamCameraHue = gearStreamCameraHue;
        this.gearStreamCameraAutoWB = gearStreamCameraAutoWB;
        this.gearStreamCameraExposure = gearStreamCameraExposure;
        this.gearStreamCameraAutoGain = gearStreamCameraAutoGain;
        this.gearStreamCameraGain = gearStreamCameraGain;
        this.gearStreamCameraVFlip = gearStreamCameraVFlip;
        this.gearStreamCameraHFlip = gearStreamCameraHFlip;
        this.gearStreamCameraManualExposure = gearStreamCameraManualExposure;
    }

    public VisionControllerResponse(String encoded) {
        String[] dataSplit = encoded.split("#");
        HashMap<String, String> elementsMap = new HashMap<>();
        if (dataSplit.length >= 2) { //If the data is correct
            String[] argsSplit = dataSplit[1].split(",");
            for (String s : argsSplit) {
                String[] argSplit = s.split(":");
                if (argSplit.length == 2) { //If the arg is in the correct format
                    elementsMap.put(argSplit[0], argSplit[1]); //Append it to the map
                }
            }

            //VALUE ASSIGNMENT
            try { goalProcDeviceNumber = Integer.valueOf(elementsMap.getOrDefault("goalProcDeviceNumber", "0")); } catch (Exception e) { goalProcDeviceNumber = 0; }
            try { gearProcDeviceNumber = Integer.valueOf(elementsMap.getOrDefault("gearProcDeviceNumber", "0")); } catch (Exception e) { gearProcDeviceNumber = 0; }
            try { goalProcFOV = Integer.valueOf(elementsMap.getOrDefault("goalProcFOV", "0")); } catch (Exception e) { goalProcFOV = 0; }
            try { gearProcFOV = Integer.valueOf(elementsMap.getOrDefault("gearProcFOV", "0")); } catch (Exception e) { gearProcFOV = 0; }
            try { streamDeviceNumber = Integer.valueOf(elementsMap.getOrDefault("streamDeviceNumber", "0")); } catch (Exception e) { streamDeviceNumber = 0; }
            try { networkBasePort = Integer.valueOf(elementsMap.getOrDefault("networkBasePort", "0")); } catch (Exception e) { networkBasePort = 0; }
            try { showDebugWindows = boolFromCStr(elementsMap.getOrDefault("showDebugWindows", "0")); } catch (Exception e) { showDebugWindows = false; }
            try { showDebugText = boolFromCStr(elementsMap.getOrDefault("showDebugText", "0")); } catch (Exception e) { showDebugText = false; }
            try { runDebugFunctions = boolFromCStr(elementsMap.getOrDefault("runDebugFunctions", "0")); } catch (Exception e) { runDebugFunctions = false; }
            try { streamCompression = Integer.valueOf(elementsMap.getOrDefault("streamCompression", "0")); } catch (Exception e) { streamCompression = 0; }
            try { goalProcHBase = Integer.valueOf(elementsMap.getOrDefault("goalProcHBase", "0")); } catch (Exception e) { goalProcHBase = 0; }
            try { goalProcSBase = Integer.valueOf(elementsMap.getOrDefault("goalProcSBase", "0")); } catch (Exception e) { goalProcSBase = 0; }
            try { goalProcVBase = Integer.valueOf(elementsMap.getOrDefault("goalProcVBase", "0")); } catch (Exception e) { goalProcVBase = 0; }
            try { goalProcHRange = Integer.valueOf(elementsMap.getOrDefault("goalProcHRange", "0")); } catch (Exception e) { goalProcHRange = 0; }
            try { goalProcSRange = Integer.valueOf(elementsMap.getOrDefault("goalProcSRange", "0")); } catch (Exception e) { goalProcSRange = 0; }
            try { goalProcVRange = Integer.valueOf(elementsMap.getOrDefault("goalProcVRange", "0")); } catch (Exception e) { goalProcVRange = 0; }
            try { gearProcHBase = Integer.valueOf(elementsMap.getOrDefault("gearProcHBase", "0")); } catch (Exception e) { gearProcHBase = 0; }
            try { gearProcSBase = Integer.valueOf(elementsMap.getOrDefault("gearProcSBase", "0")); } catch (Exception e) { gearProcSBase = 0; }
            try { gearProcVBase = Integer.valueOf(elementsMap.getOrDefault("gearProcVBase", "0")); } catch (Exception e) { gearProcVBase = 0; }
            try { gearProcHRange = Integer.valueOf(elementsMap.getOrDefault("gearProcHRange", "0")); } catch (Exception e) { gearProcHRange = 0; }
            try { gearProcSRange = Integer.valueOf(elementsMap.getOrDefault("gearProcSRange", "0")); } catch (Exception e) { gearProcSRange = 0; }
            try { gearProcVRange = Integer.valueOf(elementsMap.getOrDefault("gearProcVRange", "0")); } catch (Exception e) { gearProcVRange = 0; }
            try { goalProcAspect = Double.valueOf(elementsMap.getOrDefault("goalProcAspect", "0")); } catch (Exception e) { goalProcAspect = 0; }
            try { gearProcAspect = Double.valueOf(elementsMap.getOrDefault("gearProcAspect", "0")); } catch (Exception e) { gearProcAspect = 0; }
            try { goalProcAspectRange = Double.valueOf(elementsMap.getOrDefault("goalProcAspectRange", "0")); } catch (Exception e) { goalProcAspectRange = 0; }
            try { gearProcAspectRange = Double.valueOf(elementsMap.getOrDefault("gearProcAspectRange", "0")); } catch (Exception e) { gearProcAspectRange = 0; }
            try { goalProcCameraBrightness = Integer.valueOf(elementsMap.getOrDefault("goalProcCameraBrightness", "0")); } catch (Exception e) { goalProcCameraBrightness = 0; }
            try { goalProcCameraContrast = Integer.valueOf(elementsMap.getOrDefault("goalProcCameraContrast", "0")); } catch (Exception e) { goalProcCameraContrast = 0; }
            try { goalProcCameraSaturation = Integer.valueOf(elementsMap.getOrDefault("goalProcCameraSaturation", "0")); } catch (Exception e) { goalProcCameraSaturation = 0; }
            try { goalProcCameraHue = Integer.valueOf(elementsMap.getOrDefault("goalProcCameraHue", "0")); } catch (Exception e) { goalProcCameraHue = 0; }
            try { goalProcCameraAutoWB = boolFromCStr(elementsMap.getOrDefault("goalProcCameraAutoWB", "0")); } catch (Exception e) { goalProcCameraAutoWB = false; }
            try { goalProcCameraExposure = Integer.valueOf(elementsMap.getOrDefault("goalProcCameraExposure", "0")); } catch (Exception e) { goalProcCameraExposure = 0; }
            try { goalProcCameraAutoGain = boolFromCStr(elementsMap.getOrDefault("goalProcCameraAutoGain", "0")); } catch (Exception e) { goalProcCameraAutoGain = false; }
            try { goalProcCameraGain = Integer.valueOf(elementsMap.getOrDefault("goalProcCameraGain", "0")); } catch (Exception e) { goalProcCameraGain = 0; }
            try { goalProcCameraVFlip = boolFromCStr(elementsMap.getOrDefault("goalProcCameraVFlip", "0")); } catch (Exception e) { goalProcCameraVFlip = false; }
            try { goalProcCameraHFlip = boolFromCStr(elementsMap.getOrDefault("goalProcCameraHFlip", "0")); } catch (Exception e) { goalProcCameraHFlip = false; }
            try { goalProcCameraManualExposure = boolFromCStr(elementsMap.getOrDefault("goalProcCameraManualExposure", "0")); } catch (Exception e) { goalProcCameraManualExposure = false; }
            try { gearProcCameraBrightness = Integer.valueOf(elementsMap.getOrDefault("gearProcCameraBrightness", "0")); } catch (Exception e) { gearProcCameraBrightness = 0; }
            try { gearProcCameraContrast = Integer.valueOf(elementsMap.getOrDefault("gearProcCameraContrast", "0")); } catch (Exception e) { gearProcCameraContrast = 0; }
            try { gearProcCameraSaturation = Integer.valueOf(elementsMap.getOrDefault("gearProcCameraSaturation", "0")); } catch (Exception e) { gearProcCameraSaturation = 0; }
            try { gearProcCameraHue = Integer.valueOf(elementsMap.getOrDefault("gearProcCameraHue", "0")); } catch (Exception e) { gearProcCameraHue = 0; }
            try { gearProcCameraAutoWB = boolFromCStr(elementsMap.getOrDefault("gearProcCameraAutoWB", "0")); } catch (Exception e) { gearProcCameraAutoWB = false; }
            try { gearProcCameraExposure = Integer.valueOf(elementsMap.getOrDefault("gearProcCameraExposure", "0")); } catch (Exception e) { gearProcCameraExposure = 0; }
            try { gearProcCameraAutoGain = boolFromCStr(elementsMap.getOrDefault("gearProcCameraAutoGain", "0")); } catch (Exception e) { gearProcCameraAutoGain = false; }
            try { gearProcCameraGain = Integer.valueOf(elementsMap.getOrDefault("gearProcCameraGain", "0")); } catch (Exception e) { gearProcCameraGain = 0; }
            try { gearProcCameraVFlip = boolFromCStr(elementsMap.getOrDefault("gearProcCameraVFlip", "0")); } catch (Exception e) { gearProcCameraVFlip = false; }
            try { gearProcCameraHFlip = boolFromCStr(elementsMap.getOrDefault("gearProcCameraHFlip", "0")); } catch (Exception e) { gearProcCameraHFlip = false; }
            try { gearProcCameraManualExposure = boolFromCStr(elementsMap.getOrDefault("gearProcCameraManualExposure", "0")); } catch (Exception e) { gearProcCameraManualExposure = false; }
            try { goalStreamCameraBrightness = Integer.valueOf(elementsMap.getOrDefault("goalStreamCameraBrightness", "0")); } catch (Exception e) { goalStreamCameraBrightness = 0; }
            try { goalStreamCameraContrast = Integer.valueOf(elementsMap.getOrDefault("goalStreamCameraContrast", "0")); } catch (Exception e) { goalStreamCameraContrast = 0; }
            try { goalStreamCameraSaturation = Integer.valueOf(elementsMap.getOrDefault("goalStreamCameraSaturation", "0")); } catch (Exception e) { goalStreamCameraSaturation = 0; }
            try { goalStreamCameraHue = Integer.valueOf(elementsMap.getOrDefault("goalStreamCameraHue", "0")); } catch (Exception e) { goalStreamCameraHue = 0; }
            try { goalStreamCameraAutoWB = boolFromCStr(elementsMap.getOrDefault("goalStreamCameraAutoWB", "0")); } catch (Exception e) { goalStreamCameraAutoWB = false; }
            try { goalStreamCameraExposure = Integer.valueOf(elementsMap.getOrDefault("goalStreamCameraExposure", "0")); } catch (Exception e) { goalStreamCameraExposure = 0; }
            try { goalStreamCameraAutoGain = boolFromCStr(elementsMap.getOrDefault("goalStreamCameraAutoGain", "0")); } catch (Exception e) { goalStreamCameraAutoGain = false; }
            try { goalStreamCameraGain = Integer.valueOf(elementsMap.getOrDefault("goalStreamCameraGain", "0")); } catch (Exception e) { goalStreamCameraGain = 0; }
            try { goalStreamCameraVFlip = boolFromCStr(elementsMap.getOrDefault("goalStreamCameraVFlip", "0")); } catch (Exception e) { goalStreamCameraVFlip = false; }
            try { goalStreamCameraHFlip = boolFromCStr(elementsMap.getOrDefault("goalStreamCameraHFlip", "0")); } catch (Exception e) { goalStreamCameraHFlip = false; }
            try { goalStreamCameraManualExposure = boolFromCStr(elementsMap.getOrDefault("goalStreamCameraManualExposure", "0")); } catch (Exception e) { goalStreamCameraManualExposure = false; }
            try { gearStreamCameraBrightness = Integer.valueOf(elementsMap.getOrDefault("gearStreamCameraBrightness", "0")); } catch (Exception e) { gearStreamCameraBrightness = 0; }
            try { gearStreamCameraContrast = Integer.valueOf(elementsMap.getOrDefault("gearStreamCameraContrast", "0")); } catch (Exception e) { gearStreamCameraContrast = 0; }
            try { gearStreamCameraSaturation = Integer.valueOf(elementsMap.getOrDefault("gearStreamCameraSaturation", "0")); } catch (Exception e) { gearStreamCameraSaturation = 0; }
            try { gearStreamCameraHue = Integer.valueOf(elementsMap.getOrDefault("gearStreamCameraHue", "0")); } catch (Exception e) { gearStreamCameraHue = 0; }
            try { gearStreamCameraAutoWB = boolFromCStr(elementsMap.getOrDefault("gearStreamCameraAutoWB", "0")); } catch (Exception e) { gearStreamCameraAutoWB = false; }
            try { gearStreamCameraExposure = Integer.valueOf(elementsMap.getOrDefault("gearStreamCameraExposure", "0")); } catch (Exception e) { gearStreamCameraExposure = 0; }
            try { gearStreamCameraAutoGain = boolFromCStr(elementsMap.getOrDefault("gearStreamCameraAutoGain", "0")); } catch (Exception e) { gearStreamCameraAutoGain = false; }
            try { gearStreamCameraGain = Integer.valueOf(elementsMap.getOrDefault("gearStreamCameraGain", "0")); } catch (Exception e) { gearStreamCameraGain = 0; }
            try { gearStreamCameraVFlip = boolFromCStr(elementsMap.getOrDefault("gearStreamCameraVFlip", "0")); } catch (Exception e) { gearStreamCameraVFlip = false; }
            try { gearStreamCameraHFlip = boolFromCStr(elementsMap.getOrDefault("gearStreamCameraHFlip", "0")); } catch (Exception e) { gearStreamCameraHFlip = false; }
            try { gearStreamCameraManualExposure = boolFromCStr(elementsMap.getOrDefault("gearStreamCameraManualExposure", "0")); } catch (Exception e) { gearStreamCameraManualExposure = false; }
        }
    }

    public int getGoalProcDeviceNumber() {
        return goalProcDeviceNumber;
    }

    public void setGoalProcDeviceNumber(int goalProcDeviceNumber) {
        this.goalProcDeviceNumber = goalProcDeviceNumber;
    }

    public int getGearProcDeviceNumber() {
        return gearProcDeviceNumber;
    }

    public void setGearProcDeviceNumber(int gearProcDeviceNumber) {
        this.gearProcDeviceNumber = gearProcDeviceNumber;
    }

    public int getGoalProcFOV() {
        return goalProcFOV;
    }

    public void setGoalProcFOV(int goalProcFOV) {
        this.goalProcFOV = goalProcFOV;
    }

    public int getGearProcFOV() {
        return gearProcFOV;
    }

    public void setGearProcFOV(int gearProcFOV) {
        this.gearProcFOV = gearProcFOV;
    }

    public int getStreamDeviceNumber() {
        return streamDeviceNumber;
    }

    public void setStreamDeviceNumber(int streamDeviceNumber) {
        this.streamDeviceNumber = streamDeviceNumber;
    }

    public int getNetworkBasePort() {
        return networkBasePort;
    }

    public void setNetworkBasePort(int networkBasePort) {
        this.networkBasePort = networkBasePort;
    }

    public boolean isShowDebugWindows() {
        return showDebugWindows;
    }

    public void setShowDebugWindows(boolean showDebugWindows) {
        this.showDebugWindows = showDebugWindows;
    }

    public boolean isShowDebugText() {
        return showDebugText;
    }

    public void setShowDebugText(boolean showDebugText) {
        this.showDebugText = showDebugText;
    }

    public boolean isRunDebugFunctions() {
        return runDebugFunctions;
    }

    public void setRunDebugFunctions(boolean runDebugFunctions) {
        this.runDebugFunctions = runDebugFunctions;
    }

    public int getStreamCompression() {
        return streamCompression;
    }

    public void setStreamCompression(int streamCompression) {
        this.streamCompression = streamCompression;
    }

    public int getGoalProcHBase() {
        return goalProcHBase;
    }

    public void setGoalProcHBase(int goalProcHBase) {
        this.goalProcHBase = goalProcHBase;
    }

    public int getGoalProcSBase() {
        return goalProcSBase;
    }

    public void setGoalProcSBase(int goalProcSBase) {
        this.goalProcSBase = goalProcSBase;
    }

    public int getGoalProcVBase() {
        return goalProcVBase;
    }

    public void setGoalProcVBase(int goalProcVBase) {
        this.goalProcVBase = goalProcVBase;
    }

    public int getGoalProcHRange() {
        return goalProcHRange;
    }

    public void setGoalProcHRange(int goalProcHRange) {
        this.goalProcHRange = goalProcHRange;
    }

    public int getGoalProcSRange() {
        return goalProcSRange;
    }

    public void setGoalProcSRange(int goalProcSRange) {
        this.goalProcSRange = goalProcSRange;
    }

    public int getGoalProcVRange() {
        return goalProcVRange;
    }

    public void setGoalProcVRange(int goalProcVRange) {
        this.goalProcVRange = goalProcVRange;
    }

    public int getGearProcHBase() {
        return gearProcHBase;
    }

    public void setGearProcHBase(int gearProcHBase) {
        this.gearProcHBase = gearProcHBase;
    }

    public int getGearProcSBase() {
        return gearProcSBase;
    }

    public void setGearProcSBase(int gearProcSBase) {
        this.gearProcSBase = gearProcSBase;
    }

    public int getGearProcVBase() {
        return gearProcVBase;
    }

    public void setGearProcVBase(int gearProcVBase) {
        this.gearProcVBase = gearProcVBase;
    }

    public int getGearProcHRange() {
        return gearProcHRange;
    }

    public void setGearProcHRange(int gearProcHRange) {
        this.gearProcHRange = gearProcHRange;
    }

    public int getGearProcSRange() {
        return gearProcSRange;
    }

    public void setGearProcSRange(int gearProcSRange) {
        this.gearProcSRange = gearProcSRange;
    }

    public int getGearProcVRange() {
        return gearProcVRange;
    }

    public void setGearProcVRange(int gearProcVRange) {
        this.gearProcVRange = gearProcVRange;
    }

    public double getGoalProcAspect() {
        return goalProcAspect;
    }

    public void setGoalProcAspect(double goalProcAspect) {
        this.goalProcAspect = goalProcAspect;
    }

    public double getGearProcAspect() {
        return gearProcAspect;
    }

    public void setGearProcAspect(double gearProcAspect) {
        this.gearProcAspect = gearProcAspect;
    }

    public double getGoalProcAspectRange() {
        return goalProcAspectRange;
    }

    public void setGoalProcAspectRange(double goalProcAspectRange) {
        this.goalProcAspectRange = goalProcAspectRange;
    }

    public double getGearProcAspectRange() {
        return gearProcAspectRange;
    }

    public void setGearProcAspectRange(double gearProcAspectRange) {
        this.gearProcAspectRange = gearProcAspectRange;
    }

    public int getGoalProcCameraBrightness() {
        return goalProcCameraBrightness;
    }

    public void setGoalProcCameraBrightness(int goalProcCameraBrightness) {
        this.goalProcCameraBrightness = goalProcCameraBrightness;
    }

    public int getGoalProcCameraContrast() {
        return goalProcCameraContrast;
    }

    public void setGoalProcCameraContrast(int goalProcCameraContrast) {
        this.goalProcCameraContrast = goalProcCameraContrast;
    }

    public int getGoalProcCameraSaturation() {
        return goalProcCameraSaturation;
    }

    public void setGoalProcCameraSaturation(int goalProcCameraSaturation) {
        this.goalProcCameraSaturation = goalProcCameraSaturation;
    }

    public int getGoalProcCameraHue() {
        return goalProcCameraHue;
    }

    public void setGoalProcCameraHue(int goalProcCameraHue) {
        this.goalProcCameraHue = goalProcCameraHue;
    }

    public boolean isGoalProcCameraAutoWB() {
        return goalProcCameraAutoWB;
    }

    public void setGoalProcCameraAutoWB(boolean goalProcCameraAutoWB) {
        this.goalProcCameraAutoWB = goalProcCameraAutoWB;
    }

    public int getGoalProcCameraExposure() {
        return goalProcCameraExposure;
    }

    public void setGoalProcCameraExposure(int goalProcCameraExposure) {
        this.goalProcCameraExposure = goalProcCameraExposure;
    }

    public boolean isGoalProcCameraAutoGain() {
        return goalProcCameraAutoGain;
    }

    public void setGoalProcCameraAutoGain(boolean goalProcCameraAutoGain) {
        this.goalProcCameraAutoGain = goalProcCameraAutoGain;
    }

    public int getGoalProcCameraGain() {
        return goalProcCameraGain;
    }

    public void setGoalProcCameraGain(int goalProcCameraGain) {
        this.goalProcCameraGain = goalProcCameraGain;
    }

    public boolean isGoalProcCameraVFlip() {
        return goalProcCameraVFlip;
    }

    public void setGoalProcCameraVFlip(boolean goalProcCameraVFlip) {
        this.goalProcCameraVFlip = goalProcCameraVFlip;
    }

    public boolean isGoalProcCameraHFlip() {
        return goalProcCameraHFlip;
    }

    public void setGoalProcCameraHFlip(boolean goalProcCameraHFlip) {
        this.goalProcCameraHFlip = goalProcCameraHFlip;
    }

    public boolean isGoalProcCameraManualExposure() {
        return goalProcCameraManualExposure;
    }

    public void setGoalProcCameraManualExposure(boolean goalProcCameraManualExposure) {
        this.goalProcCameraManualExposure = goalProcCameraManualExposure;
    }

    public int getGearProcCameraBrightness() {
        return gearProcCameraBrightness;
    }

    public void setGearProcCameraBrightness(int gearProcCameraBrightness) {
        this.gearProcCameraBrightness = gearProcCameraBrightness;
    }

    public int getGearProcCameraContrast() {
        return gearProcCameraContrast;
    }

    public void setGearProcCameraContrast(int gearProcCameraContrast) {
        this.gearProcCameraContrast = gearProcCameraContrast;
    }

    public int getGearProcCameraSaturation() {
        return gearProcCameraSaturation;
    }

    public void setGearProcCameraSaturation(int gearProcCameraSaturation) {
        this.gearProcCameraSaturation = gearProcCameraSaturation;
    }

    public int getGearProcCameraHue() {
        return gearProcCameraHue;
    }

    public void setGearProcCameraHue(int gearProcCameraHue) {
        this.gearProcCameraHue = gearProcCameraHue;
    }

    public boolean isGearProcCameraAutoWB() {
        return gearProcCameraAutoWB;
    }

    public void setGearProcCameraAutoWB(boolean gearProcCameraAutoWB) {
        this.gearProcCameraAutoWB = gearProcCameraAutoWB;
    }

    public int getGearProcCameraExposure() {
        return gearProcCameraExposure;
    }

    public void setGearProcCameraExposure(int gearProcCameraExposure) {
        this.gearProcCameraExposure = gearProcCameraExposure;
    }

    public boolean isGearProcCameraAutoGain() {
        return gearProcCameraAutoGain;
    }

    public void setGearProcCameraAutoGain(boolean gearProcCameraAutoGain) {
        this.gearProcCameraAutoGain = gearProcCameraAutoGain;
    }

    public int getGearProcCameraGain() {
        return gearProcCameraGain;
    }

    public void setGearProcCameraGain(int gearProcCameraGain) {
        this.gearProcCameraGain = gearProcCameraGain;
    }

    public boolean isGearProcCameraVFlip() {
        return gearProcCameraVFlip;
    }

    public void setGearProcCameraVFlip(boolean gearProcCameraVFlip) {
        this.gearProcCameraVFlip = gearProcCameraVFlip;
    }

    public boolean isGearProcCameraHFlip() {
        return gearProcCameraHFlip;
    }

    public void setGearProcCameraHFlip(boolean gearProcCameraHFlip) {
        this.gearProcCameraHFlip = gearProcCameraHFlip;
    }

    public boolean isGearProcCameraManualExposure() {
        return gearProcCameraManualExposure;
    }

    public void setGearProcCameraManualExposure(boolean gearProcCameraManualExposure) {
        this.gearProcCameraManualExposure = gearProcCameraManualExposure;
    }

    public int getGoalStreamCameraBrightness() {
        return goalStreamCameraBrightness;
    }

    public void setGoalStreamCameraBrightness(int goalStreamCameraBrightness) {
        this.goalStreamCameraBrightness = goalStreamCameraBrightness;
    }

    public int getGoalStreamCameraContrast() {
        return goalStreamCameraContrast;
    }

    public void setGoalStreamCameraContrast(int goalStreamCameraContrast) {
        this.goalStreamCameraContrast = goalStreamCameraContrast;
    }

    public int getGoalStreamCameraSaturation() {
        return goalStreamCameraSaturation;
    }

    public void setGoalStreamCameraSaturation(int goalStreamCameraSaturation) {
        this.goalStreamCameraSaturation = goalStreamCameraSaturation;
    }

    public int getGoalStreamCameraHue() {
        return goalStreamCameraHue;
    }

    public void setGoalStreamCameraHue(int goalStreamCameraHue) {
        this.goalStreamCameraHue = goalStreamCameraHue;
    }

    public boolean isGoalStreamCameraAutoWB() {
        return goalStreamCameraAutoWB;
    }

    public void setGoalStreamCameraAutoWB(boolean goalStreamCameraAutoWB) {
        this.goalStreamCameraAutoWB = goalStreamCameraAutoWB;
    }

    public int getGoalStreamCameraExposure() {
        return goalStreamCameraExposure;
    }

    public void setGoalStreamCameraExposure(int goalStreamCameraExposure) {
        this.goalStreamCameraExposure = goalStreamCameraExposure;
    }

    public boolean isGoalStreamCameraAutoGain() {
        return goalStreamCameraAutoGain;
    }

    public void setGoalStreamCameraAutoGain(boolean goalStreamCameraAutoGain) {
        this.goalStreamCameraAutoGain = goalStreamCameraAutoGain;
    }

    public int getGoalStreamCameraGain() {
        return goalStreamCameraGain;
    }

    public void setGoalStreamCameraGain(int goalStreamCameraGain) {
        this.goalStreamCameraGain = goalStreamCameraGain;
    }

    public boolean isGoalStreamCameraVFlip() {
        return goalStreamCameraVFlip;
    }

    public void setGoalStreamCameraVFlip(boolean goalStreamCameraVFlip) {
        this.goalStreamCameraVFlip = goalStreamCameraVFlip;
    }

    public boolean isGoalStreamCameraHFlip() {
        return goalStreamCameraHFlip;
    }

    public void setGoalStreamCameraHFlip(boolean goalStreamCameraHFlip) {
        this.goalStreamCameraHFlip = goalStreamCameraHFlip;
    }

    public boolean isGoalStreamCameraManualExposure() {
        return goalStreamCameraManualExposure;
    }

    public void setGoalStreamCameraManualExposure(boolean goalStreamCameraManualExposure) {
        this.goalStreamCameraManualExposure = goalStreamCameraManualExposure;
    }

    public int getGearStreamCameraBrightness() {
        return gearStreamCameraBrightness;
    }

    public void setGearStreamCameraBrightness(int gearStreamCameraBrightness) {
        this.gearStreamCameraBrightness = gearStreamCameraBrightness;
    }

    public int getGearStreamCameraContrast() {
        return gearStreamCameraContrast;
    }

    public void setGearStreamCameraContrast(int gearStreamCameraContrast) {
        this.gearStreamCameraContrast = gearStreamCameraContrast;
    }

    public int getGearStreamCameraSaturation() {
        return gearStreamCameraSaturation;
    }

    public void setGearStreamCameraSaturation(int gearStreamCameraSaturation) {
        this.gearStreamCameraSaturation = gearStreamCameraSaturation;
    }

    public int getGearStreamCameraHue() {
        return gearStreamCameraHue;
    }

    public void setGearStreamCameraHue(int gearStreamCameraHue) {
        this.gearStreamCameraHue = gearStreamCameraHue;
    }

    public boolean isGearStreamCameraAutoWB() {
        return gearStreamCameraAutoWB;
    }

    public void setGearStreamCameraAutoWB(boolean gearStreamCameraAutoWB) {
        this.gearStreamCameraAutoWB = gearStreamCameraAutoWB;
    }

    public int getGearStreamCameraExposure() {
        return gearStreamCameraExposure;
    }

    public void setGearStreamCameraExposure(int gearStreamCameraExposure) {
        this.gearStreamCameraExposure = gearStreamCameraExposure;
    }

    public boolean isGearStreamCameraAutoGain() {
        return gearStreamCameraAutoGain;
    }

    public void setGearStreamCameraAutoGain(boolean gearStreamCameraAutoGain) {
        this.gearStreamCameraAutoGain = gearStreamCameraAutoGain;
    }

    public int getGearStreamCameraGain() {
        return gearStreamCameraGain;
    }

    public void setGearStreamCameraGain(int gearStreamCameraGain) {
        this.gearStreamCameraGain = gearStreamCameraGain;
    }

    public boolean isGearStreamCameraVFlip() {
        return gearStreamCameraVFlip;
    }

    public void setGearStreamCameraVFlip(boolean gearStreamCameraVFlip) {
        this.gearStreamCameraVFlip = gearStreamCameraVFlip;
    }

    public boolean isGearStreamCameraHFlip() {
        return gearStreamCameraHFlip;
    }

    public void setGearStreamCameraHFlip(boolean gearStreamCameraHFlip) {
        this.gearStreamCameraHFlip = gearStreamCameraHFlip;
    }

    public boolean isGearStreamCameraManualExposure() {
        return gearStreamCameraManualExposure;
    }

    public void setGearStreamCameraManualExposure(boolean gearStreamCameraManualExposure) {
        this.gearStreamCameraManualExposure = gearStreamCameraManualExposure;
    }
}
