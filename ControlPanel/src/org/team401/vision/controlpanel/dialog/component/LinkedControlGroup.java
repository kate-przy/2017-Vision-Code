package org.team401.vision.controlpanel.dialog.component;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.EventListenerList;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Links the values of a slider and a spinner
 */
public class LinkedControlGroup {
    private JSlider slider;
    private JSpinner spinner;
    private EventListenerList eventList = new EventListenerList();

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
        fireUpdate(); //Tell the listeners of this class that we updated
    }

    private void spinnerUpdate(ChangeEvent e) {
        slider.setValue((int) spinner.getValue()); //Set the slider to match the spinner
        //fireUpdate();
    }

    public void updateAll(int newValue) {
        slider.setValue(newValue);
        spinner.setValue(newValue);
    }

    public void addChangeListener(ChangeListener l) {
        eventList.add(ChangeListener.class, l); //Add the handler
    }

    public int getValue() {
        return slider.getValue();
    }

    private void fireUpdate() {
        ChangeListener[] listeners = eventList.getListeners(ChangeListener.class);
        if (listeners != null && listeners.length > 0) {
            ChangeEvent evt = new ChangeEvent(this);
            for (ChangeListener listener : listeners) {
                listener.stateChanged(evt);
            }
        }
    }
}