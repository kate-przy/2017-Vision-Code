package org.team401.visioncontroller;

import java.util.concurrent.CountDownLatch;

/**
 * Created by cameronearle on 2/21/17.
 */
class NetworkJob {
    CountDownLatch latch = new CountDownLatch(1); //A latch that is flagged when the job is done
    private String request;
    private String response;

    public NetworkJob(String request) {
        this.request = request;
    }

    String getRequest() {
        return request;
    }

    void setResponse(String response) {
        this.response = response;
    }

    String getResponse() {
        if (latch.getCount() == 0) {
            return response;
        } else {
            return null;
        }
    }
}
