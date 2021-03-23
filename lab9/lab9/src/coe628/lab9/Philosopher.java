/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package coe628.lab9;
import coe628.lab9.Diner;

/**
 *
 * @author wahab
 */
public class Philosopher extends Thread{

    private enum phil_state {THINKING, HUNGRY, EATING};
    private final int id;
    public phil_state state;
    private final Semaphore s;
    
    public Philosopher(int id){
        this.id = id;
        s = new Semaphore(0);
        state=phil_state.THINKING;
    }
    
    public void getFork(){
        this.state = phil_state.HUNGRY;
        printState();
        while(state == phil_state.HUNGRY){
            Diner.mutex.down();
            if(state == phil_state.HUNGRY && Diner.left(this.id).state != phil_state.EATING && Diner.right(this.id).state != phil_state.EATING){
                state = phil_state.EATING;
                Diner.mutex.up();
            }
            Diner.mutex.up();
            s.up();
        }
    }
    
    public void putFork(){
        Diner.mutex.down();
        this.state = phil_state.THINKING;
        think();
        if(Diner.left(this.id).state == phil_state.HUNGRY){
            Diner.left(this.id).s.up();
        }
        if(Diner.right(this.id).state == phil_state.HUNGRY){
            Diner.right(this.id).s.up();
        }
        Diner.mutex.up();
    }
    
    public void think(){
        printState();
        try{
            Thread.sleep((long) Math.round(Math.random()*5000));
        }catch(InterruptedException e){}
    }
    
    public void eat(){
        System.out.println("Philosopher " + (this.id) + ", State: " + state + ", Left State: " + Diner.left(this.id).state + ", Right State: " + Diner.right(this.id).state);
        try {
            Thread.sleep((long) Math.round(Math.random() * 5000));
        } catch (InterruptedException e) {}
        System.out.println("Philosopher " + (this.id) + ", DONE EATING");
    }
    
    private void printState() {
        System.out.println("Philosopher " + (this.id) + ", State: " + this.state);
    }
    
    public void run(){
        while(true){
            think();
            getFork();
            eat();
            putFork();
        }
    }
}
