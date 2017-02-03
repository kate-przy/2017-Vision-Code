package org.team401.vision.controlpanel.dialog;

import javax.swing.*;

/**
 * Wrapper for setting progress from other threads
 */
public class PingerUpdateHook {
    private JLabel statusLabel;
    private JProgressBar progressBar;
    PingerUpdateHook(JLabel statusLabel, JProgressBar progressBar) {
        this.statusLabel = statusLabel;
        this.progressBar = progressBar;
    }

    public void updateStatus(String newStatus) {
        statusLabel.setText("Status: " + newStatus);
    }

    public void updateProgress(int newProgress) {
        if (newProgress >= 0 || newProgress <= 100) {
            progressBar.setValue(newProgress);
        }
    }

    public void setIndeterminate(boolean newValue) {
        progressBar.setIndeterminate(newValue);
    }
}
