package org.team401.vision.controller.event;

import java.util.List;
import java.util.Vector;

/**
 * Created by cameronearle on 12/28/16.
 */
public class EventHandlerGroup<E extends EventHandler> {
    private List<E> eventHandlers = new Vector<>();

    public void addEventHandler(E e) {
        eventHandlers.add(e);
    }

    public int getNumberOfEventHandlers() {
        return eventHandlers.size();
    }

    public E getEventHandler(int index) {
        if (index >= eventHandlers.size()) {
            return null;
        } else {
            return eventHandlers.get(index);
        }
    }

    public boolean callHandler(int index, Event event) {
        if (index >= eventHandlers.size()) {
            return false;
        } else {
            eventHandlers.get(index).onEvent(event);
            return true;
        }
    }


    public void callGroup(Event event) {
        for (E handler : eventHandlers) {
            handler.onEvent(event);
        }
    }

    public void clearGroup() { //Empty the group, this is used when the client receives a new Player object, it needs to clear out the old (server only) handlers and patch in new ones
        eventHandlers.clear();
    }
}