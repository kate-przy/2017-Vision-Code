package org.team401.vision.controlpanel.update;

import org.team401.vision.controller.NetworkData;
import org.team401.vision.controller.VisionController;

import java.util.List;
import java.util.concurrent.CountDownLatch;

/**
 * Created by cameronearle on 3/21/17.
 */
public class UpdateTask implements Runnable {
    private UpdateManager manager;
    private VisionController controller;
    private List<UpdateGroup> groupList;

    private CountDownLatch latch;

    private Dualean refreshTracker = new Dualean(false);

    public UpdateTask(UpdateManager manager, VisionController controller, List<UpdateGroup> groupList) {
        this.manager = manager;
        this.controller = controller;
        this.groupList = groupList;
    }

    @Override
    public void run() {
        latch = new CountDownLatch(1);
        refreshTracker.update(controller.ping()); //Ping vision
        if (refreshTracker.currentTruePreviousFalse()) { //We have just connected, and we have to update
            manager.refresh();
        } else if (refreshTracker.bothTrue()) { //We are connected and have refreshed
            for (UpdateGroup g : groupList) { //Iterate the groups
                NetworkData d = new NetworkData(g.getName()); //Create a data to send
                List<UpdatePair> pairList = g.getPairList(); //Get the update pairs from the group
                for (UpdatePair p : pairList) { //Iterate the pairs
                    d.putElement(p.getKey(), p.getValue()); //Add each pair to the data to send
                }
                controller.request(d); //Push the data
            }
        } else {
            System.out.println("NOT CONNECTED!!!");
        }
        latch.countDown();
    }

    public void waitForStop() {
        try {
            latch.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
