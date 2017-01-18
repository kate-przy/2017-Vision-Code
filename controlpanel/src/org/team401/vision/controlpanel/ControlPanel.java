package org.team401.vision.controlpanel;

import org.team401.vision.controlpanel.dialog.AddressEntryDialog;
import org.team401.vision.controlpanel.dialog.ConnectingDialog;
import org.zeromq.ZMQ;

/**
 * came20's 2017-Vision-Code
 * Copyright (C) 2017 came20 (http://came20.net)
 * License information can be found in the "LICENSE" file,
 * found inside this package.  Should a "LICENSE" file not
 * be present, it is most likely not an official package,
 * released by myself (came20), and should be used with caution
 */
public class ControlPanel {
    public static void main(String[] args) {
        ConnectingDialog addressEntryDialog = new ConnectingDialog();
        addressEntryDialog.setProgressIndeterminate(true);
        addressEntryDialog.pack();
        addressEntryDialog.setVisible(true);
    }
}
