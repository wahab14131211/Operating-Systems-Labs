/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: wahab
 *
 * Created on February 20, 2021, 1:33 PM
 */

#include  <stdio.h> /* printf */
#include  <sys/types.h> /* pid_t */
#include <unistd.h> /* get_pid */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <sys/wait.h>  /* wait */
#include <pthread.h>
#include <sys/stat.h>
#define max_threads 5

void * count(void *);
int globalNumber = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
//Create a mutex

int main(void) {
    int i,thread_return[max_threads];
    pthread_t counterThread[max_threads];
    for(int i=0; i<max_threads;i++){
        thread_return[i]=pthread_create(&counterThread[i],NULL,count,NULL);
    }
    for(int i=0; i<max_threads;i++){
        pthread_join(counterThread[i],NULL);
    }
    //Create the 5 threads
    //Wait for all treads to finish

    return (0);
}

void * count(void * junk) {
    int loopCount = 0;
    pthread_mutex_lock(&mutex1);
    while (loopCount < 10) {
        int tmpNumber = globalNumber;
        printf("counter: %d, Thread: %ld, PID: %d\n",
                tmpNumber, pthread_self(), getpid());
        tmpNumber = globalNumber;
        tmpNumber++;
        usleep(random() % 2);
        globalNumber = tmpNumber;
        loopCount++;
    }
    pthread_mutex_unlock(&mutex1);
    return (0);
}

