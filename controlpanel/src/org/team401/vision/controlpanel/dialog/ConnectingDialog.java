package org.team401.vision.controlpanel.dialog;

import javax.swing.*;
import java.awt.event.*;

public class ConnectingDialog extends JDialog {
    private JPanel contentPane;
    private JLabel addressLabel;
    private JProgressBar progressBar;
    private JLabel statusLabel;


    private PingerUpdateHook pingerUpdateHook;

    public ConnectingDialog(String address, int port) {
        setContentPane(contentPane);
        setModal(true);
        addressLabel.setText(address + ":" + port); //Set the address label
        pingerUpdateHook = new PingerUpdateHook(statusLabel, progressBar); //Initialize the update hook
    }

    /**
     * Builds and displays the current instance of this dialog
     */
    public void build() {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                pack();
                setVisible(true);
            }
        });
    }

    public PingerUpdateHook getPingerUpdateHook() {
        return pingerUpdateHook;
    }

    public void setProgress(int progress) {
        if (progress >= 0 && progress <= 100) { //If the progress given is a valid percentage
            progressBar.setValue(progress);
        }
    }

    public void setProgressIndeterminate(boolean value) {
        progressBar.setIndeterminate(value);
    }

    public void setStatus(String status) {
        statusLabel.setText("Status: " + status); //Update the value label
    }
}
