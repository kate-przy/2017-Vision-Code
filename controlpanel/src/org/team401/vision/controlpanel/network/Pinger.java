package org.team401.vision.controlpanel.network;

import org.team401.vision.controlpanel.dialog.PingerUpdateHook;
import org.zeromq.ZMQ;

import java.util.HashMap;

/**
 * Created by cameronearle on 1/18/17.
 */
public class Pinger {
    public static boolean ping(String address, int port, int timeout, PingerUpdateHook hook) {
        if (hook != null) {
            hook.setIndeterminate(true);
            hook.updateStatus("Setting up");
        }
        ZMQ.Context context = ZMQ.context(1); //Initialize a context
        ZMQ.Socket pingSock = context.socket(ZMQ.REQ); //Initialize a socket to connect to the server
        pingSock.setReceiveTimeOut(timeout); //Set up the ping timeout
        if (hook != null) {
            hook.setIndeterminate(false);
            hook.updateStatus("Connecting");
            hook.updateProgress(25);
        }
        pingSock.connect("tcp://" + address + ":" + port); //Connect to the server
        if (hook != null) {
            hook.updateStatus("Pinging");
            hook.updateProgress(50);
        }
        pingSock.send("PING");
        if (hook != null) {
            hook.updateStatus("Waiting for response");
            hook.updateProgress(75);
        }
        boolean result;
        result = pingSock.recvStr() != null; //If the ping succeeded
        if (result) {
            hook.updateStatus("Ping Successful!");
            hook.updateProgress(100);
        } else {
            hook.updateStatus("Ping Failed!");
            hook.updateProgress(0);
        }
        pingSock.close(); //Close the socket when we are done
        return result; //Return the result
    }

    /**
     * Gets basic data about the server in question, currently camera size
     * @param address The address to connect to
     * @param port The port to connect on
     * @return A map containing string-keyed data
     */
    public static HashMap<String, Integer> getBasicData(String address, int port) {
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket initSock = context.socket(ZMQ.REP);
        initSock.connect("tcp://" + address + ":" + port);
        initSock.send(Request.INIT.toString());
        String[] respData = initSock.recvStr().split(",");
        initSock.close();
        HashMap<String, Integer> returnMap = new HashMap<>();
        returnMap.put("width", Integer.parseInt(respData[0]));
        returnMap.put("height", Integer.parseInt(respData[1]));
        return returnMap;
    }
}
