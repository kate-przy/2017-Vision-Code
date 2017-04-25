package org.team401.vision.controlpanel.stream;

import org.zeromq.ZMQ;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.util.Base64;
import java.util.concurrent.atomic.AtomicReference;

/**
 * Created by cameronearle on 3/18/17.
 */
public class StreamListener extends Thread {
    private String address;
    private int port;
    private JLabel imageLabel;

    private AtomicReference<BufferedImage> latest = new AtomicReference<>(new BufferedImage(640, 480, BufferedImage.TYPE_3BYTE_BGR));

    private boolean freeze = false;

    public StreamListener(String address, int port, JLabel updateLabel) {
        this.address = address;
        this.port = port;
        imageLabel = updateLabel;
    }

    public StreamListener(String address, int port) {
        this(address, port, null);
    }

    public void setUpdateLabel(JLabel updateLabel) {
        imageLabel = updateLabel;
    }

    public void setFreeze(boolean newFreeze) {
        freeze = newFreeze;
    }

    public boolean toggleFreeze() {
        freeze = !freeze;
        return freeze;
    }

    public BufferedImage getLatest() {
        return latest.get();
    }

    @Override
    public void run() {
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket socket = context.socket(ZMQ.SUB);
        socket.connect("tcp://" + address + ":" + port);
        socket.subscribe("".getBytes());
        Base64.Decoder decoder = Base64.getDecoder();
        while (!Thread.interrupted()) {
            try {
                latest.set(ImageIO.read(new ByteArrayInputStream(decoder.decode(socket.recv()))));
                if (imageLabel != null && !freeze) {
                    imageLabel.setIcon(new ImageIcon(latest.get()));
                }
            } catch (Exception e) {
                //Who really cares anyway?
            }
        }
    }
}
