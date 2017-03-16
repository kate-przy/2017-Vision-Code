package org.team401.vision.VisionDataStream;

import org.zeromq.ZMQ;

import java.util.concurrent.atomic.AtomicReference;

/**
 * Created by cameronearle on 1/20/17.
 */
public class VisionDataStream extends Thread {
    private String address;
    private int port;


    private VisionData currentGoalData = new VisionData();
    private VisionData currentGearData = new VisionData();

    public VisionDataStream(String address, int port) {
        this.address = address;
        this.port = port;
    }

    @Override
    public void run() {
        //currentData.set(new VisionData()); //Null init
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket socket = context.socket(ZMQ.SUB);
        socket.setReceiveTimeOut(500); //Set a receive timeout so that the data is marked as invalid if we don't get anything
        socket.subscribe("".getBytes());
        socket.connect("tcp://" + address + ":" + port);
        VisionData latestFromNetwork = null;
        while (!isInterrupted()) {
            latestFromNetwork = (new VisionData(socket.recvStr())); //Get the current data
            if (latestFromNetwork.getType().equals(VisionData.VisionDataType.GOAL_DATA) || latestFromNetwork.getType().equals(VisionData.VisionDataType.GOAL_DATA_INVALID)) {
                currentGoalData = latestFromNetwork;
            } else if (latestFromNetwork.getType().equals(VisionData.VisionDataType.GEAR_DATA) || latestFromNetwork.getType().equals(VisionData.VisionDataType.GEAR_DATA_INVALID)) {
                currentGearData = latestFromNetwork;
            } else {
                currentGoalData = new VisionData();
                currentGearData = new VisionData();
            }
        }
        socket.close();
    }

    public double getLatestGoalDistance() {
        return currentGoalData.distance;
    }

    public double getLatestGoalPitch() {
        return currentGoalData.pitch;
    }

    public double getLatestGoalYaw() {
        return currentGoalData.yaw;
    }

    public VisionData.Strafe getLatestGearStrafe() {
        return currentGearData.strafe;
    }

    public double getLatestGearDistance() {
        return currentGearData.distance;
    }

    public double getLatestGearYaw() {
        return currentGearData.yaw;
    }
}
