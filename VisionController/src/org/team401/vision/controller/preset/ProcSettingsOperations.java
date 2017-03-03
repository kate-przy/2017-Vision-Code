package org.team401.vision.controller.preset;

import org.team401.vision.controller.NetworkData;
import org.team401.vision.controller.VisionController;

/**
 * Created by cameronearle on 2/25/17.
 */
public class ProcSettingsOperations {
    public static NetworkData setGoalProcSettings(VisionController controller, int hLower, int sLower, int vLower, int hUpper, int sUpper, int vUpper,
                                                  double minArea, double minPerimeter, double minWidth, double maxWidth,
                                                  double minHeight, double maxHeight, double minSolidity, double maxSolidity,
                                                  double minVertices, double maxVertices, double minRatio, double maxRatio) {
        NetworkData request = new NetworkData("SETTINGS_GOAL_PROC"); //Build the request
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
        
        return controller.request(request); //Make the request
    }

    public static NetworkData setGearProcSettings(VisionController controller, int hLower, int sLower, int vLower, int hUpper, int sUpper, int vUpper,
                                                  double minArea, double minPerimeter, double minWidth, double maxWidth,
                                                  double minHeight, double maxHeight, double minSolidity, double maxSolidity,
                                                  double minVertices, double maxVertices, double minRatio, double maxRatio) {
        NetworkData request = new NetworkData("SETTINGS_GEAR_PROC"); //Build the request
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

        return controller.request(request); //Make the request
    }
}
