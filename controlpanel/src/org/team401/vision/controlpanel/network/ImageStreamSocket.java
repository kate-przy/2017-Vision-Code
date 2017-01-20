package org.team401.vision.controlpanel.network;

import org.zeromq.ZMQ;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.util.concurrent.atomic.AtomicReference;

/**
 * Created by cameronearle on 1/18/17.
 */
public class ImageStreamSocket implements Runnable {
    private String address;
    private int port;

    private AtomicReference<BufferedImage> latestImage;

    public ImageStreamSocket(String address, int port) {
        this.address = address;
        this.port = port;
    }

    @Override
    public void run() {
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket socket = context.socket(ZMQ.SUB);
        socket.subscribe("".getBytes());
        socket.connect("tcp://" + address + ":" + port); //Connect to the server
        while (!Thread.currentThread().isInterrupted()) {
            try {
                latestImage.set(ImageIO.read(new ByteArrayInputStream(socket.recv()))); //Read the image from the socket
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        socket.close();
    }
}
