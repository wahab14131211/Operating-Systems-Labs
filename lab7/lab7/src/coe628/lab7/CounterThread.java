package coe628.lab7;

/**
 * A Thread that increments a counter by 1, 2, 3, ... n.
 * 
 */
public class CounterThread extends Thread {

    Counter counter;
    int n = 0;

    public CounterThread(Counter counter, int n) {
        this.counter = counter;
        this.n = n;
    }

    @Override
    public void run() {
        for (int i = 0; i < n; i++) {
            counter.add(i);
        }
    }
}
