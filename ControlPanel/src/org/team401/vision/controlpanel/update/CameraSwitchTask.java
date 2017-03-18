package org.team401.vision.controlpanel.update;

import org.team401.vision.controller.VisionController;

/**
 * Created by cameronearle on 3/16/17.
 */
class CameraSwitchTask implements Runnable {
    private VisionController controller;
    private VisionController.Camera camera;
    public CameraSwitchTask(VisionController controller, VisionController.Camera camera) {
        this.controller = controller;
        this.camera = camera;
    }

    @Override
    public void run() {
        controller.setActiveCamera(camera);
    }
}
