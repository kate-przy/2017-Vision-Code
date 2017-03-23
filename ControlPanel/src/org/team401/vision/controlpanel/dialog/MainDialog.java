package org.team401.vision.controlpanel.dialog;

import com.alee.extended.colorchooser.WebColorChooserField;
import com.alee.extended.panel.WebButtonGroup;
import com.alee.laf.button.WebButton;
import org.team401.vision.controller.NetworkData;
import org.team401.vision.controller.VisionController;
import org.team401.vision.controlpanel.dialog.component.LinkedControlGroup;
import org.team401.vision.controlpanel.stream.StreamListener;
import org.team401.vision.controlpanel.update.ColorConverter;
import org.team401.vision.controlpanel.update.UpdateGroup;
import org.team401.vision.controlpanel.update.UpdateManager;
import org.team401.vision.controlpanel.update.UpdatePair;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.text.NumberFormat;
import java.util.EventObject;

public class MainDialog extends JDialog {
    private VisionController controller;
    private StreamListener streamListener;

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
    private JSpinner goalProcMinAreaSpinner;
    private JSpinner goalProcMinPerimeterSpinner;
    private JButton freezeStreamButton;
    private JSpinner gearCameraProcBrightnessSpinner;
    private JSpinner gearCameraProcContrastSpinner;
    private JSpinner gearCameraProcSaturationSpinner;
    private JSpinner gearCameraProcHueSpinner;
    private JSpinner gearCameraProcExposureSpinner;
    private JSpinner gearCameraProcGainSpinner;
    private JSlider gearCameraProcBrightnessSlider;
    private JSlider gearCameraProcContrastSlider;
    private JSlider gearCameraProcSaturationSlider;
    private JSlider gearCameraProcHueSlider;
    private JSlider gearCameraProcExposureSlider;
    private JSlider gearCameraProcGainSlider;
    private JCheckBox gearCameraProcAutoWBCheckbox;
    private JCheckBox gearCameraProcAutoGainCheckbox;
    private JCheckBox gearCameraProcVFlipCheckbox;
    private JCheckBox gearCameraProcHFlipCheckbox;
    private JCheckBox gearCameraProcManualExposureCheckbox;
    private JSpinner gearProcMinAreaSpinner;
    private JSpinner gearProcMinPerimeterSpinner;
    private JButton resetButton;
    private JSpinner streamCompressionSpinner;
    private JSlider streamCompressionSlider;
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
    private JSpinner gearCameraStreamBrightnessSpinner;
    private JSpinner gearCameraStreamContrastSpinner;
    private JSpinner gearCameraStreamSaturationSpinner;
    private JSpinner gearCameraStreamHueSpinner;
    private JSpinner gearCameraStreamExposureSpinner;
    private JSpinner gearCameraStreamGainSpinner;
    private JCheckBox gearCameraStreamAutoWBCheckbox;
    private JCheckBox gearCameraStreamAutoGainCheckbox;
    private JCheckBox gearCameraStreamVFlipCheckbox;
    private JCheckBox gearCameraStreamHFlipCheckbox;
    private JCheckBox gearCameraStreamManualExposureCheckbox;
    private JSlider gearCameraStreamBrightnessSlider;
    private JSlider gearCameraStreamContrastSlider;
    private JSlider gearCameraStreamSaturationSlider;
    private JSlider gearCameraStreamHueSlider;
    private JSlider gearCameraStreamExposureSlider;
    private JSlider gearCameraStreamGainSlider;
    private JButton gearProcLowerColorApplyButton;
    private JButton gearProcUpperColorApplyButton;
    private WebColorChooserField gearProcColorLower;
    private WebColorChooserField gearProcColorUpper;


    private WebButtonGroup goalCameraModeButtonGroup;
    private WebButtonGroup gearCameraModeButtonGroup;
    private WebButtonGroup activeCameraButtonGroup;
    private JSpinner gearProcMinWidthSpinner;
    private JSpinner gearProcMinHeightSpinner;
    private JSpinner gearProcMinSoliditySpinner;
    private JSpinner gearProcMinVerticesSpinner;
    private JSpinner gearProcMinRatioSpinner;
    private JSpinner gearProcMaxWidthSpinner;
    private JSpinner gearProcMaxHeightSpinner;
    private JSpinner gearProcMaxSoliditySpinner;
    private JSpinner gearProcMaxVerticesSpinner;
    private JSpinner gearProcMaxRatioSpinner;
    private JSpinner goalProcMinWidthSpinner;
    private JSpinner goalProcMinHeightSpinner;
    private JSpinner goalProcMinSoliditySpinner;
    private JSpinner goalProcMinVerticesSpinner;
    private JSpinner goalProcMinRatioSpinner;
    private JSpinner goalProcMaxWidthSpinner;
    private JSpinner goalProcMaxHeightSpinner;
    private JSpinner goalProcMaxSoliditySpinner;
    private JSpinner goalProcMaxVerticesSpinner;
    private JSpinner goalProcMaxRatioSpinner;

    private WebButton activeCameraOffButton;
    private WebButton activeCameraGoalButton;
    private WebButton activeCameraGearButton;

    private WebButton goalCameraProcModeButton;
    private WebButton goalCameraStreamModeButton;
    private WebButton gearCameraProcModeButton;
    private WebButton gearCameraStreamModeButton;

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
    
    private UpdatePair goalProcColorLowerHUpdatePair;
    private UpdatePair goalProcColorLowerSUpdatePair;
    private UpdatePair goalProcColorLowerVUpdatePair;
    private UpdatePair goalProcColorUpperHUpdatePair;
    private UpdatePair goalProcColorUpperSUpdatePair;
    private UpdatePair goalProcColorUpperVUpdatePair;
    private UpdatePair gearProcColorLowerHUpdatePair;
    private UpdatePair gearProcColorLowerSUpdatePair;
    private UpdatePair gearProcColorLowerVUpdatePair;
    private UpdatePair gearProcColorUpperHUpdatePair;
    private UpdatePair gearProcColorUpperSUpdatePair;
    private UpdatePair gearProcColorUpperVUpdatePair;

    private UpdateManager updateManager;
    
    public MainDialog(VisionController controller, StreamListener streamListener) {
        this.controller = controller;
        this.streamListener = streamListener;

        setContentPane(contentPane);
        setModal(true);
        getRootPane().setDefaultButton(saveButton);

        // call onCancel() when cross is clicked
        setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                onQuit();
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

        gearCameraProcBrightnessGroup = new LinkedControlGroup(gearCameraProcBrightnessSlider, gearCameraProcBrightnessSpinner, 0, 255, 0);
        gearCameraProcContrastGroup = new LinkedControlGroup(gearCameraProcContrastSlider, gearCameraProcContrastSpinner, 0, 255, 0);
        gearCameraProcSaturationGroup = new LinkedControlGroup(gearCameraProcSaturationSlider, gearCameraProcSaturationSpinner, 0, 255, 0);
        gearCameraProcHueGroup = new LinkedControlGroup(gearCameraProcHueSlider, gearCameraProcHueSpinner, 0, 255, 0);
        gearCameraProcExposureGroup = new LinkedControlGroup(gearCameraProcExposureSlider, gearCameraProcExposureSpinner, 0, 255, 0);
        gearCameraProcGainGroup = new LinkedControlGroup(gearCameraProcGainSlider, gearCameraProcGainSpinner, 0, 255, 0);

        gearCameraStreamBrightnessGroup = new LinkedControlGroup(gearCameraStreamBrightnessSlider, gearCameraStreamBrightnessSpinner, 0, 255, 0);
        gearCameraStreamContrastGroup = new LinkedControlGroup(gearCameraStreamContrastSlider, gearCameraStreamContrastSpinner, 0, 255, 0);
        gearCameraStreamSaturationGroup = new LinkedControlGroup(gearCameraStreamSaturationSlider, gearCameraStreamSaturationSpinner, 0, 255, 0);
        gearCameraStreamHueGroup = new LinkedControlGroup(gearCameraStreamHueSlider, gearCameraStreamHueSpinner, 0, 255, 0);
        gearCameraStreamExposureGroup = new LinkedControlGroup(gearCameraStreamExposureSlider, gearCameraStreamExposureSpinner, 0, 255, 0);
        gearCameraStreamGainGroup = new LinkedControlGroup(gearCameraStreamGainSlider, gearCameraStreamGainSpinner, 0, 255, 0);

        streamCompressionGroup = new LinkedControlGroup(streamCompressionSlider, streamCompressionSpinner, 0, 100, 0);

        //SET UP UPDATE PAIRS
        UpdatePair goalCameraProcBrightnessUpdatePair = new UpdatePair("goalProcCameraBrightness", 0, goalCameraProcBrightnessGroup::getValue, (Object o) -> goalCameraProcBrightnessGroup.setValue((Integer) o), Integer.class);
        UpdatePair goalCameraProcContrastUpdatePair = new UpdatePair("goalProcCameraContrast", 0, goalCameraProcContrastGroup::getValue, (Object o) -> goalCameraProcContrastGroup.setValue((Integer) o), Integer.class);
        UpdatePair goalCameraProcSaturationUpdatePair = new UpdatePair("goalProcCameraSaturation", 0, goalCameraProcSaturationGroup::getValue, (Object o) -> goalCameraProcSaturationGroup.setValue((Integer) o), Integer.class);
        UpdatePair goalCameraProcHueUpdatePair = new UpdatePair("goalProcCameraHue", 0, goalCameraProcHueGroup::getValue, (Object o) -> goalCameraProcHueGroup.setValue((Integer) o), Integer.class);
        UpdatePair goalCameraProcExposureUpdatePair = new UpdatePair("goalProcCameraExposure", 0, goalCameraProcExposureGroup::getValue, (Object o) -> goalCameraProcExposureGroup.setValue((Integer) o), Integer.class);
        UpdatePair goalCameraProcGainUpdatePair = new UpdatePair("goalProcCameraGain", 0, goalCameraProcGainGroup::getValue, (Object o) -> goalCameraProcGainGroup.setValue((Integer) o), Integer.class);
        UpdatePair gearCameraProcBrightnessUpdatePair = new UpdatePair("gearProcCameraBrightness", 0, gearCameraProcBrightnessGroup::getValue, (Object o) -> gearCameraProcBrightnessGroup.setValue((Integer) o), Integer.class);
        UpdatePair gearCameraProcContrastUpdatePair = new UpdatePair("gearProcCameraContrast", 0, gearCameraProcContrastGroup::getValue, (Object o) -> gearCameraProcContrastGroup.setValue((Integer) o), Integer.class);
        UpdatePair gearCameraProcSaturationUpdatePair = new UpdatePair("gearProcCameraSaturation", 0, gearCameraProcSaturationGroup::getValue, (Object o) -> gearCameraProcSaturationGroup.setValue((Integer) o), Integer.class);
        UpdatePair gearCameraProcHueUpdatePair = new UpdatePair("gearProcCameraHue", 0, gearCameraProcHueGroup::getValue, (Object o) -> gearCameraProcHueGroup.setValue((Integer) o), Integer.class);
        UpdatePair gearCameraProcExposureUpdatePair = new UpdatePair("gearProcCameraExposure", 0, gearCameraProcExposureGroup::getValue, (Object o) -> gearCameraProcExposureGroup.setValue((Integer) o), Integer.class);
        UpdatePair gearCameraProcGainUpdatePair = new UpdatePair("gearProcCameraGain", 0, gearCameraProcGainGroup::getValue, (Object o) -> gearCameraProcGainGroup.setValue((Integer) o), Integer.class);
        UpdatePair goalCameraStreamBrightnessUpdatePair = new UpdatePair("goalStreamCameraBrightness", 0, goalCameraStreamBrightnessGroup::getValue, (Object o) -> goalCameraStreamBrightnessGroup.setValue((Integer) o), Integer.class);
        UpdatePair goalCameraStreamContrastUpdatePair = new UpdatePair("goalStreamCameraContrast", 0, goalCameraStreamContrastGroup::getValue, (Object o) -> goalCameraStreamContrastGroup.setValue((Integer) o), Integer.class);
        UpdatePair goalCameraStreamSaturationUpdatePair = new UpdatePair("goalStreamCameraSaturation", 0, goalCameraStreamSaturationGroup::getValue, (Object o) -> goalCameraStreamSaturationGroup.setValue((Integer) o), Integer.class);
        UpdatePair goalCameraStreamHueUpdatePair = new UpdatePair("goalStreamCameraHue", 0, goalCameraStreamHueGroup::getValue, (Object o) -> goalCameraStreamHueGroup.setValue((Integer) o), Integer.class);
        UpdatePair goalCameraStreamExposureUpdatePair = new UpdatePair("goalStreamCameraExposure", 0, goalCameraStreamExposureGroup::getValue, (Object o) -> goalCameraStreamExposureGroup.setValue((Integer) o), Integer.class);
        UpdatePair goalCameraStreamGainUpdatePair = new UpdatePair("goalStreamCameraGain", 0, goalCameraStreamGainGroup::getValue, (Object o) -> goalCameraStreamGainGroup.setValue((Integer) o), Integer.class);
        UpdatePair gearCameraStreamBrightnessUpdatePair = new UpdatePair("gearStreamCameraBrightness", 0, gearCameraStreamBrightnessGroup::getValue, (Object o) -> gearCameraStreamBrightnessGroup.setValue((Integer) o), Integer.class);
        UpdatePair gearCameraStreamContrastUpdatePair = new UpdatePair("gearStreamCameraContrast", 0, gearCameraStreamContrastGroup::getValue, (Object o) -> gearCameraStreamContrastGroup.setValue((Integer) o), Integer.class);
        UpdatePair gearCameraStreamSaturationUpdatePair = new UpdatePair("gearStreamCameraSaturation", 0, gearCameraStreamSaturationGroup::getValue, (Object o) -> gearCameraStreamSaturationGroup.setValue((Integer) o), Integer.class);
        UpdatePair gearCameraStreamHueUpdatePair = new UpdatePair("gearStreamCameraHue", 0, gearCameraStreamHueGroup::getValue, (Object o) -> gearCameraStreamHueGroup.setValue((Integer) o), Integer.class);
        UpdatePair gearCameraStreamExposureUpdatePair = new UpdatePair("gearStreamCameraExposure", 0, gearCameraStreamExposureGroup::getValue, (Object o) -> gearCameraStreamExposureGroup.setValue((Integer) o), Integer.class);
        UpdatePair gearCameraStreamGainUpdatePair = new UpdatePair("gearStreamCameraGain", 0, gearCameraStreamGainGroup::getValue, (Object o) -> gearCameraStreamGainGroup.setValue((Integer) o), Integer.class);

        UpdatePair goalCameraProcAutoWBUpdatePair = new UpdatePair("goalProcCameraAutoWB", false, goalCameraProcAutoWBCheckbox::isSelected, (Object o) -> goalCameraProcAutoWBCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair goalCameraProcAutoGainUpdatePair = new UpdatePair("goalProcCameraAutoGain", false, goalCameraProcAutoGainCheckbox::isSelected, (Object o) -> goalCameraProcAutoGainCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair goalCameraProcVFlipUpdatePair = new UpdatePair("goalProcCameraVFlip", false, goalCameraProcVFlipCheckbox::isSelected, (Object o) -> goalCameraProcVFlipCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair goalCameraProcHFlipUpdatePair = new UpdatePair("goalProcCameraHFlip", false, goalCameraProcHFlipCheckbox::isSelected, (Object o) -> goalCameraProcHFlipCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair goalCameraProcManualExposureUpdatePair = new UpdatePair("goalProcCameraManualExposure", false, goalCameraProcManualExposureCheckbox::isSelected, (Object o) -> goalCameraProcManualExposureCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair gearCameraProcAutoWBUpdatePair = new UpdatePair("gearProcCameraAutoWB", false, gearCameraProcAutoWBCheckbox::isSelected, (Object o) -> gearCameraProcAutoWBCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair gearCameraProcAutoGainUpdatePair = new UpdatePair("gearProcCameraAutoGain", false, gearCameraProcAutoGainCheckbox::isSelected, (Object o) -> gearCameraProcAutoGainCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair gearCameraProcVFlipUpdatePair = new UpdatePair("gearProcCameraVFlip", false, gearCameraProcVFlipCheckbox::isSelected, (Object o) -> gearCameraProcVFlipCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair gearCameraProcHFlipUpdatePair = new UpdatePair("gearProcCameraHFlip", false, gearCameraProcHFlipCheckbox::isSelected, (Object o) -> gearCameraProcHFlipCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair gearCameraProcManualExposureUpdatePair = new UpdatePair("gearProcCameraManualExposure", false, gearCameraProcManualExposureCheckbox::isSelected, (Object o) -> gearCameraProcManualExposureCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair goalCameraStreamAutoWBUpdatePair = new UpdatePair("goalStreamCameraAutoWB", false, goalCameraStreamAutoWBCheckbox::isSelected, (Object o) -> goalCameraStreamAutoWBCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair goalCameraStreamAutoGainUpdatePair = new UpdatePair("goalStreamCameraAutoGain", false, goalCameraStreamAutoGainCheckbox::isSelected, (Object o) -> goalCameraStreamAutoGainCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair goalCameraStreamVFlipUpdatePair = new UpdatePair("goalStreamCameraVFlip", false, goalCameraStreamVFlipCheckbox::isSelected, (Object o) -> goalCameraStreamVFlipCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair goalCameraStreamHFlipUpdatePair = new UpdatePair("goalStreamCameraHFlip", false, goalCameraStreamHFlipCheckbox::isSelected, (Object o) -> goalCameraStreamHFlipCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair goalCameraStreamManualExposureUpdatePair = new UpdatePair("goalStreamCameraManualExposure", false, goalCameraStreamManualExposureCheckbox::isSelected, (Object o) -> goalCameraStreamManualExposureCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair gearCameraStreamAutoWBUpdatePair = new UpdatePair("gearStreamCameraAutoWB", false, gearCameraStreamAutoWBCheckbox::isSelected, (Object o) -> gearCameraStreamAutoWBCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair gearCameraStreamAutoGainUpdatePair = new UpdatePair("gearStreamCameraAutoGain", false, gearCameraStreamAutoGainCheckbox::isSelected, (Object o) -> gearCameraStreamAutoGainCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair gearCameraStreamVFlipUpdatePair = new UpdatePair("gearStreamCameraVFlip", false, gearCameraStreamVFlipCheckbox::isSelected, (Object o) -> gearCameraStreamVFlipCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair gearCameraStreamHFlipUpdatePair = new UpdatePair("gearStreamCameraHFlip", false, gearCameraStreamHFlipCheckbox::isSelected, (Object o) -> gearCameraStreamHFlipCheckbox.setSelected((Boolean) o), Boolean.class);
        UpdatePair gearCameraStreamManualExposureUpdatePair = new UpdatePair("gearStreamCameraManualExposure", false, gearCameraStreamManualExposureCheckbox::isSelected, (Object o) -> gearCameraStreamManualExposureCheckbox.setSelected((Boolean) o), Boolean.class);

        UpdatePair goalMinAreaUpdatePair = new UpdatePair("goalMinArea", 0d, goalProcMinAreaSpinner::getValue, goalProcMinAreaSpinner::setValue, Double.class);
        UpdatePair goalMinPerimeterUpdatePair = new UpdatePair("goalMinPerimeter", 0d, goalProcMinPerimeterSpinner::getValue, goalProcMinPerimeterSpinner::setValue, Double.class);
        UpdatePair goalMinWidthUpdatePair = new UpdatePair("goalMinWidth", 0d, goalProcMinWidthSpinner::getValue, goalProcMinWidthSpinner::setValue, Double.class);
        UpdatePair goalMinHeightUpdatePair = new UpdatePair("goalMinHeight", 0d, goalProcMinHeightSpinner::getValue, goalProcMinHeightSpinner::setValue, Double.class);
        UpdatePair goalMinSolidityUpdatePair = new UpdatePair("goalMinSolidity", 0d, goalProcMinSoliditySpinner::getValue, goalProcMinSoliditySpinner::setValue, Double.class);
        UpdatePair goalMinVerticesUpdatePair = new UpdatePair("goalMinVertices", 0d, goalProcMinVerticesSpinner::getValue, goalProcMinVerticesSpinner::setValue, Double.class);
        UpdatePair goalMinRatioUpdatePair = new UpdatePair("goalMinRatio", 0d, goalProcMinRatioSpinner::getValue, goalProcMinRatioSpinner::setValue, Double.class);
        UpdatePair goalMaxWidthUpdatePair = new UpdatePair("goalMaxWidth", 0d, goalProcMaxWidthSpinner::getValue, goalProcMaxWidthSpinner::setValue, Double.class);
        UpdatePair goalMaxHeightUpdatePair = new UpdatePair("goalMaxHeight", 0d, goalProcMaxHeightSpinner::getValue, goalProcMaxHeightSpinner::setValue, Double.class);
        UpdatePair goalMaxSolidityUpdatePair = new UpdatePair("goalMaxSolidity", 0d, goalProcMaxSoliditySpinner::getValue, goalProcMaxSoliditySpinner::setValue, Double.class);
        UpdatePair goalMaxVerticesUpdatePair = new UpdatePair("goalMaxVertices", 0d, goalProcMaxVerticesSpinner::getValue, goalProcMaxVerticesSpinner::setValue, Double.class);
        UpdatePair goalMaxRatioUpdatePair = new UpdatePair("goalMaxRatio", 0d, goalProcMaxRatioSpinner::getValue, goalProcMaxRatioSpinner::setValue, Double.class);
        UpdatePair gearMinAreaUpdatePair = new UpdatePair("gearMinArea", 0d, gearProcMinAreaSpinner::getValue, gearProcMinAreaSpinner::setValue, Double.class);
        UpdatePair gearMinPerimeterUpdatePair = new UpdatePair("gearMinPerimeter", 0d, gearProcMinPerimeterSpinner::getValue, gearProcMinPerimeterSpinner::setValue, Double.class);
        UpdatePair gearMinWidthUpdatePair = new UpdatePair("gearMinWidth", 0d, gearProcMinWidthSpinner::getValue, gearProcMinWidthSpinner::setValue, Double.class);
        UpdatePair gearMinHeightUpdatePair = new UpdatePair("gearMinHeight", 0d, gearProcMinHeightSpinner::getValue, gearProcMinHeightSpinner::setValue, Double.class);
        UpdatePair gearMinSolidityUpdatePair = new UpdatePair("gearMinSolidity", 0d, gearProcMinSoliditySpinner::getValue, gearProcMinSoliditySpinner::setValue, Double.class);
        UpdatePair gearMinVerticesUpdatePair = new UpdatePair("gearMinVertices", 0d, gearProcMinVerticesSpinner::getValue, gearProcMinVerticesSpinner::setValue, Double.class);
        UpdatePair gearMinRatioUpdatePair = new UpdatePair("gearMinRatio", 0d, gearProcMinRatioSpinner::getValue, gearProcMinRatioSpinner::setValue, Double.class);
        UpdatePair gearMaxWidthUpdatePair = new UpdatePair("gearMaxWidth", 0d, gearProcMaxWidthSpinner::getValue, gearProcMaxWidthSpinner::setValue, Double.class);
        UpdatePair gearMaxHeightUpdatePair = new UpdatePair("gearMaxHeight", 0d, gearProcMaxHeightSpinner::getValue, gearProcMaxHeightSpinner::setValue, Double.class);
        UpdatePair gearMaxSolidityUpdatePair = new UpdatePair("gearMaxSolidity", 0d, gearProcMaxSoliditySpinner::getValue, gearProcMaxSoliditySpinner::setValue, Double.class);
        UpdatePair gearMaxVerticesUpdatePair = new UpdatePair("gearMaxVertices", 0d, gearProcMaxVerticesSpinner::getValue, gearProcMaxVerticesSpinner::setValue, Double.class);
        UpdatePair gearMaxRatioUpdatePair = new UpdatePair("gearMaxRatio", 0d, gearProcMaxRatioSpinner::getValue, gearProcMaxRatioSpinner::setValue, Double.class);

        goalProcColorLowerHUpdatePair = new UpdatePair("goalProcHLower", 0, () -> new ColorConverter(goalProcColorLower.getColor()).getH(), (Object o) -> {
            ColorConverter converter = new ColorConverter(goalProcColorLower.getColor());
            int newH = (Integer) o;
            int newS = converter.getS();
            int newV = converter.getV();
            Color newColor = new ColorConverter(newH, newS, newV).getColor();
            goalProcColorLower.setColor(newColor);
        }, Integer.class);
        goalProcColorLowerSUpdatePair = new UpdatePair("goalProcSLower", 0, () -> new ColorConverter(goalProcColorLower.getColor()).getS(), (Object o) -> {
            ColorConverter converter = new ColorConverter(goalProcColorLower.getColor());
            int newH = converter.getH();
            int newS = (Integer) o;
            int newV = converter.getV();
            Color newColor = new ColorConverter(newH, newS, newV).getColor();
            goalProcColorLower.setColor(newColor);
        }, Integer.class);
        goalProcColorLowerVUpdatePair = new UpdatePair("goalProcVLower", 0, () -> new ColorConverter(goalProcColorLower.getColor()).getV(), (Object o) -> {
            ColorConverter converter = new ColorConverter(goalProcColorLower.getColor());
            int newH = converter.getH();
            int newS = converter.getS();
            int newV = (Integer) o;
            Color newColor = new ColorConverter(newH, newS, newV).getColor();
            goalProcColorLower.setColor(newColor);
        }, Integer.class);

        goalProcColorUpperHUpdatePair = new UpdatePair("goalProcHUpper", 0, () -> new ColorConverter(goalProcColorUpper.getColor()).getH(), (Object o) -> {
            ColorConverter converter = new ColorConverter(goalProcColorUpper.getColor());
            int newH = (Integer) o;
            int newS = converter.getS();
            int newV = converter.getV();
            Color newColor = new ColorConverter(newH, newS, newV).getColor();
            goalProcColorUpper.setColor(newColor);
        }, Integer.class);
        goalProcColorUpperSUpdatePair = new UpdatePair("goalProcSUpper", 0, () -> new ColorConverter(goalProcColorUpper.getColor()).getS(), (Object o) -> {
            ColorConverter converter = new ColorConverter(goalProcColorUpper.getColor());
            int newH = converter.getH();
            int newS = (Integer) o;
            int newV = converter.getV();
            Color newColor = new ColorConverter(newH, newS, newV).getColor();
            goalProcColorUpper.setColor(newColor);
        }, Integer.class);
        goalProcColorUpperVUpdatePair = new UpdatePair("goalProcVUpper", 0, () -> new ColorConverter(goalProcColorUpper.getColor()).getV(), (Object o) -> {
            ColorConverter converter = new ColorConverter(goalProcColorUpper.getColor());
            int newH = converter.getH();
            int newS = converter.getS();
            int newV = (Integer) o;
            Color newColor = new ColorConverter(newH, newS, newV).getColor();
            goalProcColorUpper.setColor(newColor);
        }, Integer.class);
        gearProcColorLowerHUpdatePair = new UpdatePair("gearProcHLower", 0, () -> new ColorConverter(gearProcColorLower.getColor()).getH(), (Object o) -> {
            ColorConverter converter = new ColorConverter(gearProcColorLower.getColor());
            int newH = (Integer) o;
            int newS = converter.getS();
            int newV = converter.getV();
            Color newColor = new ColorConverter(newH, newS, newV).getColor();
            gearProcColorLower.setColor(newColor);
        }, Integer.class);
        gearProcColorLowerSUpdatePair = new UpdatePair("gearProcSLower", 0, () -> new ColorConverter(gearProcColorLower.getColor()).getS(), (Object o) -> {
            ColorConverter converter = new ColorConverter(gearProcColorLower.getColor());
            int newH = converter.getH();
            int newS = (Integer) o;
            int newV = converter.getV();
            Color newColor = new ColorConverter(newH, newS, newV).getColor();
            gearProcColorLower.setColor(newColor);
        }, Integer.class);
        gearProcColorLowerVUpdatePair = new UpdatePair("gearProcVLower", 0, () -> new ColorConverter(gearProcColorLower.getColor()).getV(), (Object o) -> {
            ColorConverter converter = new ColorConverter(gearProcColorLower.getColor());
            int newH = converter.getH();
            int newS = converter.getS();
            int newV = (Integer) o;
            Color newColor = new ColorConverter(newH, newS, newV).getColor();
            gearProcColorLower.setColor(newColor);
        }, Integer.class);

        gearProcColorUpperHUpdatePair = new UpdatePair("gearProcHUpper", 0, () -> new ColorConverter(gearProcColorUpper.getColor()).getH(), (Object o) -> {
            ColorConverter converter = new ColorConverter(gearProcColorUpper.getColor());
            int newH = (Integer) o;
            int newS = converter.getS();
            int newV = converter.getV();
            Color newColor = new ColorConverter(newH, newS, newV).getColor();
            gearProcColorUpper.setColor(newColor);
        }, Integer.class);
        gearProcColorUpperSUpdatePair = new UpdatePair("gearProcSUpper", 0, () -> new ColorConverter(gearProcColorUpper.getColor()).getS(), (Object o) -> {
            ColorConverter converter = new ColorConverter(gearProcColorUpper.getColor());
            int newH = converter.getH();
            int newS = (Integer) o;
            int newV = converter.getV();
            Color newColor = new ColorConverter(newH, newS, newV).getColor();
            gearProcColorUpper.setColor(newColor);
        }, Integer.class);
        gearProcColorUpperVUpdatePair = new UpdatePair("gearProcVUpper", 0, () -> new ColorConverter(gearProcColorUpper.getColor()).getV(), (Object o) -> {
            ColorConverter converter = new ColorConverter(gearProcColorUpper.getColor());
            int newH = converter.getH();
            int newS = converter.getS();
            int newV = (Integer) o;
            Color newColor = new ColorConverter(newH, newS, newV).getColor();
            gearProcColorUpper.setColor(newColor);
        }, Integer.class);

        UpdatePair streamCompressionUpdatePair = new UpdatePair("streamCompression", 0, streamCompressionGroup::getValue, (Object o) -> streamCompressionGroup.setValue((Integer) o), Integer.class);
        


        //REGISTER COMPONENTS TO UPDATE PAIR EVENTS
        goalCameraProcBrightnessGroup.addChangeListener(goalCameraProcBrightnessUpdatePair::onUpdate);
        goalCameraProcContrastGroup.addChangeListener(goalCameraProcContrastUpdatePair::onUpdate);
        goalCameraProcSaturationGroup.addChangeListener(goalCameraProcSaturationUpdatePair::onUpdate);
        goalCameraProcHueGroup.addChangeListener(goalCameraProcHueUpdatePair::onUpdate);
        goalCameraProcExposureGroup.addChangeListener(goalCameraProcExposureUpdatePair::onUpdate);
        goalCameraProcGainGroup.addChangeListener(goalCameraProcGainUpdatePair::onUpdate);

        goalCameraStreamBrightnessGroup.addChangeListener(goalCameraStreamBrightnessUpdatePair::onUpdate);
        goalCameraStreamContrastGroup.addChangeListener(goalCameraStreamContrastUpdatePair::onUpdate);
        goalCameraStreamSaturationGroup.addChangeListener(goalCameraStreamSaturationUpdatePair::onUpdate);
        goalCameraStreamHueGroup.addChangeListener(goalCameraStreamHueUpdatePair::onUpdate);
        goalCameraStreamExposureGroup.addChangeListener(goalCameraStreamExposureUpdatePair::onUpdate);
        goalCameraStreamGainGroup.addChangeListener(goalCameraStreamGainUpdatePair::onUpdate);

        gearCameraProcBrightnessGroup.addChangeListener(gearCameraProcBrightnessUpdatePair::onUpdate);
        gearCameraProcContrastGroup.addChangeListener(gearCameraProcContrastUpdatePair::onUpdate);
        gearCameraProcSaturationGroup.addChangeListener(gearCameraProcSaturationUpdatePair::onUpdate);
        gearCameraProcHueGroup.addChangeListener(gearCameraProcHueUpdatePair::onUpdate);
        gearCameraProcExposureGroup.addChangeListener(gearCameraProcExposureUpdatePair::onUpdate);
        gearCameraProcGainGroup.addChangeListener(gearCameraProcGainUpdatePair::onUpdate);

        gearCameraStreamBrightnessGroup.addChangeListener(gearCameraStreamBrightnessUpdatePair::onUpdate);
        gearCameraStreamContrastGroup.addChangeListener(gearCameraStreamContrastUpdatePair::onUpdate);
        gearCameraStreamSaturationGroup.addChangeListener(gearCameraStreamSaturationUpdatePair::onUpdate);
        gearCameraStreamHueGroup.addChangeListener(gearCameraStreamHueUpdatePair::onUpdate);
        gearCameraStreamExposureGroup.addChangeListener(gearCameraStreamExposureUpdatePair::onUpdate);
        gearCameraStreamGainGroup.addChangeListener(gearCameraStreamGainUpdatePair::onUpdate);

        goalCameraProcAutoWBCheckbox.addActionListener(goalCameraProcAutoWBUpdatePair::onUpdate);
        goalCameraProcAutoGainCheckbox.addActionListener(goalCameraProcAutoGainUpdatePair::onUpdate);
        goalCameraProcVFlipCheckbox.addActionListener(goalCameraProcVFlipUpdatePair::onUpdate);
        goalCameraProcHFlipCheckbox.addActionListener(goalCameraProcHFlipUpdatePair::onUpdate);
        goalCameraProcManualExposureCheckbox.addActionListener(goalCameraProcManualExposureUpdatePair::onUpdate);

        goalCameraStreamAutoWBCheckbox.addActionListener(goalCameraStreamAutoWBUpdatePair::onUpdate);
        goalCameraStreamAutoGainCheckbox.addActionListener(goalCameraStreamAutoGainUpdatePair::onUpdate);
        goalCameraStreamVFlipCheckbox.addActionListener(goalCameraStreamVFlipUpdatePair::onUpdate);
        goalCameraStreamHFlipCheckbox.addActionListener(goalCameraStreamHFlipUpdatePair::onUpdate);
        goalCameraStreamManualExposureCheckbox.addActionListener(goalCameraStreamManualExposureUpdatePair::onUpdate);

        gearCameraProcAutoWBCheckbox.addActionListener(gearCameraProcAutoWBUpdatePair::onUpdate);
        gearCameraProcAutoGainCheckbox.addActionListener(gearCameraProcAutoGainUpdatePair::onUpdate);
        gearCameraProcVFlipCheckbox.addActionListener(gearCameraProcVFlipUpdatePair::onUpdate);
        gearCameraProcHFlipCheckbox.addActionListener(gearCameraProcHFlipUpdatePair::onUpdate);
        gearCameraProcManualExposureCheckbox.addActionListener(gearCameraProcManualExposureUpdatePair::onUpdate);

        gearCameraStreamAutoWBCheckbox.addActionListener(gearCameraStreamAutoWBUpdatePair::onUpdate);
        gearCameraStreamAutoGainCheckbox.addActionListener(gearCameraStreamAutoGainUpdatePair::onUpdate);
        gearCameraStreamVFlipCheckbox.addActionListener(gearCameraStreamVFlipUpdatePair::onUpdate);
        gearCameraStreamHFlipCheckbox.addActionListener(gearCameraStreamHFlipUpdatePair::onUpdate);
        gearCameraStreamManualExposureCheckbox.addActionListener(gearCameraStreamManualExposureUpdatePair::onUpdate);

        goalProcMinAreaSpinner.addChangeListener(goalMinAreaUpdatePair::onUpdate);
        goalProcMinPerimeterSpinner.addChangeListener(goalMinPerimeterUpdatePair::onUpdate);
        gearProcMinAreaSpinner.addChangeListener(gearMinAreaUpdatePair::onUpdate);
        gearProcMinPerimeterSpinner.addChangeListener(gearMinPerimeterUpdatePair::onUpdate);

        goalProcMinWidthSpinner.addChangeListener(goalMinWidthUpdatePair::onUpdate);
        goalProcMaxWidthSpinner.addChangeListener(goalMaxWidthUpdatePair::onUpdate);
        goalProcMinHeightSpinner.addChangeListener(goalMinHeightUpdatePair::onUpdate);
        goalProcMaxHeightSpinner.addChangeListener(goalMaxHeightUpdatePair::onUpdate);
        goalProcMinSoliditySpinner.addChangeListener(goalMinSolidityUpdatePair::onUpdate);
        goalProcMaxSoliditySpinner.addChangeListener(goalMaxSolidityUpdatePair::onUpdate);
        goalProcMinVerticesSpinner.addChangeListener(goalMinVerticesUpdatePair::onUpdate);
        goalProcMaxVerticesSpinner.addChangeListener(goalMaxVerticesUpdatePair::onUpdate);
        goalProcMinRatioSpinner.addChangeListener(goalMinRatioUpdatePair::onUpdate);
        goalProcMaxRatioSpinner.addChangeListener(goalMaxRatioUpdatePair::onUpdate);

        gearProcMinWidthSpinner.addChangeListener(gearMinWidthUpdatePair::onUpdate);
        gearProcMaxWidthSpinner.addChangeListener(gearMaxWidthUpdatePair::onUpdate);
        gearProcMinHeightSpinner.addChangeListener(gearMinHeightUpdatePair::onUpdate);
        gearProcMaxHeightSpinner.addChangeListener(gearMaxHeightUpdatePair::onUpdate);
        gearProcMinSoliditySpinner.addChangeListener(gearMinSolidityUpdatePair::onUpdate);
        gearProcMaxSoliditySpinner.addChangeListener(gearMaxSolidityUpdatePair::onUpdate);
        gearProcMinVerticesSpinner.addChangeListener(gearMinVerticesUpdatePair::onUpdate);
        gearProcMaxVerticesSpinner.addChangeListener(gearMaxVerticesUpdatePair::onUpdate);
        gearProcMinRatioSpinner.addChangeListener(gearMinRatioUpdatePair::onUpdate);
        gearProcMaxRatioSpinner.addChangeListener(gearMaxRatioUpdatePair::onUpdate);
        
        goalProcLowerColorApplyButton.addActionListener(goalProcColorLowerHUpdatePair::onUpdate);
        goalProcLowerColorApplyButton.addActionListener(goalProcColorLowerSUpdatePair::onUpdate);
        goalProcLowerColorApplyButton.addActionListener(goalProcColorLowerVUpdatePair::onUpdate);
        goalProcUpperColorApplyButton.addActionListener(goalProcColorUpperHUpdatePair::onUpdate);
        goalProcUpperColorApplyButton.addActionListener(goalProcColorUpperSUpdatePair::onUpdate);
        goalProcUpperColorApplyButton.addActionListener(goalProcColorUpperVUpdatePair::onUpdate);

        gearProcLowerColorApplyButton.addActionListener(gearProcColorLowerHUpdatePair::onUpdate);
        gearProcLowerColorApplyButton.addActionListener(gearProcColorLowerSUpdatePair::onUpdate);
        gearProcLowerColorApplyButton.addActionListener(gearProcColorLowerVUpdatePair::onUpdate);
        gearProcUpperColorApplyButton.addActionListener(gearProcColorUpperHUpdatePair::onUpdate);
        gearProcUpperColorApplyButton.addActionListener(gearProcColorUpperSUpdatePair::onUpdate);
        gearProcUpperColorApplyButton.addActionListener(gearProcColorUpperVUpdatePair::onUpdate);

        streamerQualityApplyButton.addActionListener(streamCompressionUpdatePair::onUpdate);

        UpdateGroup goalCameraProcGroup = new UpdateGroup("SETTINGS_GOAL_PROC_CAMERA", goalCameraProcBrightnessUpdatePair,
                goalCameraProcContrastUpdatePair, goalCameraProcSaturationUpdatePair, goalCameraProcHueUpdatePair, 
                goalCameraProcExposureUpdatePair, goalCameraProcGainUpdatePair, goalCameraProcAutoWBUpdatePair, goalCameraProcAutoGainUpdatePair, 
                goalCameraProcVFlipUpdatePair, goalCameraProcHFlipUpdatePair, goalCameraProcManualExposureUpdatePair);
        UpdateGroup goalCameraStreamGroup = new UpdateGroup("SETTINGS_GOAL_STREAM_CAMERA", goalCameraStreamBrightnessUpdatePair,
                goalCameraStreamContrastUpdatePair, goalCameraStreamSaturationUpdatePair, goalCameraStreamHueUpdatePair,
                goalCameraStreamExposureUpdatePair, goalCameraStreamGainUpdatePair, goalCameraStreamAutoWBUpdatePair, goalCameraStreamAutoGainUpdatePair,
                goalCameraStreamVFlipUpdatePair, goalCameraStreamHFlipUpdatePair, goalCameraStreamManualExposureUpdatePair);
        UpdateGroup gearCameraProcGroup = new UpdateGroup("SETTINGS_GEAR_PROC_CAMERA", gearCameraProcBrightnessUpdatePair,
                gearCameraProcContrastUpdatePair, gearCameraProcSaturationUpdatePair, gearCameraProcHueUpdatePair,
                gearCameraProcExposureUpdatePair, gearCameraProcGainUpdatePair, gearCameraProcAutoWBUpdatePair, gearCameraProcAutoGainUpdatePair,
                gearCameraProcVFlipUpdatePair, gearCameraProcHFlipUpdatePair, gearCameraProcManualExposureUpdatePair);
        UpdateGroup gearCameraStreamGroup = new UpdateGroup("SETTINGS_GEAR_STREAM_CAMERA", gearCameraStreamBrightnessUpdatePair,
                gearCameraStreamContrastUpdatePair, gearCameraStreamSaturationUpdatePair, gearCameraStreamHueUpdatePair,
                gearCameraStreamExposureUpdatePair, gearCameraStreamGainUpdatePair, gearCameraStreamAutoWBUpdatePair, gearCameraStreamAutoGainUpdatePair,
                gearCameraStreamVFlipUpdatePair, gearCameraStreamHFlipUpdatePair, gearCameraStreamManualExposureUpdatePair);
        UpdateGroup goalProcUpdateGroup = new UpdateGroup("SETTINGS_GOAL_PROC", goalMinAreaUpdatePair, goalMinPerimeterUpdatePair, 
                goalMinWidthUpdatePair, goalMaxWidthUpdatePair, goalMinHeightUpdatePair, goalMaxHeightUpdatePair,
                goalMinSolidityUpdatePair, goalMaxSolidityUpdatePair, goalMinVerticesUpdatePair, 
                goalMaxVerticesUpdatePair, goalMinRatioUpdatePair, goalMaxRatioUpdatePair, 
                goalProcColorLowerSUpdatePair, goalProcColorLowerVUpdatePair, goalProcColorLowerHUpdatePair, 
                goalProcColorUpperSUpdatePair, goalProcColorUpperVUpdatePair, goalProcColorUpperHUpdatePair);
        UpdateGroup gearProcUpdateGroup = new UpdateGroup("SETTINGS_GEAR_PROC", gearMinAreaUpdatePair, gearMinPerimeterUpdatePair,
                gearMinWidthUpdatePair, gearMaxWidthUpdatePair, gearMinHeightUpdatePair, gearMaxHeightUpdatePair,
                gearMinSolidityUpdatePair, gearMaxSolidityUpdatePair, gearMinVerticesUpdatePair,
                gearMaxVerticesUpdatePair, gearMinRatioUpdatePair, gearMaxRatioUpdatePair,
                gearProcColorLowerSUpdatePair, gearProcColorLowerVUpdatePair, gearProcColorLowerHUpdatePair,
                gearProcColorUpperSUpdatePair, gearProcColorUpperVUpdatePair, gearProcColorUpperHUpdatePair);
        UpdateGroup streamCompressionUpdateGroup = new UpdateGroup("SETTINGS_STREAM_COMPRESSION", streamCompressionUpdatePair);

        updateManager = new UpdateManager(controller, 500, goalCameraProcGroup, goalCameraStreamGroup,
                gearCameraProcGroup, gearCameraStreamGroup, goalProcUpdateGroup, gearProcUpdateGroup, streamCompressionUpdateGroup);

        updateManager.start();

        //Streaming
        streamListener.setUpdateLabel(imageLabel); //Set the label to be updated from the camera

        buttonCancel.addActionListener((ActionEvent e) -> onQuit());

        streamWarningLabel.setVisible(false);

        streamCompressionGroup.addChangeListener((ChangeEvent e) -> {
            if (streamCompressionGroup.getValue() > 30) {
                streamWarningLabel.setVisible(true);
            } else {
                streamWarningLabel.setVisible(false);
            }
        });

        saveButton.addActionListener((ActionEvent e) -> controller.asyncRequest(new NetworkData("ACTION_WRITE_CONFIG"))); //Config saving

        resetButton.addActionListener((ActionEvent e) -> controller.asyncRequest(new NetworkData("ACTION_RESET_CONFIG"))); //Config reset

        //STREAM BUTTONS
        activeCameraOffButton.addActionListener((ActionEvent e) -> controller.setActiveCamera(VisionController.Camera.OFF));
        activeCameraGoalButton.addActionListener((ActionEvent e) -> controller.setActiveCamera(VisionController.Camera.GOAL));
        activeCameraGearButton.addActionListener((ActionEvent e) -> controller.setActiveCamera(VisionController.Camera.GEAR));

        goalCameraProcModeButton.addActionListener((ActionEvent e) -> controller.setCameraMode(VisionController.Camera.GOAL, VisionController.CameraMode.PROCESSING));
        goalCameraStreamModeButton.addActionListener((ActionEvent e) -> controller.setCameraMode(VisionController.Camera.GOAL, VisionController.CameraMode.STREAMING));
        gearCameraProcModeButton.addActionListener((ActionEvent e) -> controller.setCameraMode(VisionController.Camera.GEAR, VisionController.CameraMode.PROCESSING));
        gearCameraStreamModeButton.addActionListener((ActionEvent e) -> controller.setCameraMode(VisionController.Camera.GEAR, VisionController.CameraMode.STREAMING));


        refreshButton.addActionListener((ActionEvent e) -> updateManager.refresh());

        freezeStreamButton.addActionListener((ActionEvent e) -> {
            if (streamListener.toggleFreeze()) {
                freezeStreamButton.setText("Resume Stream");
            } else {
                freezeStreamButton.setText("Freeze Stream");
            }
        });

        streamWarningLabel.setIcon(new ImageIcon(MainDialog.class.getResource("/res/warning32.png")));

    }

    //General action methods
    public void onQuit() {
        System.exit(0);
    }

    private void createUIComponents() {
        goalProcMinWidthSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        goalProcMaxWidthSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        goalProcMinHeightSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        goalProcMaxHeightSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        goalProcMinSoliditySpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        goalProcMaxSoliditySpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        goalProcMinVerticesSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        goalProcMaxVerticesSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        goalProcMinRatioSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        goalProcMaxRatioSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));

        gearProcMinWidthSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        gearProcMaxWidthSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        gearProcMinHeightSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        gearProcMaxHeightSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        gearProcMinSoliditySpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        gearProcMaxSoliditySpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        gearProcMinVerticesSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        gearProcMaxVerticesSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        gearProcMinRatioSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        gearProcMaxRatioSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));

        goalProcMinAreaSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        goalProcMinPerimeterSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        gearProcMinAreaSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));
        gearProcMinPerimeterSpinner = new JSpinner(new SpinnerNumberModel(0d, -2147483648d, 2147483648d, 1d));

        goalProcMinAreaSpinner.setValue(0d);
        goalProcMinPerimeterSpinner.setValue(0d);
        gearProcMinAreaSpinner.setValue(0d);
        gearProcMinPerimeterSpinner.setValue(0d);

        goalProcMinWidthSpinner.setValue(0d);
        goalProcMaxWidthSpinner.setValue(0d);
        goalProcMinHeightSpinner.setValue(0d);
        goalProcMaxHeightSpinner.setValue(0d);
        goalProcMinSoliditySpinner.setValue(0d);
        goalProcMaxSoliditySpinner.setValue(0d);
        goalProcMinVerticesSpinner.setValue(0d);
        goalProcMaxVerticesSpinner.setValue(0d);
        goalProcMinRatioSpinner.setValue(0d);
        goalProcMaxRatioSpinner.setValue(0d);

        gearProcMinWidthSpinner.setValue(0d);
        gearProcMaxWidthSpinner.setValue(0d);
        gearProcMinHeightSpinner.setValue(0d);
        gearProcMaxHeightSpinner.setValue(0d);
        gearProcMinSoliditySpinner.setValue(0d);
        gearProcMaxSoliditySpinner.setValue(0d);
        gearProcMinVerticesSpinner.setValue(0d);
        gearProcMaxVerticesSpinner.setValue(0d);
        gearProcMinRatioSpinner.setValue(0d);
        gearProcMaxRatioSpinner.setValue(0d);


        goalCameraProcModeButton = new WebButton("Processing");
        goalCameraStreamModeButton = new WebButton("Stream");
        gearCameraProcModeButton = new WebButton("Processing");
        gearCameraStreamModeButton = new WebButton("Stream");

        activeCameraOffButton = new WebButton("Off");
        activeCameraGoalButton = new WebButton("Goal");
        activeCameraGearButton = new WebButton("Gear");

        goalCameraModeButtonGroup = new WebButtonGroup(true, goalCameraProcModeButton, goalCameraStreamModeButton);
        gearCameraModeButtonGroup = new WebButtonGroup(true, gearCameraProcModeButton, gearCameraStreamModeButton);

        activeCameraButtonGroup = new WebButtonGroup(true, activeCameraOffButton, activeCameraGoalButton, activeCameraGearButton);
    }
}
