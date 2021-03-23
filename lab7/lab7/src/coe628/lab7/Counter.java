package coe628.lab7;
/** Maintains a count. */
public class Counter {
    int count = 0;
    /**
     * Add value to count.
     * @param value int to add to count
     */
    public synchronized void add(int value) {
        this.count += value;
        try {
            Thread.sleep(10);
        } catch (InterruptedException ex) {
            System.err.println("Should not get here!" + ex);
        }
    }
}
