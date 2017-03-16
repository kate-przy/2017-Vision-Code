package org.team401.vision.controlpanel.update;

import java.awt.*;

/**
 * Created by cameronearle on 3/13/17.
 */
public class ColorConverter {
    private Color rgbColor;
    private float[] hsvColor = {0f, 0f, 0f};
    private int r;
    private int g;
    private int b;

    public ColorConverter(Color c) {
        rgbColor = c;
        r = rgbColor.getRed();
        g = rgbColor.getGreen();
        b = rgbColor.getBlue();
        hsvColor = Color.RGBtoHSB(r, g, b, hsvColor); //Convert the color
    }

    public ColorConverter(int h, int s, int v) {
        hsvColor[0] = (float) h/180f;
        hsvColor[1] = (float) s/255f;
        hsvColor[2] = (float) v/255f;
        rgbColor = new Color(Color.HSBtoRGB(hsvColor[0], hsvColor[1], hsvColor[2]));
        r = rgbColor.getRed();
        g = rgbColor.getGreen();
        b = rgbColor.getBlue();
    }

    public int getH() {
        return Math.round(hsvColor[0] * 180);
    }

    public int getS() {
        return Math.round(hsvColor[1] * 255);
    }

    public int getV() {
        return Math.round(hsvColor[2] * 255);
    }

    public Color getColor() {
        return rgbColor;
    }
}
