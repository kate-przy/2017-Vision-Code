package org.team401.vision.controller;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by cameronearle on 2/24/17.
 */
public class NetworkData {
    private HashMap<String, String> map = new HashMap<>(); //Hashmap to hold all of our values
    private String type; //The type of data, used purely for identification

    /**
     * General purpose constructor for user-made networkdata
     * @param type The type to use
     * @param pairs Pairs to use, varargs
     */
    public NetworkData(String type, Pair... pairs) {
        this.type = type;
        for (Pair p : pairs) {
            putElement(p);
        }
    }

    /**
     * Decode constructor, used to parse hashed network data
     * @param encoded The encoded string
     */
    public static NetworkData decode(String encoded) {
        String commandSplit[] = encoded.split("#"); //Split on the '#', dividing the command in half
        String commandType;
        String args[];
        NetworkData toReturn;
        if (commandSplit.length >= 1) { //If there is any data
            commandType = commandSplit[0]; //Set the command type
            toReturn = new NetworkData(commandType);
            if (commandSplit.length >= 2) { //If there are args
                String[] argsSplit = commandSplit[1].split(","); //Split up each argument group
                for (String s : argsSplit) {
                    String[] argSplit = s.split(":"); //Break each arg into key and value
                    if (argSplit.length >= 2) { //If this is a valid arg
                        toReturn.putElement(argSplit[0], argSplit[1]); //Put the element into the map
                    }
                }
            }
        } else { //There is no data
            toReturn = new NetworkData("INVALID"); //Mark the data to return as "INVALID" (there is no "invalid" state, all data MUST be initialized)
        }
        return toReturn;
    }

    /**
     * General purpose put method to add elements to the map
     * @param key The key to use
     * @param value The value to use
     */
    public void putElement(String key, Object value) {
        map.put(key, value.toString());
    }

    /**
     * Special method to put Pair objects into the map, used by the varargs constructor
     * @param pair The pair to insert
     */
    public void putElement(Pair pair) {
        map.put(pair.getKey(), pair.getValue());
    }

    /**
     * Method to retrieve an element from the map, and cast to the desired class
     * @param key The key to read
     * @param clazz The class type to cast to
     * @param <T> Set by clazz
     * @return The casted object
     */
    public <T> T getElement(String key, Class<T> clazz) {
        String rawValue = map.getOrDefault(key, "0");
        try {
            if (Byte.class.isAssignableFrom(clazz)) {
                return (T) Byte.valueOf(rawValue);
            } else if (Short.class.isAssignableFrom(clazz)) {
                return (T) Short.valueOf(rawValue);
            } else if (Integer.class.isAssignableFrom(clazz)) {
                return (T) Integer.valueOf(rawValue);
            } else if (Long.class.isAssignableFrom(clazz)) {
                return (T) Long.valueOf(rawValue);
            } else if (Float.class.isAssignableFrom(clazz)) {
                return (T) Float.valueOf(rawValue);
            } else if (Double.class.isAssignableFrom(clazz)) {
                return (T) Double.valueOf(rawValue);
            } else if (Boolean.class.isAssignableFrom(clazz)) {
                //SPECIAL CASE
                if (rawValue.equals("1") || rawValue.equals("true")) { //Handle our "C-Style" booleans
                    return (T) new Boolean(true); //Return a true objective boolean
                } else {
                    return (T) new Boolean(false); //Return a false objective boolean
                }
            } else if (String.class.isAssignableFrom(clazz)) {
                return (T) rawValue;
            } else { //We can try to cast this, but it probably won't work
                return clazz.cast(rawValue);
            }
        } catch (Exception e) { //If casting fails
            System.err.println("Error casting key [" + key + "] to class [" + clazz.getSimpleName() + "]"); //Tell them
            e.printStackTrace(); //Tell them more
            return null; //Break their program
        }
    }

    /**
     * Getter for the type of this data
     * @return The type of this data
     */
    public String getType() {
        return type;
    }

    /**
     * Method to hash out this data into a routable form
     * @return The hashed string
     */
    public String hash() {
        String toReturn = type + "#"; //Set up the initial string
        boolean first = true;
        for (Map.Entry<String, String> entry : map.entrySet()) { //Iterate the map
            if (!first) { //If this is not the first iteration
                toReturn += ","; //Add a comma to the previous data set
            }
            toReturn += entry.getKey() + ":" + entry.getValue(); //Append the data to the string
            first = false; //Mark future executions that this is not the first run
        }
        return toReturn; //Return the built string
    }

    /**
     * Override of toString, calls hash()
     * @return The result of hash()
     */
    @Override
    public String toString() {
        return hash(); //Run our designated method for hashing
    }
}
