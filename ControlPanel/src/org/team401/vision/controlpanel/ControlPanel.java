package org.team401.vision.controlpanel;

import com.alee.laf.WebLookAndFeel;
import org.team401.vision.controller.VisionController;
import org.team401.vision.controlpanel.dialog.MainDialog;
import org.zeromq.ZMQ;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.io.ByteArrayInputStream;

/**
 * Created by cameronearle on 3/1/17.
 */
public class ControlPanel {
    public static void main(String[] args) {
        String address = "127.0.0.1";
        int port = 5800;

        if (args.length == 1) { //We have a custom address
            address = args[0]; //Set the address
        }
        if (args.length > 1) { //We have a custom port
            try {
                port = Integer.valueOf(args[1]); //Set port
            } catch (Exception e) {}
        }

        VisionController controller = new VisionController(address, port + 3); //Set up the controller
        controller.start(); //Start the controller

        WebLookAndFeel.install(); //Set up the WebLAF
        MainDialog mainDialog = new MainDialog(controller); //Set up the main dialog

        SwingUtilities.invokeLater(() -> {
            mainDialog.pack(); //Render the dialog
            mainDialog.setVisible(true); //Make the dialog visible
        });

    }
}
