package org.team401.vision.controller.preset;

import org.team401.vision.controller.NetworkData;
import org.team401.vision.controller.VisionController;

/**
 * Created by cameronearle on 2/25/17.
 */
public class CameraSettingsOperations {
    public static NetworkData setGoalProcCameraSettings(VisionController controller, int brightness, int contrast, int saturation,
                                                  int hue, boolean autoWB, int exposure, boolean autoGain, int gain,
                                                  boolean vFlip, boolean hFlip, boolean manualExposure) {
        NetworkData request = new NetworkData("SETTINGS_GOAL_PROC_CAMERA"); //Build the request
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

        return controller.request(request); //Make the request
    }

    public static NetworkData setGearProcCameraSettings(VisionController controller, int brightness, int contrast, int saturation,
                                                  int hue, boolean autoWB, int exposure, boolean autoGain, int gain,
                                                  boolean vFlip, boolean hFlip, boolean manualExposure) {
        NetworkData request = new NetworkData("SETTINGS_GEAR_PROC_CAMERA"); //Build the request
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

        return controller.request(request); //Make the request
    }

    public static NetworkData setGoalStreamCameraSettings(VisionController controller, int brightness, int contrast, int saturation,
                                                  int hue, boolean autoWB, int exposure, boolean autoGain, int gain,
                                                  boolean vFlip, boolean hFlip, boolean manualExposure) {
        NetworkData request = new NetworkData("SETTINGS_GOAL_STREAM_CAMERA"); //Build the request
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

        return controller.request(request); //Make the request
    }

    public static NetworkData setGearStreamCameraSettings(VisionController controller, int brightness, int contrast, int saturation,
                                                  int hue, boolean autoWB, int exposure, boolean autoGain, int gain,
                                                  boolean vFlip, boolean hFlip, boolean manualExposure) {
        NetworkData request = new NetworkData("SETTINGS_GEAR_STREAM_CAMERA"); //Build the request
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

        return controller.request(request); //Make the request
    }
}
