package org.team401.vision.eyes;

import boofcv.gui.image.ImagePanel;
import boofcv.gui.image.ScaleOptions;
import boofcv.gui.image.ShowImages;
import org.zeromq.ZMQ;

import javax.imageio.ImageIO;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.util.Base64;

/**
 * Created by cameronearle on 2/21/17.
 */
public class Eyes {
    public static void main(String[] args) {
        String address = "10.4.1.17";
        int port = 5802;

        if (args.length == 1) { //We have a custom address
            address = args[0]; //Set the address
        }
        if (args.length > 1) { //We have a custom port
            try {
                port = Integer.valueOf(args[1]); //Set port
            } catch (Exception e) {}
        }

        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket socket = context.socket(ZMQ.SUB);
        socket.subscribe("".getBytes());
        socket.connect("tcp://" + address + ":" + port);

        ImagePanel panel = new ImagePanel(640, 480);
        panel.setScaling(ScaleOptions.ALL); //Scale in all directions
        ShowImages.showWindow(panel, "Eyes: 401", true);
        Base64.Decoder decoder = Base64.getDecoder();

        while (true) {
            try {
                panel.setBufferedImage(ImageIO.read(new ByteArrayInputStream(decoder.decode(socket.recv()))));
            } catch (Exception e) {
                e.printStackTrace();

            }
        }
    }
}
