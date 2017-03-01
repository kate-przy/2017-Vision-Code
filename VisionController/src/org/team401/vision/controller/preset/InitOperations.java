package org.team401.vision.controller.preset;

import org.team401.vision.controller.NetworkData;
import org.team401.vision.controller.VisionController;

/**
 * Created by cameronearle on 2/25/17.
 */
public class InitOperations {
    public static NetworkData init(VisionController controller) {
        return controller.request(new NetworkData("INIT"));
    }
}
