package org.team401.vision.controlpanel.network;

import org.team401.vision.controlpanel.dialog.ResponseHook;
import org.zeromq.ZMQ;

import java.util.ArrayList;
import java.util.List;

/**
 * came20's 2017-Vision-Code
 * Copyright (C) 2017 came20 (http://came20.net)
 * License information can be found in the "LICENSE" file,
 * found inside this package.  Should a "LICENSE" file not
 * be present, it is most likely not an official package,
 * released by myself (came20), and should be used with caution
 */
public class ControlSocket implements Runnable {
    private String address;
    private int port;
    private ZMQ.Context context = ZMQ.context(1); //Initialize the zeromq context
    private ZMQ.Socket socket;
    private List<NetworkJob> jobQueue = new ArrayList<>();
    private ResponseHook dialogUpdateHook;

    public ControlSocket(String address, int port, ResponseHook dialogUpdateHook) {
        this.address = address;
        this.port = port;
        this.dialogUpdateHook = dialogUpdateHook;
    }

    public Response sendRequest(Request request, String[] params) {
        NetworkJob currentJob = new NetworkJob(request, params); //Initialize the job
        try {
            currentJob.jobLatch.await(); //Wait for the job to finish
        } catch (InterruptedException ignored) {}
        String[] responseData = currentJob.respData.split(","); //Get the response data
        Response returnResponse = new Response();
        returnResponse.exposure = Integer.parseInt(responseData[0]);
        if (dialogUpdateHook != null) {
            dialogUpdateHook.swingUpdate(returnResponse);
        }
        return returnResponse;
    }

    @Override
    public void run() {
        socket = context.socket(ZMQ.REQ);
        socket.connect("tcp://" + address + ":" + port); //Connect to the server
        NetworkJob currentJob;
        while (!Thread.currentThread().isInterrupted()) {
            while (jobQueue.size() > 0) {
                currentJob = jobQueue.remove(0); //Get the latest job
                socket.send(currentJob.request.toString() + "," + String.join("-", currentJob.params)); //Send the command string
                currentJob.respData = socket.recvStr(); //Store the response for later processing
                currentJob.jobLatch.countDown(); //Tell the sender that the job is complete
            }
            try {
                Thread.sleep(10);
            } catch (InterruptedException ignored) {
                Thread.currentThread().interrupt(); //Re-interrupt the current thread so it stops
            }
        }
    }
}
