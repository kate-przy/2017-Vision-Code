package org.team401.vision.controller;

import java.util.concurrent.CountDownLatch;

/**
 * Created by cameronearle on 2/24/17.
 */
class NetworkJob {
    CountDownLatch latch = new CountDownLatch(1); //Set up a latch so we can return when the job is complete from a different thread
    NetworkData request;
    NetworkData response;

    NetworkJob(NetworkData request) {
        this.request = request;
    }
}
