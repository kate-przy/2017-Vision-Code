package org.team401.vision.controlpanel.update;

import org.team401.vision.controller.VisionController;

/**
 * Created by cameronearle on 3/16/17.
 */
class CameraModeTask implements Runnable {
    private VisionController controller;
    private VisionController.Camera camera;
    private VisionController.CameraMode mode;

    public CameraModeTask(VisionController controller, VisionController.Camera camera, VisionController.CameraMode mode) {
        this.controller = controller;
        this.camera = camera;
        this.mode = mode;
    }

    @Override
    public void run() {
        controller.setCameraMode(camera, mode);
    }
}
