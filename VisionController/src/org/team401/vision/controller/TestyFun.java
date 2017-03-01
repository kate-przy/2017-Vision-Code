package org.team401.vision.controller;


import org.team401.vision.controller.preset.CameraSettingsOperations;
import org.team401.vision.controller.preset.StreamOperations;

/**
 * Created by cameronearle on 2/24/17.
 */
public class TestyFun {
    public static void main(String[] args) {
        VisionController controller = new VisionController("127.0.0.1", 5803);
        controller.start();

        StreamOperations.setGoalCameraStream(controller);
    }
}
