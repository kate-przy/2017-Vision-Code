package org.team401.vision.controlpanel.dialog;


import org.team401.vision.controlpanel.network.Response;

import javax.swing.*;

/**
 * Created by cameronearle on 1/19/17.
 */
public class ResponseHook {
    private LinkedControlGroup exposureGroup;

    ResponseHook(LinkedControlGroup exposureGroup) {
        this.exposureGroup = exposureGroup;
    }

    /**
     * Fires an update from the current thread
     * @param response The response to read new data from
     */
    public void pushUpdate(Response response) {
        exposureGroup.updateAll(response.exposure); //Runs directly, updating immediately
    }

    /**
     * Fires an update event on the swing thread
     * @param response The response to read new data from
     */
    public void swingUpdate(Response response) {
        SwingUtilities.invokeLater(() -> pushUpdate(response)); //Puts a runnable on the swing runtime, invoked at some point
    }

    /**
     * Fires an update event on a new thread
     * @param response The response to read new data from
     */
    public void asyncUpdate(Response response) {
        new Thread(() -> pushUpdate(response)).start(); //Puts a runnable on the thread stack, invoked as soon as possible
    }
}
