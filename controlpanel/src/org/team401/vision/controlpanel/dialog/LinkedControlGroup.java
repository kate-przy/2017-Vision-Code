package org.team401.vision.controlpanel.dialog;


import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;

/**
 * Links the values of a slider and a spinner
 */
public class LinkedControlGroup {
    private JSlider slider;
    private JSpinner spinner;

    public LinkedControlGroup(JSlider slider, JSpinner spinner, int lowerBound, int upperBound, int defaultValue) {
        this.slider = slider;
        this.spinner = spinner;
        this.slider.addChangeListener(this::sliderUpdate);
        this.spinner.addChangeListener(this::spinnerUpdate);
        this.slider.setMinimum(lowerBound);
        this.slider.setMaximum(upperBound);
        this.slider.setValue(defaultValue);
        SpinnerNumberModel spinnerNumberModel = new SpinnerNumberModel(defaultValue, lowerBound, upperBound, 1);
        this.spinner.setModel(spinnerNumberModel);
    }

    private void sliderUpdate(ChangeEvent e) {
        spinner.setValue(slider.getValue()); //Set the spinner to match the spinner
    }

    private void spinnerUpdate(ChangeEvent e) {
        slider.setValue((int) spinner.getValue()); //Set the slider to match the spinner
    }

    public void updateAll(int newValue) {
        slider.setValue(newValue);
        spinner.setValue(newValue);
    }

}
