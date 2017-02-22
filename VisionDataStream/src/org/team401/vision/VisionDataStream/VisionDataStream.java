package org.team401.vision.VisionDataStream;

import org.zeromq.ZMQ;

import java.util.concurrent.atomic.AtomicReference;

/**
 * Created by cameronearle on 1/20/17.
 */
public class VisionDataStream extends Thread {
    private String address;
    private int port;

    private AtomicReference<VisionData> currentGoalData = new AtomicReference<VisionData>(new VisionData()); //Atomic variable to hold the latest data
    private AtomicReference<VisionData> currentGearData = new AtomicReference<VisionData>(new VisionData());

    public VisionDataStream(String address, int port) {
        this.address = address;
        this.port = port;
    }

    @Override
    public void run() {
        //currentData.set(new VisionData()); //Null init
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket socket = context.socket(ZMQ.SUB);
        socket.setReceiveTimeOut(30); //Set a receive timeout so that the data is marked as invalid if we don't get anything
        socket.subscribe("".getBytes());
        socket.connect("tcp://" + address + ":" + port);
        VisionData latestFromNetwork = null;
        while (!isInterrupted()) {
            latestFromNetwork = (new VisionData(socket.recvStr())); //Get the current data
            if (latestFromNetwork.getType().equals(VisionData.VisionDataType.GOAL_DATA) || latestFromNetwork.getType().equals(VisionData.VisionDataType.GOAL_DATA_INVALID)) {
                currentGoalData.set(latestFromNetwork);
            } else if (latestFromNetwork.getType().equals(VisionData.VisionDataType.GEAR_DATA) || latestFromNetwork.getType().equals(VisionData.VisionDataType.GEAR_DATA_INVALID)) {
                currentGearData.set(latestFromNetwork);
            } else {
                currentGoalData.set(new VisionData());
                currentGearData.set(new VisionData());
            }
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                Thread.interrupted(); //Re-enstate the interrupt
            }
        }
        socket.close();
    }

    public VisionData getLatestGoalData() {
        return currentGoalData.get();
    }

    public VisionData getLatestGearData() {
        return currentGearData.get();
    }
}
