package org.team401.vision.controlpanel.update;

/**
 * Created by cameronearle on 3/21/17.
 */
public class Dualean {
    private boolean current;
    private boolean previous;

    public Dualean(boolean initialValue) {
        current = initialValue;
        previous = initialValue;
    }

    public void update(boolean newValue) {
        previous = current;
        current = newValue;
    }

    public void setBoth(boolean newValue) {
        previous = newValue;
        current = newValue;
    }

    public boolean bothTrue() {
        return (previous && current);
    }

    public boolean bothFalse() {
        return (!previous && !current);
    }

    public boolean currentTruePreviousFalse() {
        return (!previous && current);
    }

    public boolean currentFalsePreviousTrue() {
        return (previous && !current);
    }
}
