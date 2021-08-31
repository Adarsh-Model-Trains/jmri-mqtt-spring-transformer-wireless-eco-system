package com.adarsh.model.trains.util;

import lombok.extern.slf4j.Slf4j;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */

@Slf4j
public class CircularQueue<T> {

    private int size;
    private int startPoint;
    private int endPoint;
    private Node<T>[] queueData;

    public CircularQueue(int size) {
        this.size = size;
        this.queueData = new Node[size];
        this.startPoint = -1;
        this.endPoint = -1;
        for (int i = 0; i < size; i++) {
            this.queueData[i] = null;
        }
    }


    public boolean enqueue(T value) {
        int newInsertPoint = (endPoint + 1) % size;
            queueData[newInsertPoint] = new Node(value);
            this.endPoint = newInsertPoint;
            return true;
    }

    public T dequeue() throws Exception {
        int newRemovalPoint = (startPoint + 1) % size;
        if (queueData[newRemovalPoint] != null) {
            Node<T> removalData = this.queueData[newRemovalPoint];
            this.queueData[newRemovalPoint] = null;
            this.startPoint = newRemovalPoint;
            return removalData.getData();
        }
        return null;
    }

    public void display() {
        int st = 0;
        int end = 0;
        st = (startPoint + 1) % size;
        end = st;
        while (true) {
            log.info("Displaying => {}", queueData[st].getData());
            st = (st + 1) % size;
            if (st == end) {
                break;
            }
            if (queueData[st] == null) {
                break;
            }
        }
    }

    public class Node<T> {
        T data;

        public Node(T data) {
            this.data = data;
        }

        public void setData(T data) {
            this.data = data;
        }

        public T getData() {
            return data;
        }
    }
}
