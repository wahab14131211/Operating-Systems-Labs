package coe628.lab7;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        Counter counter = new Counter();
        Thread threadA = new CounterThread(counter, 10);
        Thread threadB = new CounterThread(counter, 11);
        System.out.println("Starting A");
        threadA.start();
        System.out.println("Starting B");
        threadB.start();
        threadB.join(); //Wait for B to finish if commented the 55 loops of threadB wont be executed, only 45 of threadA
        threadA.join(); //Wait for A to finish if commented, still get complete output
        System.out.println("count: " + counter.count);
    }
}

