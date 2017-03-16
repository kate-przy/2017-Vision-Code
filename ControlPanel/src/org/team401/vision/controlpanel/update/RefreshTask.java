package org.team401.vision.controlpanel.update;

import org.team401.vision.controller.NetworkData;
import org.team401.vision.controller.VisionController;

import java.util.List;
import java.util.Vector;

/**
 * Created by cameronearle on 3/13/17.
 */
class RefreshTask implements Runnable {
    private List<UpdateGroup> groupList = new Vector<>();
    private VisionController controller;

    public RefreshTask(VisionController controller, List<UpdateGroup> groups) {
        System.out.println("---GROUPS---");
        for (UpdateGroup g : groups) {
            System.out.println(g.getName());
        }
        System.out.println("---END GROUPS---");
        this.controller = controller;
        for (UpdateGroup g : groups) {
            groupList.add(g);
        }
    }

    @Override
    public void run() {
        System.out.println("REFRESHING");
        NetworkData latestData = controller.getCurrentSettings();
        for (UpdateGroup g : groupList) {
            g.updateGroup(latestData);
        }
        System.out.println("IM DONE SCUM");
    }
}
