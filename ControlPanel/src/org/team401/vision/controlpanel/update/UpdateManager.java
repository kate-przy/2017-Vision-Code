package org.team401.vision.controlpanel.update;

import org.team401.vision.controller.NetworkData;
import org.team401.vision.controller.VisionController;

import java.util.List;
import java.util.Vector;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Created by cameronearle on 3/12/17.
 */
public class UpdateManager {
    private VisionController controller;
    private ScheduledThreadPoolExecutor executor = new ScheduledThreadPoolExecutor(1);
    private UpdaterTask updaterTask;
    private ConnectionStateManager stateManager;

    private int interval;
    private List<UpdateGroup> updateGroupList = new Vector<>();
    
    public UpdateManager(VisionController controller, int interval, UpdateGroup... groups) {
        this.controller = controller;
        this.interval = interval;
        for (UpdateGroup g : groups) {
            updateGroupList.add(g);
        }
        updaterTask = new UpdaterTask(this, this.controller, updateGroupList);

        stateManager = new ConnectionStateManager(false);
        stateManager.update(this.controller);
    }

    public ConnectionStateManager getStateManager() {
        return stateManager;
    }

    public void start() {
        executor.scheduleAtFixedRate(updaterTask, 0, interval, TimeUnit.MILLISECONDS);
    }

    public void refreshComponents() {
        RefreshTask t = new RefreshTask(controller, updateGroupList);
        Future f = executor.submit(t);
        try {
            f.get();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }
    }

    public void setActiveCamera(VisionController.Camera newCamera) {
        executor.submit(new CameraSwitchTask(controller, newCamera));
    }

    public void setCameraMode(VisionController.Camera camera, VisionController.CameraMode newMode) {
        executor.submit(new CameraModeTask(controller, camera, newMode));
    }
}
