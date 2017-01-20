package org.team401.vision.controlpanel;

import org.team401.vision.controlpanel.dialog.AddressEntryDialog;
import org.team401.vision.controlpanel.dialog.ConnectingDialog;
import org.team401.vision.controlpanel.dialog.MainDialog;
import org.team401.vision.controlpanel.network.ControlSocket;
import org.team401.vision.controlpanel.network.ImageStreamSocket;
import org.team401.vision.controlpanel.network.Pinger;
import org.zeromq.ZMQ;

import java.util.HashMap;

/**
 * came20's 2017-Vision-Code
 * Copyright (C) 2017 came20 (http://came20.net)
 * License information can be found in the "LICENSE" file,
 * found inside this package.  Should a "LICENSE" file not
 * be present, it is most likely not an official package,
 * released by myself (came20), and should be used with caution
 */
public class ControlPanel {
    //DEFAULT ADDRESS OF JETSON
    private static final String defaultAddress = "127.0.0.1";
    private static final int defaultPort = 5800;
    private static String address;
    private static int port;

    public static void main(String[] args) {
        ConnectingDialog defaultConnectDialog = new ConnectingDialog(defaultAddress, defaultPort); //Set up the default connect dialog
        defaultConnectDialog.build();
        try {
            Thread.sleep(5000); //Give the window some time to appear
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Attempting to connect to default server [" + defaultAddress + ":" + defaultPort + "]");
        boolean defaultPing = Pinger.ping(defaultAddress, defaultPort, 10000, defaultConnectDialog.getPingerUpdateHook());
        try {
            Thread.sleep(5000); //Give the user some time to see the output
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        defaultConnectDialog.dispose();
        if (defaultPing) { //If the ping passed
            address = defaultAddress;
            port = defaultPort;
        } else { //The ping failed
            String lastAddress = defaultAddress;
            int lastPort = defaultPort;
            while (true) { //Keep doing this until it works
                AddressEntryDialog fallbackAddressEntryDialog = new AddressEntryDialog(lastAddress + ":" + lastPort);
                fallbackAddressEntryDialog.build();
                String fallBackAddressRaw = fallbackAddressEntryDialog.getAddress();
                String[] fallBackAddressList = fallBackAddressRaw.split(":"); //Split on the : to get the address and port
                if (fallBackAddressList.length != 2) { //If the address is not the correct length
                    System.out.println("Invalid address [" + fallBackAddressRaw + "], try again");
                    continue;
                }
                String fallbackAddress = fallBackAddressList[0];
                int fallbackPort = Integer.parseInt(fallBackAddressList[1]);
                ConnectingDialog fallbackConnectDialog = new ConnectingDialog(fallbackAddress, fallbackPort);
                fallbackConnectDialog.build();
                try {
                    Thread.sleep(5000); //Give the dialog time to open
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println("Attempting to connect to fallback server [" + fallbackAddress + ":" + fallbackPort + "]");
                boolean fallbackPing = Pinger.ping(fallbackAddress, fallbackPort, 10000, fallbackConnectDialog.getPingerUpdateHook()); //Ping the new address
                try {
                    Thread.sleep(5000); //Give the user some time to see the output
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                fallbackConnectDialog.dispose();
                if (fallbackPing) { //If the ping passed
                    address = fallbackAddress;
                    port = fallbackPort;
                    break;
                }
                //The ping failed, we try again
                lastAddress = fallbackAddress; //Set the last address and port so that the dialog can show which ping failed
                lastPort = fallbackPort;
            }
        }
        int cameraWidth, cameraHeight;
        HashMap<String, Integer> initData = Pinger.getBasicData(address, port); //Get the camera width and height from the server to initialize our window
        cameraWidth = initData.getOrDefault("width", 640);
        cameraHeight = initData.getOrDefault("height", 480);

        MainDialog mainDialog = new MainDialog(cameraWidth, cameraHeight);
        mainDialog.build();

    }
}
