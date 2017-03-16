package org.team401.vision.controlpanel.update;

import org.team401.vision.controller.NetworkData;
import org.team401.vision.controller.VisionController;

import java.util.List;
import java.util.Vector;
import java.util.concurrent.Future;
import java.util.concurrent.ScheduledThreadPoolExecutor;

/**
 * Created by cameronearle on 3/13/17.
 */
class UpdaterTask implements Runnable {
    private List<UpdateGroup> groupList = new Vector<>();
    private VisionController controller;

    public UpdaterTask(VisionController controller, List<UpdateGroup> groups) {
        this.controller = controller;
        for (UpdateGroup g : groups) {
            groupList.add(g);
        }
    }

    @Override
    public void run() {
        for (UpdateGroup g : groupList) {
            NetworkData d = new NetworkData(g.getName()); //Initialize the data to send
            List<UpdatePair> pairs = g.getPairList();
            for (UpdatePair p : pairs) {
                d.putElement(p.getKey(), p.getValue()); //Translate update data to network data
            }
            controller.asyncRequest(d);
        }
    }
}
