/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package coe628.lab9;

/**
 *
 * @author wahab
 */
public class Diner {
    
    public static final int N = 5;
    public static final Semaphore mutex = new Semaphore(1);
    public static Philosopher philosopher_table[] = new Philosopher[N];
    
    public static void main(String[] args){
        for (int i=0;i<N;i++){
            philosopher_table[i] = new Philosopher(i);
        }
        for (Thread t : philosopher_table){
            t.start();
        }
    }
    
    public static Philosopher left(int id){
        return philosopher_table[id==0 ? N-1 : id-1];
    }
    public static Philosopher right(int id){
        return philosopher_table[(id+1)%N];
    }
}
