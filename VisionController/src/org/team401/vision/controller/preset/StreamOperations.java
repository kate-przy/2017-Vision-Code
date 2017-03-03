package org.team401.vision.controller.preset;

import org.team401.vision.controller.NetworkData;
import org.team401.vision.controller.Pair;
import org.team401.vision.controller.VisionController;

/**
 * Created by cameronearle on 2/25/17.
 */
public class StreamOperations {
    public static NetworkData setActiveCameraOff(VisionController controller) {
        return controller.request(new NetworkData("MODE_STREAMER_OFF"));
    }

    public static NetworkData setActiveCameraGoal(VisionController controller) {
        return controller.request(new NetworkData("MODE_STREAMER_GOAL"));
    }

    public static NetworkData setActiveCameraGear(VisionController controller) {
        return controller.request(new NetworkData("MODE_STREAMER_GEAR"));
    }

    public static NetworkData setGoalCameraProc(VisionController controller) {
        return controller.request(new NetworkData("MODE_GOAL_PROC"));
    }

    public static NetworkData setGoalCameraStream(VisionController controller) {
        return controller.request(new NetworkData("MODE_GOAL_STREAM"));
    }

    public static NetworkData setGearCameraProc(VisionController controller) {
        return controller.request(new NetworkData("MODE_GEAR_PROC"));
    }

    public static NetworkData setGearCameraStream(VisionController controller) {
        return controller.request(new NetworkData("MODE_GEAR_STREAM"));
    }

    public static NetworkData setCompression(VisionController controller, int newCompression) {
        return controller.request(new NetworkData("SETTINGS_STREAM_COMPRESSION", new Pair("compression", newCompression)));
    }
}
