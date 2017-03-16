package org.team401.vision.controller.event;

import org.team401.vision.controller.NetworkData;

/**
 * Created by cameronearle on 3/11/17.
 */
public class OutgoingDataEvent implements Event {
    private NetworkData outgoingData;

    public OutgoingDataEvent(NetworkData outgoingData) {
        this.outgoingData = outgoingData;
    }

    public NetworkData getOutgoingData() {
        return outgoingData;
    }
}
