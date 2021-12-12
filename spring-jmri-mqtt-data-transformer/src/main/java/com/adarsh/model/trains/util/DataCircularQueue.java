package com.adarsh.model.trains.util;

import lombok.extern.slf4j.Slf4j;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */

@Slf4j
public class DataCircularQueue {

    private int size;
    private int startPoint;
    private int endPoint;
    private String[] queueData;

    public DataCircularQueue(int size) {
        this.size = size;
        this.queueData = new String[size];
        this.startPoint = -1;
        this.endPoint = -1;
        for (int i = 0; i < size; i++) {
            this.queueData[i] = null;
        }
    }


    public boolean enqueue(String value) {
        int newInsertPoint = (endPoint + 1) % size;
        queueData[newInsertPoint] = value;
        this.endPoint = newInsertPoint;
        return true;
    }

    public String dequeue() throws Exception {
        int newRemovalPoint = (startPoint + 1) % size;
        if (queueData[newRemovalPoint] != null) {
            String removalData = this.queueData[newRemovalPoint];
            this.queueData[newRemovalPoint] = null;
            this.startPoint = newRemovalPoint;
            return removalData;
        }
        return null;
    }

    public boolean isEmpty() throws Exception {
            int newRemovalPoint = (startPoint + 1) % size;
            if (queueData[newRemovalPoint] != null) {
                return false;
            }
            return true;
    }
}
