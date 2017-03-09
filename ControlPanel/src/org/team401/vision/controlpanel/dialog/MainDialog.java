package org.team401.vision.controlpanel.dialog;

import com.alee.extended.colorchooser.WebColorChooserField;
import org.team401.vision.controller.NetworkData;
import org.team401.vision.controller.VisionController;
import org.team401.vision.controlpanel.dialog.component.LinkedControlGroup;

import javax.swing.*;
import java.awt.event.*;
import java.text.NumberFormat;
import java.util.EventObject;

public class MainDialog extends JDialog {
    private VisionController controller;

    private JPanel contentPane;
    private JButton saveButton;
    private JButton buttonCancel;
    private JLabel imageLabel;
    private JTabbedPane selectorPane;
    private JPanel goalCameraProcSettingsPanel;
    private JSpinner goalCameraProcBrightnessSpinner;
    private JSlider goalCameraProcBrightnessSlider;
    private JSpinner goalCameraProcContrastSpinner;
    private JSlider goalCameraProcContrastSlider;
    private JSpinner goalCameraProcSaturationSpinner;
    private JSlider goalCameraProcSaturationSlider;
    private JSpinner goalCameraProcHueSpinner;
    private JSlider goalCameraProcHueSlider;
    private JSpinner goalCameraProcExposureSpinner;
    private JSlider goalCameraProcExposureSlider;
    private JSpinner goalCameraProcGainSpinner;
    private JSlider goalCameraProcGainSlider;
    private JCheckBox goalCameraProcAutoWBCheckbox;
    private JCheckBox goalCameraProcAutoGainCheckbox;
    private JCheckBox goalCameraProcVFlipCheckbox;
    private JCheckBox goalCameraProcHFlipCheckbox;
    private JCheckBox goalCameraProcManualExposureCheckbox;
    private JPanel goalProcSettingsPanel;
    private JSpinner goalProcMinAreaSpinner;
    private JSpinner goalProcMinPerimeterSpinner;
    private JFormattedTextField goalProcMinWidthTextfield;
    private JFormattedTextField goalProcMinHeightTextfield;
    private JFormattedTextField goalProcMinSolidityTextfield;
    private JFormattedTextField goalProcMinVerticesTextfield;
    private JFormattedTextField goalProcMinRatioTextfield;
    private JFormattedTextField goalProcMaxWidthTextfield;
    private JFormattedTextField goalProcMaxHeightTextfield;
    private JFormattedTextField goalProcMaxSolidityTextfield;
    private JFormattedTextField goalProcMaxVerticesTextfield;
    private JFormattedTextField goalProcMaxRatioTextfield;
    private JButton freezeStreamButton;
    private JSpinner gearCameraBrightnessSpinner;
    private JSpinner gearCameraContrastSpinner;
    private JSpinner gearCameraSaturationSpinner;
    private JSpinner gearCameraHueSpinner;
    private JSpinner gearCameraExposureSpinner;
    private JSpinner gearCameraGainSpinner;
    private JSlider gearCameraBrightnessSlider;
    private JSlider gearCameraContrastSlider;
    private JSlider gearCameraSaturationSlider;
    private JSlider gearCameraHueSlider;
    private JSlider gearCameraExposureSlider;
    private JSlider gearCameraGainSlider;
    private JCheckBox gearCameraAutoWBCheckbox;
    private JCheckBox gearCameraAutoGainCheckbox;
    private JCheckBox gearCameraVFlipCheckbox;
    private JCheckBox gearCameraHFlipCheckbox;
    private JCheckBox gearCameraManualExposureCheckbox;
    private WebColorChooserField gearProcLowerColor;
    private WebColorChooserField gearProcUpperColor;
    private JSpinner gearProcMinAreaSpinner;
    private JSpinner gearProcMinPerimeterSpinner;
    private JFormattedTextField gearProcMinWidthTextfield;
    private JFormattedTextField gearProcMaxWidthTextfield;
    private JFormattedTextField gearProcMinHeightTextfield;
    private JFormattedTextField gearProcMaxHeightTextfield;
    private JFormattedTextField gearProcMinSolidityTextfield;
    private JFormattedTextField gearProcMaxSolidityTextfield;
    private JFormattedTextField gearProcMinVerticesTextfield;
    private JFormattedTextField gearProcMaxVerticesTextfield;
    private JFormattedTextField gearProcMinRatioTextfield;
    private JFormattedTextField gearProcMaxRatioTextfield;
    private JButton resetButton;
    private JSpinner streamCompressionSpinner;
    private JSlider streamCompressionSlider;
    private JButton offButton;
    private JButton goalButton;
    private JButton gearButton;
    private JButton streamerQualityApplyButton;
    private JLabel streamWarningLabel;
    private JButton goalProcLowerColorApplyButton;
    private JButton goalProcUpperColorApplyButton;
    private WebColorChooserField goalProcColorLower;
    private WebColorChooserField goalProcColorUpper;
    private JTabbedPane goalCameraSelectorPane;
    private JPanel goalCameraStreamSettingsPanel;
    private JSpinner goalCameraStreamBrightnessSpinner;
    private JSpinner goalCameraStreamContrastSpinner;
    private JSpinner goalCameraStreamSaturationSpinner;
    private JSpinner goalCameraStreamHueSpinner;
    private JSpinner goalCameraStreamExposureSpinner;
    private JSpinner goalCameraStreamGainSpinner;
    private JSlider goalCameraStreamBrightnessSlider;
    private JSlider goalCameraStreamContrastSlider;
    private JSlider goalCameraStreamSaturationSlider;
    private JSlider goalCameraStreamHueSlider;
    private JSlider goalCameraStreamExposureSlider;
    private JSlider goalCameraStreamGainSlider;
    private JCheckBox goalCameraStreamAutoWBCheckbox;
    private JCheckBox goalCameraStreamAutoGainCheckbox;
    private JCheckBox goalCameraStreamVFlipCheckbox;
    private JCheckBox goalCameraStreamHFlipCheckbox;
    private JCheckBox goalCameraStreamManualExposureCheckbox;
    private JButton refreshButton;
    private JTabbedPane gearCameraSelectorPane;

    private LinkedControlGroup goalCameraProcBrightnessGroup;
    private LinkedControlGroup goalCameraProcContrastGroup;
    private LinkedControlGroup goalCameraProcSaturationGroup;
    private LinkedControlGroup goalCameraProcHueGroup;
    private LinkedControlGroup goalCameraProcExposureGroup;
    private LinkedControlGroup goalCameraProcGainGroup;

    private LinkedControlGroup gearCameraProcBrightnessGroup;
    private LinkedControlGroup gearCameraProcContrastGroup;
    private LinkedControlGroup gearCameraProcSaturationGroup;
    private LinkedControlGroup gearCameraProcHueGroup;
    private LinkedControlGroup gearCameraProcExposureGroup;
    private LinkedControlGroup gearCameraProcGainGroup;

    private LinkedControlGroup goalCameraStreamBrightnessGroup;
    private LinkedControlGroup goalCameraStreamContrastGroup;
    private LinkedControlGroup goalCameraStreamSaturationGroup;
    private LinkedControlGroup goalCameraStreamHueGroup;
    private LinkedControlGroup goalCameraStreamExposureGroup;
    private LinkedControlGroup goalCameraStreamGainGroup;

    private LinkedControlGroup gearCameraStreamBrightnessGroup;
    private LinkedControlGroup gearCameraStreamContrastGroup;
    private LinkedControlGroup gearCameraStreamSaturationGroup;
    private LinkedControlGroup gearCameraStreamHueGroup;
    private LinkedControlGroup gearCameraStreamExposureGroup;
    private LinkedControlGroup gearCameraStreamGainGroup;

    private LinkedControlGroup streamCompressionGroup;

    public MainDialog(VisionController controller) {
        this.controller = controller;

        setContentPane(contentPane);
        setModal(true);
        getRootPane().setDefaultButton(saveButton);

        saveButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onSave();
            }
        });

        buttonCancel.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onCancel();
            }
        });

        //SET UP LINKED CONTROLS
        goalCameraProcBrightnessGroup = new LinkedControlGroup(goalCameraProcBrightnessSlider, goalCameraProcBrightnessSpinner, 0, 255, 0);
        goalCameraProcContrastGroup = new LinkedControlGroup(goalCameraProcContrastSlider, goalCameraProcContrastSpinner, 0, 255, 0);
        goalCameraProcSaturationGroup = new LinkedControlGroup(goalCameraProcSaturationSlider, goalCameraProcSaturationSpinner, 0, 255, 0);
        goalCameraProcHueGroup = new LinkedControlGroup(goalCameraProcHueSlider, goalCameraProcHueSpinner, 0, 255, 0);
        goalCameraProcExposureGroup = new LinkedControlGroup(goalCameraProcExposureSlider, goalCameraProcExposureSpinner, 0, 255, 0);
        goalCameraProcGainGroup = new LinkedControlGroup(goalCameraProcGainSlider, goalCameraProcGainSpinner, 0, 255, 0);

        goalCameraStreamBrightnessGroup = new LinkedControlGroup(goalCameraStreamBrightnessSlider, goalCameraStreamBrightnessSpinner, 0, 255, 0);
        goalCameraStreamContrastGroup = new LinkedControlGroup(goalCameraStreamContrastSlider, goalCameraStreamContrastSpinner, 0, 255, 0);
        goalCameraStreamSaturationGroup = new LinkedControlGroup(goalCameraStreamSaturationSlider, goalCameraStreamSaturationSpinner, 0, 255, 0);
        goalCameraStreamHueGroup = new LinkedControlGroup(goalCameraStreamHueSlider, goalCameraStreamHueSpinner, 0, 255, 0);
        goalCameraStreamExposureGroup = new LinkedControlGroup(goalCameraStreamExposureSlider, goalCameraStreamExposureSpinner, 0, 255, 0);
        goalCameraStreamGainGroup = new LinkedControlGroup(goalCameraStreamGainSlider, goalCameraStreamGainSpinner, 0, 255, 0);

        gearCameraProcBrightnessGroup = new LinkedControlGroup(gearCameraBrightnessSlider, gearCameraBrightnessSpinner, 0, 255, 0);
        gearCameraProcContrastGroup = new LinkedControlGroup(gearCameraContrastSlider, gearCameraContrastSpinner, 0, 255, 0);
        gearCameraProcSaturationGroup = new LinkedControlGroup(gearCameraSaturationSlider, gearCameraSaturationSpinner, 0, 255, 0);
        gearCameraProcHueGroup = new LinkedControlGroup(gearCameraHueSlider, gearCameraHueSpinner, 0, 255, 0);
        gearCameraProcExposureGroup = new LinkedControlGroup(gearCameraExposureSlider, gearCameraExposureSpinner, 0, 255, 0);
        gearCameraProcGainGroup = new LinkedControlGroup(gearCameraGainSlider, gearCameraGainSpinner, 0, 255, 0);

        streamCompressionGroup = new LinkedControlGroup(streamCompressionSlider, streamCompressionSpinner, 0, 100, 0);

        //ACTION BINDINGS
        resetButton.addActionListener(this::onReset);
        
        /*
        goalCameraBrightnessGroup.addChangeListener(this::onGoalCameraUpdate);
        goalCameraContrastGroup.addChangeListener(this::onGoalCameraUpdate);
        goalCameraSaturationGroup.addChangeListener(this::onGoalCameraUpdate);
        goalCameraHueGroup.addChangeListener(this::onGoalCameraUpdate);
        goalCameraExposureGroup.addChangeListener(this::onGoalCameraUpdate);
        goalCameraGainGroup.addChangeListener(this::onGoalCameraUpdate);
        */
        goalCameraProcAutoWBCheckbox.addActionListener(this::onGoalCameraUpdate);
        goalCameraProcAutoGainCheckbox.addActionListener(this::onGoalCameraUpdate);
        goalCameraProcVFlipCheckbox.addActionListener(this::onGoalCameraUpdate);
        goalCameraProcHFlipCheckbox.addActionListener(this::onGoalCameraUpdate);

        goalProcLowerColorApplyButton.addActionListener(this::onGoalProcUpdate);
        goalProcUpperColorApplyButton.addActionListener(this::onGoalProcUpdate);
        goalProcMinAreaSpinner.addChangeListener(this::onGoalProcUpdate);
        goalProcMinPerimeterSpinner.addChangeListener(this::onGoalProcUpdate);
        goalProcMinWidthTextfield.addActionListener(this::onGoalProcUpdate);
        goalProcMaxWidthTextfield.addActionListener(this::onGoalProcUpdate);
        goalProcMinHeightTextfield.addActionListener(this::onGoalProcUpdate);
        goalProcMaxHeightTextfield.addActionListener(this::onGoalProcUpdate);
        goalProcMinSolidityTextfield.addActionListener(this::onGoalProcUpdate);
        goalProcMaxSolidityTextfield.addActionListener(this::onGoalProcUpdate);
        goalProcMinVerticesTextfield.addActionListener(this::onGoalProcUpdate);
        goalProcMaxVerticesTextfield.addActionListener(this::onGoalProcUpdate);
        goalProcMinRatioTextfield.addActionListener(this::onGoalProcUpdate);
        goalProcMaxRatioTextfield.addActionListener(this::onGoalProcUpdate);

        streamCompressionGroup.addChangeListener(this::onStreamCompressionImmediateUpdate);
        streamerQualityApplyButton.addActionListener(this::onStreamCompressionApply);



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

        streamWarningLabel.setVisible(false);
    }

    private void onSave() {
        controller.request(new NetworkData("save")); //Send a save request
    }

    private void onCancel() {
        System.exit(0); //Close the program
    }

    //ACTION METHODS
    private void onReset(ActionEvent e) {
        System.out.println("TEST");
    }

    /**
     * Method called when any of the goal camera settings are changed
     * @param e
     */
    private void onGoalCameraUpdate(EventObject e) {
    }

    /**
     * Method called when any of the goal proc settings are change
     * @param e
     */
    private void onGoalProcUpdate(EventObject e) {
        System.out.println("PROC");
    }

    private void onStreamCompressionImmediateUpdate(EventObject e) {
        if (streamCompressionGroup.getValue() > 30) {
            streamWarningLabel.setVisible(true);
        } else {
            streamWarningLabel.setVisible(false);
        }
    }

    private void onStreamCompressionApply(EventObject e) {
        controller.setQuality(streamCompressionGroup.getValue());
    }

    private void createUIComponents() {
        NumberFormat nf = NumberFormat.getInstance();                //Initialize JFormattedTextFields to only hold numbers
        goalProcMinWidthTextfield = new JFormattedTextField(nf);
        goalProcMaxWidthTextfield = new JFormattedTextField(nf);
        goalProcMinHeightTextfield = new JFormattedTextField(nf);
        goalProcMaxHeightTextfield = new JFormattedTextField(nf);
        goalProcMinSolidityTextfield = new JFormattedTextField(nf);
        goalProcMaxSolidityTextfield = new JFormattedTextField(nf);
        goalProcMinVerticesTextfield = new JFormattedTextField(nf);
        goalProcMaxVerticesTextfield = new JFormattedTextField(nf);
        goalProcMinRatioTextfield = new JFormattedTextField(nf);
        goalProcMaxRatioTextfield = new JFormattedTextField(nf);

        gearProcMinWidthTextfield = new JFormattedTextField(nf);
        gearProcMaxWidthTextfield = new JFormattedTextField(nf);
        gearProcMinHeightTextfield = new JFormattedTextField(nf);
        gearProcMaxHeightTextfield = new JFormattedTextField(nf);
        gearProcMinSolidityTextfield = new JFormattedTextField(nf);
        gearProcMaxSolidityTextfield = new JFormattedTextField(nf);
        gearProcMinVerticesTextfield = new JFormattedTextField(nf);
        gearProcMaxVerticesTextfield = new JFormattedTextField(nf);
        gearProcMinRatioTextfield = new JFormattedTextField(nf);
        gearProcMaxRatioTextfield = new JFormattedTextField(nf);
    }
}
