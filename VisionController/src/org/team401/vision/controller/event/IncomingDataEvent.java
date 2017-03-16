package org.team401.vision.controller.event;

import org.team401.vision.controller.NetworkData;

/**
 * Created by cameronearle on 3/11/17.
 */
public class IncomingDataEvent implements Event {
    private NetworkData incomingData;

    public IncomingDataEvent(NetworkData incomingData) {
        this.incomingData = incomingData;
    }

    public NetworkData getIncomingData() {
        return incomingData;
    }
}
