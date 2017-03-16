package org.team401.vision.controlpanel.update;

import java.util.EventObject;
import java.util.concurrent.atomic.AtomicReference;

/**
 * Created by cameronearle on 3/12/17.
 */
public class UpdatePair {
    private String key;
    private UpdateGetMethod getMethod;
    private UpdateSetMethod setMethod;
    private AtomicReference<Object> latestValue;
    private Class clazz;

    public UpdatePair(String key, Object initialValue, UpdateGetMethod getMethod, UpdateSetMethod setMethod, Class clazz) {
        this.key = key;
        this.getMethod = getMethod;
        this.setMethod = setMethod;
        this.latestValue = new AtomicReference<>(initialValue);
        this.clazz = clazz;
    }

    public String getKey() {
        return key;
    }

    public Object getValue() {
        return latestValue.get();
    }

    public Class getClazz() {
        return clazz;
    }

    public void setValue(Object v) {
        setMethod.setValue(v);
        latestValue.set(v);
        System.err.println("DEBUG SET: [" + key + "], [" + v.toString() + "]");
    }

    public void onUpdate(EventObject e) {
        latestValue.set(getMethod.getValue());
        System.err.println("DEBUG UPDATE: [" + key + "], [" + latestValue.get().toString() + "]");
    }

    public void onUpdate() {
        onUpdate(null);
    }
}
