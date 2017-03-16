package org.team401.vision.controlpanel.update;

import org.team401.vision.controller.NetworkData;

import java.util.List;
import java.util.Vector;

/**
 * Created by cameronearle on 3/13/17.
 */
public class UpdateGroup {
    private String name;
    private List<UpdatePair> pairList = new Vector<>();

    public UpdateGroup(String name, UpdatePair... pairs) {
        this.name = name;
        for (UpdatePair p : pairs) {
            pairList.add(p);
        }
    }

    public void addPair(UpdatePair p) {
        pairList.add(p);
    }

    public List<UpdatePair> getPairList() {
        return pairList;
    }

    public String getName() {
        return name;
    }

    public void updateGroup(NetworkData data) {
        for (UpdatePair pair : pairList) {
            System.out.println(pair.getKey());
            pair.setValue(data.getElement(pair.getKey(), pair.getClazz()));
        }
    }
}
