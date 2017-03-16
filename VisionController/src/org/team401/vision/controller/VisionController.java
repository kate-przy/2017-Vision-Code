package org.team401.vision.controller;

import org.team401.vision.controller.event.*;
import org.zeromq.ZMQ;

import java.util.ArrayList;
import java.util.Vector;


/**
 * Created by cameronearle on 2/24/17.
 */
public class VisionController extends Thread {

    private String address;
    private int port;

    private EventHandlerGroup<OutgoingDataEventHandler> outgoingHandlerGroup = new EventHandlerGroup<>();
    private EventHandlerGroup<IncomingDataEventHandler> incomingHandlerGroup = new EventHandlerGroup<>();

    private Vector<NetworkJob> jobQueue = new Vector<>(); //A queue to hold the jobs


    public VisionController(String address, int port) {
        this.address = address;
        this.port = port;
    }

    public void addOutgoingDataEventHandler(OutgoingDataEventHandler e) {
        outgoingHandlerGroup.addEventHandler(e);
    }

    public void addIncomingDataEventHandler(IncomingDataEventHandler e) {
        incomingHandlerGroup.addEventHandler(e);
    }

    @Override
    public void run() {
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket socket = context.socket(ZMQ.REQ); //Create a socket to communicate with vision
        socket.setReceiveTimeOut(1000); //Wait up to one second
        socket.connect("tcp://" + address + ":" + port);

        NetworkJob latestJob;
        while (!interrupted()) {
            if (jobQueue.size() > 0) { //If there is any data in the queue
                latestJob = jobQueue.remove(0); //Remove the latest job from the queue
                try {
                    socket.send(latestJob.request.hash());
                    final NetworkData finalRequest = latestJob.request;
                    new Thread(() -> outgoingHandlerGroup.callGroup(new OutgoingDataEvent(finalRequest))).start(); //Announce the send
                } catch (Exception e) {}

                try {
                    latestJob.response = NetworkData.decode(socket.recvStr()); //Try to get the response
                    final NetworkData finalResponse = latestJob.response;
                    new Thread(() -> incomingHandlerGroup.callGroup(new IncomingDataEvent(finalResponse))).start(); //Announce the receive
                } catch (Exception e) {
                    latestJob.response = new NetworkData("INVALID"); //Set to invalid if there was no response
                }
                latestJob.latch.countDown(); //Tick the job latch, allowing the caller to continue
            }
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                interrupt(); //Re-interrupt
            }
        }
    }

    public NetworkData request(NetworkData request) {
        NetworkJob job = new NetworkJob(request); //Create a new job for our request
        jobQueue.add(job);
        try {
            job.latch.await(); //Wait for the job to complete
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return job.response; //Return the response that should have been set by the network loop
    }

    public void asyncRequest(NetworkData request) {
        NetworkJob job = new NetworkJob(request);
        jobQueue.add(job);
    }


    ////// ROBOT SPECIFIC SETTINGS //////
    public enum Camera {
        OFF(0, "OFF"),
        GOAL(1, "GOAL"),
        GEAR(2, "GEAR");

        private final int ID;
        private final String NAME;

        Camera(int id, String name) {
            ID = id;
            NAME = name;
        }
    }
    private Camera currentCamera = Camera.GOAL;

    //// STREAM SETTINGS ////

    public enum CameraMode {
        PROCESSING(0, "PROC"),
        STREAMING(1, "STREAM");

        private final int ID;
        private final String NAME;

        CameraMode(int id, String name) {
            ID = id;
            NAME = name;
        }
    }
    private CameraMode currentGoalCameraMode = CameraMode.PROCESSING;
    private CameraMode currentGearCameraMode = CameraMode.PROCESSING;

    /**
     * Sets the camera that will be streamed
     * @param camera The camera to stream
     */
    public void setActiveCamera(Camera camera) {
        if (camera != null) {
            asyncRequest(new NetworkData("MODE_STREAMER_" + camera.NAME));
            currentCamera = camera;
        }
    }

    /**
     * Gets the currently known active camera
     * @return The active camera
     */
    public Camera getActiveCamera() {
        return currentCamera;
    }

    public void setCameraMode(Camera camera, CameraMode mode) {
        if (camera != null && mode != null && camera != Camera.OFF) {
            asyncRequest(new NetworkData("MODE_" + camera.NAME + "_" + mode.NAME));
            switch (camera) { //Block to update our stored camera modes
                case GOAL:
                    currentGoalCameraMode = mode;
                    break;
                case GEAR:
                    currentGearCameraMode = mode;
                    break;
            }
        }
    }

    /**
     * Gets the mode of the specified camera
     * @param camera The specified camera
     * @return The mode of the specified camera
     */
    public CameraMode getCurrentCameraMode(Camera camera) {
        if (camera != null && camera != Camera.OFF) {
            switch (camera) {
                case GOAL:
                    return currentGoalCameraMode;
                case GEAR:
                    return currentGearCameraMode;
            }
        }
        return CameraMode.PROCESSING;
    }

    /**
     * Toggles between active cameras
     */
    public void toggleActiveCamera() {
        switch (currentCamera) {
            case GOAL:
                setActiveCamera(Camera.GEAR);
                break;
            case GEAR:
                setActiveCamera(Camera.GOAL);
                break;
            case OFF: //If the streaming is off, this will turn it back on
                setActiveCamera(Camera.GOAL);
                break;
        }
    }

    /**
     * Sets the quality of the stream
     * WARNING: HIGH LEVELS CAN CAUSE NON-RECOVERABLE LAG!!!
     * @param quality The quality level to set, integer between 0 and 100
     * @return The updated config
     */
    public void setQuality(int quality) {
        asyncRequest(new NetworkData("SETTINGS_STREAM_COMPRESSION", new Pair("streamCompression", quality)));
    }

    //// END STREAM SETTINGS ////

    //// GET SETTINGS ////

    /**
     * Grabs the latest config from the vision code
     * @return The latest config
     */
    public NetworkData getCurrentSettings() {
        return request(new NetworkData("INIT"));
    }

    //// END GET SETTINGS ////

    //// PROC SETTINGS ////

    /**
     * Sets the camera settings for the specified camera
     * @param camera The specified camera
     * @param hLower The lower H bound
     * @param sLower The lower S bound
     * @param vLower The lower V bound
     * @param hUpper The upper H bound
     * @param sUpper The upper S bound
     * @param vUpper The upper V bound
     * @param minArea The minimum area of the target
     * @param minPerimeter The minimum perimeter of the target
     * @param minWidth The minimum width of the target (pixels)
     * @param maxWidth The maximum width of the target (pixels)
     * @param minHeight The minimum height of the target (pixels)
     * @param maxHeight The maximum height of the target (pixels)
     * @param minSolidity The minimum solidity of the target
     * @param maxSolidity The maximum solidity of the target
     * @param minVertices The minimum vertices of the target
     * @param maxVertices The maximum vertices of the target
     * @param minRatio The minimum ratio of the target
     * @param maxRatio The maximum ratio of the target
     * @return The updated config
     */
    public void setProcSettings(Camera camera, int hLower, int sLower, int vLower, int hUpper, int sUpper, int vUpper,
                                                  double minArea, double minPerimeter, double minWidth, double maxWidth,
                                                  double minHeight, double maxHeight, double minSolidity, double maxSolidity,
                                                  double minVertices, double maxVertices, double minRatio, double maxRatio) {
        NetworkData request = new NetworkData("INVALID"); //Start with an invalid request

        switch (camera) {
            case GOAL:
                request = new NetworkData("SETTINGS_GOAL_PROC"); //Build the request
                request.putElement("goalProcHLower", hLower);
                request.putElement("goalProcSLower", sLower);
                request.putElement("goalProcVLower", vLower);
                request.putElement("goalProcHUpper", hUpper);
                request.putElement("goalProcSUpper", sUpper);
                request.putElement("goalProcVUpper", vUpper);
                request.putElement("goalMinArea", minArea);
                request.putElement("goalMinPerimeter", minPerimeter);
                request.putElement("goalMinWidth", minWidth);
                request.putElement("goalMaxWidth", maxWidth);
                request.putElement("goalMinHeight", minHeight);
                request.putElement("goalMaxHeight", maxHeight);
                request.putElement("goalMinSolidity", minSolidity);
                request.putElement("goalMaxSolidity", maxSolidity);
                request.putElement("goalMinVertices", minVertices);
                request.putElement("goalMaxVertices", maxVertices);
                request.putElement("goalMinRatio", minRatio);
                request.putElement("goalMaxRatio", maxRatio);
                break;
            case GEAR:
                request = new NetworkData("SETTINGS_GEAR_PROC"); //Build the request
                request.putElement("gearProcHLower", hLower);
                request.putElement("gearProcSLower", sLower);
                request.putElement("gearProcVLower", vLower);
                request.putElement("gearProcHUpper", hUpper);
                request.putElement("gearProcSUpper", sUpper);
                request.putElement("gearProcVUpper", vUpper);
                request.putElement("gearMinArea", minArea);
                request.putElement("gearMinPerimeter", minPerimeter);
                request.putElement("gearMinWidth", minWidth);
                request.putElement("gearMaxWidth", maxWidth);
                request.putElement("gearMinHeight", minHeight);
                request.putElement("gearMaxHeight", maxHeight);
                request.putElement("gearMinSolidity", minSolidity);
                request.putElement("gearMaxSolidity", maxSolidity);
                request.putElement("gearMinVertices", minVertices);
                request.putElement("gearMaxVertices", maxVertices);
                request.putElement("gearMinRatio", minRatio);
                request.putElement("gearMaxRatio", maxRatio);
                break;
        }
        asyncRequest(request); //Make the request
    }

    //// END PROC SETTINGS ////

    //// CAMERA SETTINGS ////

    /**
     * Sets camera settings on the specified camera
     * @param camera The specified camera
     * @param cameraMode The mode to set settings for
     * @param brightness The brightness of the image
     * @param contrast The contrast of the image
     * @param saturation The saturation of the image
     * @param hue The hue of the image
     * @param autoWB Should we use Auto White Balance?
     * @param exposure The exposure of the image
     * @param autoGain Should we use Auto Gain Control?
     * @param gain The gain of the image
     * @param vFlip Should we flip the image vertically (upside-down camera)
     * @param hFlip Should we flip the image horizontally (sideways camera)
     * @param manualExposure Should we use manual exposure?
     * @return The updated config
     */
    public void setCameraSettings(Camera camera, CameraMode cameraMode, int brightness, int contrast, int saturation,
                                         int hue, boolean autoWB, int exposure, boolean autoGain, int gain,
                                         boolean vFlip, boolean hFlip, boolean manualExposure) {
        NetworkData request = new NetworkData("INVALID");
        switch (camera) {
            case GOAL:
                switch (cameraMode) {
                    case PROCESSING:
                        request = new NetworkData("SETTINGS_GOAL_PROC_CAMERA"); //Build the request
                        request.putElement("goalProcCameraBrightness", brightness);
                        request.putElement("goalProcCameraContrast", contrast);
                        request.putElement("goalProcCameraSaturation", saturation);
                        request.putElement("goalProcCameraHue", hue);
                        request.putElement("goalProcCameraAutoWB", autoWB);
                        request.putElement("goalProcCameraExposure", exposure);
                        request.putElement("goalProcCameraAutoGain", autoGain);
                        request.putElement("goalProcCameraGain", gain);
                        request.putElement("goalProcCameraVFlip", vFlip);
                        request.putElement("goalProcCameraHFlip", hFlip);
                        request.putElement("goalProcCameraManualExposure", manualExposure);
                        break;
                    case STREAMING:
                        request = new NetworkData("SETTINGS_GOAL_STREAM_CAMERA"); //Build the request
                        request.putElement("goalStreamCameraBrightness", brightness);
                        request.putElement("goalStreamCameraContrast", contrast);
                        request.putElement("goalStreamCameraSaturation", saturation);
                        request.putElement("goalStreamCameraHue", hue);
                        request.putElement("goalStreamCameraAutoWB", autoWB);
                        request.putElement("goalStreamCameraExposure", exposure);
                        request.putElement("goalStreamCameraAutoGain", autoGain);
                        request.putElement("goalStreamCameraGain", gain);
                        request.putElement("goalStreamCameraVFlip", vFlip);
                        request.putElement("goalStreamCameraHFlip", hFlip);
                        request.putElement("goalStreamCameraManualExposure", manualExposure);
                        break;
                }
                break;
            case GEAR:
                switch (cameraMode) {
                    case PROCESSING:
                        request = new NetworkData("SETTINGS_GEAR_PROC_CAMERA"); //Build the request
                        request.putElement("gearProcCameraBrightness", brightness);
                        request.putElement("gearProcCameraContrast", contrast);
                        request.putElement("gearProcCameraSaturation", saturation);
                        request.putElement("gearProcCameraHue", hue);
                        request.putElement("gearProcCameraAutoWB", autoWB);
                        request.putElement("gearProcCameraExposure", exposure);
                        request.putElement("gearProcCameraAutoGain", autoGain);
                        request.putElement("gearProcCameraGain", gain);
                        request.putElement("gearProcCameraVFlip", vFlip);
                        request.putElement("gearProcCameraHFlip", hFlip);
                        request.putElement("gearProcCameraManualExposure", manualExposure);
                        break;
                    case STREAMING:
                        request = new NetworkData("SETTINGS_GEAR_STREAM_CAMERA"); //Build the request
                        request.putElement("gearStreamCameraBrightness", brightness);
                        request.putElement("gearStreamCameraContrast", contrast);
                        request.putElement("gearStreamCameraSaturation", saturation);
                        request.putElement("gearStreamCameraHue", hue);
                        request.putElement("gearStreamCameraAutoWB", autoWB);
                        request.putElement("gearStreamCameraExposure", exposure);
                        request.putElement("gearStreamCameraAutoGain", autoGain);
                        request.putElement("gearStreamCameraGain", gain);
                        request.putElement("gearStreamCameraVFlip", vFlip);
                        request.putElement("gearStreamCameraHFlip", hFlip);
                        request.putElement("gearStreamCameraManualExposure", manualExposure);
                        break;
                }
                break;
        }
        asyncRequest(request);
    }

    //// END CAMERA SETTINGS ////

}
