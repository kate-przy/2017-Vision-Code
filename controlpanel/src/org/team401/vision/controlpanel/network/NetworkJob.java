package org.team401.vision.controlpanel.network;

import java.util.concurrent.CountDownLatch;

/**
 * came20's 2017-Vision-Code
 * Copyright (C) 2017 came20 (http://came20.net)
 * License information can be found in the "LICENSE" file,
 * found inside this package.  Should a "LICENSE" file not
 * be present, it is most likely not an official package,
 * released by myself (came20), and should be used with caution
 */
class NetworkJob {
    CountDownLatch jobLatch = new CountDownLatch(1); //Initialize a callback wait
    Request request;
    String[] params;
    String respData;

    NetworkJob(Request request, String[] params) {
        this.request = request;
        this.params = params;
    }
}
