package org.team401.visioncontroller;

/**
 * Created by cameronearle on 2/21/17.
 */
public class VisionController {
    private String address;
    private int port;

    private ControllerBackend backend;
    private Thread backendThread;

    private static String boolToCString(boolean bool) {
        if (bool) {
            return "1";
        } else {
            return "0";
        }
    }

    public VisionController(String address, int port) {
        this.address = address;
        this.port = port;
        backend = new ControllerBackend(this.address, this.port); //Initialize a backend to handle our requests
        backendThread = new Thread(backend);
    }

    public void start() {
        backendThread.start();
    }

    public void stop() {
        backendThread.interrupt();
    }

    public VisionControllerResponse setActiveCamera(Flags.StreamerMode mode) {
        return backend.submit(new NetworkJob("MODE_STREAMER_" + mode.toString() + "#"));
    }

    public VisionControllerResponse setCameraMode(Flags.Camera camera, Flags.CameraMode mode) {
        return backend.submit(new NetworkJob("MODE_" + camera.toString() + "_" + mode.toString()));
    }

    public VisionControllerResponse setStreamCompression(int compression) {
        return backend.submit(new NetworkJob("SETTINGS_STREAM_COMPRESSION#" + "streamCompression:" + compression));
    }

    public VisionControllerResponse setProcessorSettings(Flags.Camera processor, int hBase, int sBase, int vBase, int hRange, int sRange, int vRange, double aspect, double aspectRange) {
        return backend.submit(new NetworkJob("SETTINGS_" + processor.toString() + "_PROC#" +
                                            processor.toString().toLowerCase() + "ProcHBase:" + hBase + "," +
                                            processor.toString().toLowerCase() + "ProcSBase:" + sBase + "," +
                                            processor.toString().toLowerCase() + "ProcVBase:" + vBase + "," +
                                            processor.toString().toLowerCase() + "ProcHRange:" + hRange + "," +
                                            processor.toString().toLowerCase() + "ProcSRange:" + sRange + "," +
                                            processor.toString().toLowerCase() + "ProcVRange:" + vRange + "," +
                                            processor.toString().toLowerCase() + "ProcAspect:" + aspect + "," +
                                            processor.toString().toLowerCase() + "ProcAspectRange:" + aspectRange));
    }

    public VisionControllerResponse setCameraSettings(Flags.Camera camera, Flags.CameraMode mode, int brightness, int contrast, int saturation, int hue, boolean autoWB, int exposure, boolean autoGain, int gain, boolean vFlip, boolean hFlip, boolean manualExposure) {
        switch (camera) {
            case GOAL:
                switch (mode) {
                    case PROC:
                        return backend.submit(new NetworkJob("SETTINGS_GOAL_PROC_CAMERA#" +
                                "goalProcCameraBrightness:" + brightness + "," +
                                "goalProcCameraContrast:" + contrast + "," +
                                "goalProcCameraSaturation:" + saturation + "," +
                                "goalProcCameraHue:" + hue + "," +
                                "goalProcCameraAutoWB:" + boolToCString(autoWB) + "," +
                                "goalProcCameraExposure:" + exposure + "," +
                                "goalProcCameraAutoGain:" + boolToCString(autoGain) + "," +
                                "goalProcCameraGain:" + gain + "," +
                                "goalProcCameraVFlip:" + boolToCString(vFlip) + "," +
                                "goalProcCameraHFlip:" + boolToCString(hFlip) + "," +
                                "goalProcCameraManualExposure:" + boolToCString(manualExposure)));
                    case STREAM:
                        return backend.submit(new NetworkJob("SETTINGS_GOAL_STREAM_CAMERA#" +
                                "goalStreamCameraBrightness:" + brightness + "," +
                                "goalStreamCameraContrast:" + contrast + "," +
                                "goalStreamCameraSaturation:" + saturation + "," +
                                "goalStreamCameraHue:" + hue + "," +
                                "goalStreamCameraAutoWB:" + boolToCString(autoWB) + "," +
                                "goalStreamCameraExposure:" + exposure + "," +
                                "goalStreamCameraAutoGain:" + boolToCString(autoGain) + "," +
                                "goalStreamCameraGain:" + gain + "," +
                                "goalStreamCameraVFlip:" + boolToCString(vFlip) + "," +
                                "goalStreamCameraHFlip:" + boolToCString(hFlip) + "," +
                                "goalStreamCameraManualExposure:" + boolToCString(manualExposure)));
                }
                break;
            case GEAR:
                switch (mode) {
                    case PROC:
                        return backend.submit(new NetworkJob("SETTINGS_GEAR_PROC_CAMERA#" +
                                "gearProcCameraBrightness:" + brightness + "," +
                                "gearProcCameraContrast:" + contrast + "," +
                                "gearProcCameraSaturation:" + saturation + "," +
                                "gearProcCameraHue:" + hue + "," +
                                "gearProcCameraAutoWB:" + boolToCString(autoWB) + "," +
                                "gearProcCameraExposure:" + exposure + "," +
                                "gearProcCameraAutoGain:" + boolToCString(autoGain) + "," +
                                "gearProcCameraGain:" + gain + "," +
                                "gearProcCameraVFlip:" + boolToCString(vFlip) + "," +
                                "gearProcCameraHFlip:" + boolToCString(hFlip) + "," +
                                "gearProcCameraManualExposure:" + boolToCString(manualExposure)));
                    case STREAM:
                        return backend.submit(new NetworkJob("SETTINGS_GEAR_STREAM_CAMERA#" +
                                "gearStreamCameraBrightness:" + brightness + "," +
                                "gearStreamCameraContrast:" + contrast + "," +
                                "gearStreamCameraSaturation:" + saturation + "," +
                                "gearStreamCameraHue:" + hue + "," +
                                "gearStreamCameraAutoWB:" + boolToCString(autoWB) + "," +
                                "gearStreamCameraExposure:" + exposure + "," +
                                "gearStreamCameraAutoGain:" + boolToCString(autoGain) + "," +
                                "gearStreamCameraGain:" + gain + "," +
                                "gearStreamCameraVFlip:" + boolToCString(vFlip) + "," +
                                "gearStreamCameraHFlip:" + boolToCString(hFlip) + "," +
                                "gearStreamCameraManualExposure:" + boolToCString(manualExposure)));
                }
                break;
        }
        return null; //Everything else has failed
    }
}
