package org.team401.vision.controlpanel.dialog;

import javax.swing.*;
import java.awt.event.*;

public class ConnectingDialog extends JDialog {
    private JPanel contentPane;
    private JLabel addressLabel;
    private JProgressBar progressBar;
    private JLabel statusLabel;

    public ConnectingDialog() {
        setContentPane(contentPane);
        setModal(true);
    }

    public void setProgress(int progress) {
        if (progress >= 0 && progress <= 100) { //If the progress given is a valid percentage
            progressBar.setValue(progress);
        }
    }

    public void setProgressIndeterminate(boolean value) {
        progressBar.setIndeterminate(value);
    }
}
