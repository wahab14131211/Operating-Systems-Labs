/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: wahab
 *
 * Created on February 8, 2021, 9:50 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h> 
#include <unistd.h> 


/*
 * 
 */
int main(int argc, char** argv) {
    char *parent_command, *child_command;
    parent_command=(char *)malloc(100*sizeof(char));
    child_command=(char *)malloc(100*sizeof(char));
    printf("Your Command>");
    fgets(parent_command,100,stdin);
    child_command=strchr(parent_command,'|')+1; //identify the pipe
    if(child_command-1==NULL){ //check to see if there is a pipe
        fprintf(stderr,"No Pipe Found");
        exit(1);
    }
    for(;child_command[0]==' ';child_command=child_command+1); //remove any spaces between pipe and the child command
    for(char *temp=strchr(parent_command,'|')-1;temp[0]==' ';temp[0]='\0',temp--); //remove any spaces between pipe and the parent command

    int pd[2]; //create pipe descriptor

    if(pipe(pd)<0){ //create pipe and check for errors
        fprintf(stderr,"Error in creating pipe");
        exit(1);
    }

    if(fork()==0){
        //child process
        dup2(pd[0],0);
        close(pd[1]);
        system(child_command);
        exit(0);
    }else{
        //parent process
        dup2(pd[1],1);
        close(pd[0]);
        system(parent_command);
    }
    return(0);
}

