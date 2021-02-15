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
    char *input;
    do{
        char *new_argv[100];
        input=(char *)malloc(100*sizeof(char));
        strncpy(input,"\0",100);
        int input_counter=0,argv_counter=0, ch, fork_boolean;
        printf("Your Command>");
        while((ch=getchar()) != '\n'){
            if(input_counter==0){
                new_argv[argv_counter]=input+input_counter;
                *(input+input_counter)=ch;
                input_counter++;
                argv_counter++;
            }else if(ch==' '){
                new_argv[argv_counter]=input+input_counter+1;
                *(input+input_counter)='\0';
                input_counter++;
                argv_counter++;
            }else{
                *(input+input_counter)=ch;
                input_counter++;
            }
        }
        *(input+input_counter)='\0';
        new_argv[argv_counter]=NULL;
        if(*(input+input_counter-1)=='&'){
            *(input+input_counter-1)='\0';
            fork_boolean=1;
        }else{
            fork_boolean=0;
        }
        pid_t pid = fork();
        if(pid<0){
            fprintf(stderr,"Error in creating child process");
        }
        if(pid>0){
            //parent process
            if(!fork_boolean){
                wait(NULL);  
            }
            goto outside_fork;
        }else{
            //child process
            int return_value = execvp(input,new_argv);
            exit(return_value);
        }

        outside_fork:
        ;
        //printf("input is: %s\nnew_argv1 is: %s\nnew_argv2 is: %s\nnew_argv3 is: %s\n",input,new_argv[0],new_argv[1],new_argv[2]);
        
    }while(strncmp(input,"exit",4)!=0);
    printf("GoodBye");
    return (EXIT_SUCCESS);
}

