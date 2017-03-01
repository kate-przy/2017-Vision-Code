package org.team401.vision.controller;

import org.zeromq.ZMQ;

import java.util.ArrayList;

/**
 * Created by cameronearle on 2/24/17.
 */
public class VisionController extends Thread {

    private String address;
    private int port;

    private ArrayList<NetworkJob> jobQueue = new ArrayList<>(); //A queue to hold the jobs


    public VisionController(String address, int port) {
        this.address = address;
        this.port = port;
    }

    @Override
    public void run() {
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket socket = context.socket(ZMQ.REQ); //Create a socket to communicate with vision
        socket.connect("tcp://" + address + ":" + port);

        NetworkJob latestJob;
        while (!interrupted()) {
            if (jobQueue.size() > 0) { //If there is any data in the queue
                latestJob = jobQueue.remove(0); //Remove the latest job from the queue
                socket.send(latestJob.request.hash()); //Hash the latest job's request, and send it
                latestJob.response = NetworkData.decode(socket.recvStr()); //Set the response to the parsed response data
                latestJob.latch.countDown(); //Tick the job latch, allowing the caller to continue
            }
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                interrupt(); //Re-interrupt
            }
        }
    }

    public NetworkData request(NetworkData request) {
        NetworkJob job = new NetworkJob(request); //Create a new job for our request
        jobQueue.add(job);
        try {
            job.latch.await(); //Wait for the job to complete
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return job.response; //Return the response that should have been set by the network loop
    }
}
