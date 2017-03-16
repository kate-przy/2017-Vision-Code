package org.team401.vision.controller.event;


/**
 * Created by cameronearle on 3/11/17.
 */
public interface EventHandler<E extends Event> {
    void onEvent(E e);
}
