package org.team401.visioncontroller;

import org.zeromq.ZMQ;

import java.util.ArrayList;

/**
 * Created by cameronearle on 2/21/17.
 */
class ControllerBackend implements Runnable {
    private String address;
    private int port;
    private ArrayList<NetworkJob> jobQueue = new ArrayList<>();

    ControllerBackend(String address, int port) {
        this.address = address;
        this.port = port;
    }

    @Override
    public void run() {
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket socket = context.socket(ZMQ.REQ);
        socket.connect("tcp://" + address + ":" + port);
        NetworkJob latestJob;
        while (!Thread.interrupted()) {
            if (jobQueue.size() > 0) {
                latestJob = jobQueue.remove(0);
                socket.send(latestJob.getRequest());
                latestJob.setResponse(socket.recvStr());
                latestJob.latch.countDown(); //Release the job
            }
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); //Reset the interrupt flag
            }
        }
        socket.close(); //Close the socket when we are done with it
    }

    public VisionControllerResponse submit(NetworkJob job) {
        jobQueue.add(job);
        try {
            job.latch.await();
        } catch (InterruptedException e) {}
        return new VisionControllerResponse(job.getResponse());
    }
}
