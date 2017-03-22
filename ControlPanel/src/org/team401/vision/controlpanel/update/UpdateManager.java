package org.team401.vision.controlpanel.update;

import org.team401.vision.controller.NetworkData;
import org.team401.vision.controller.VisionController;

import java.util.List;
import java.util.Vector;
import java.util.concurrent.Future;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Created by cameronearle on 3/12/17.
 */
public class UpdateManager {
    private VisionController controller; //The controller to send data with

    private int interval; //The interval to run at
    private List<UpdateGroup> updateGroupList = new Vector<>(); //The list of groups to update

    private ScheduledThreadPoolExecutor executor = new ScheduledThreadPoolExecutor(1); //An executor to run our tasks
    private Future mainFuture;
    private UpdateTask task;
    
    public UpdateManager(VisionController controller, int interval, UpdateGroup... groups) {
        this.controller = controller;
        this.interval = interval;
        for (UpdateGroup g : groups) {
            updateGroupList.add(g);
        }
        task = new UpdateTask(this, controller, updateGroupList);
    }

    public void start() {
        mainFuture = executor.scheduleAtFixedRate(task, 0, interval, TimeUnit.MILLISECONDS);
    }

    public void stop() {
        if (mainFuture != null) {
            mainFuture.cancel(true);
        }
        mainFuture = null;
    }

    public void refresh() {
        System.out.println("UPDATING");
        if (controller.ping()) { //If vision is online
            System.out.println("VISION ONLINE");
            NetworkData d = controller.getCurrentSettings(); //Get the latest settings from the server
            for (UpdateGroup g : updateGroupList) {
                System.out.println("UPDATING: " + g.getName());
                g.updateGroup(d); //Update the gui
            }
        }
        System.out.println("DONE UPDATING!");

    }
}
