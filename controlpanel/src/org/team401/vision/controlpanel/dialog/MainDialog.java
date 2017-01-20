package org.team401.vision.controlpanel.dialog;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MainDialog extends JDialog {
    private JPanel contentPane;
    private JButton buttonOK;
    private JButton buttonCancel;
    private JLabel imageLabel;
    private JSlider exposureSlider;
    private JSpinner exposureSpinner;
    private JComboBox cameraSelector;

    private ResponseHook primaryUpdateHook;

    public MainDialog(int width, int height) {
        setContentPane(contentPane);
        setModal(true);
        getRootPane().setDefaultButton(buttonOK);

        buttonOK.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onOK();
            }
        });

        buttonCancel.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onCancel();
            }
        });

        // call onCancel() when cross is clicked
        setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                onCancel();
            }
        });

        // call onCancel() on ESCAPE
        contentPane.registerKeyboardAction(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onCancel();
            }
        }, KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);

        Dimension dimension = new Dimension(width, height);
        imageLabel.setMinimumSize(dimension); //Enforce that the image display label is set to the correct size
        imageLabel.setMaximumSize(dimension);
        imageLabel.setPreferredSize(dimension);

        LinkedControlGroup exposureGroup = new LinkedControlGroup(exposureSlider, exposureSpinner, 0, 255, 30);

        primaryUpdateHook = new ResponseHook(exposureGroup);
    }

    public void build() {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                pack();
                setVisible(true);
            }
        });
    }

    public ResponseHook getPrimaryUpdateHook() {
        return primaryUpdateHook;
    }

    private void onOK() {
        // add your code here
        dispose();
    }

    private void onCancel() {
        // add your code here if necessary
        dispose();
        System.exit(0xDEADBEEF); //Rip Control Panel :(
    }
}
