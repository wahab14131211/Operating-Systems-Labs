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
    char *parent_input, *child_input;
    do{
        char *parent_argv[100], *child_argv[100];
        parent_input=(char *)malloc(100*sizeof(char));
        child_input=(char *)malloc(100*sizeof(char));
        strncpy(parent_input,"\0",100);
        strncpy(child_input,"\0",100);
        int parent_input_counter=0,child_input_counter=0,parent_argv_counter=0, child_argv_counter=0, ch, parent_or_child=0;
        printf("Your Command>");
        while((ch=getchar()) != '\n'){
            if(parent_input_counter==0){
                parent_argv[parent_argv_counter]=parent_input;
                *(parent_input+parent_input_counter)=ch;
                parent_input_counter++;
                parent_argv_counter++;
            }else if(ch=='|'){
                parent_or_child=1;
            }else if(ch==' '){
                if(!parent_or_child){
                    parent_argv[parent_argv_counter]=parent_input+parent_input_counter+1;
                    *(parent_input+parent_input_counter)='\0';
                    parent_input_counter++;
                    parent_argv_counter++;
                }else{
                    if(child_input_counter==0){
                        child_argv[child_argv_counter]=child_input;
                        *(child_input+child_input_counter)=ch;
                        child_input_counter++;
                        child_argv_counter++;
                    }else{
                        child_argv[child_argv_counter]=child_input+child_input_counter+1;
                        *(child_input+child_input_counter)='\0';
                        child_input_counter++;
                        child_argv_counter++;
                    }
                }
            }else{
                if(!parent_or_child){
                    *(parent_input+parent_input_counter)=ch;
                    parent_input_counter++;
                }else{
                    *(child_input+child_input_counter)=ch;
                    child_input_counter++;
                }
            }
        }
        *(parent_input+parent_input_counter)='\0';
        *(child_input+child_input_counter)='\0';
        parent_argv[parent_argv_counter]=NULL;
        child_argv[child_argv_counter]=NULL;

        //since exec will replace the current process image with a new image, and we need to run exec in the "parent", we will have 3 levels of processes
        //1. This process which handles user input and spawns a child process to run the first command
        //2. This process will be considered the "parent" process and will spawn another child to run the child process
        //3. runs the child process

        pid_t pid1 = fork(); //spawn level 2 process as described above
        if(pid1<0){
            fprintf(stderr,"Error in creating child process");
        }
        if(pid1>0){
            //level 1 process
            wait(0);
            goto outside_fork;
        }else{
            //level 2 process
            int pd[2];
            if(pipe(pd)==-1){
                fprintf(stderr,"Error in creating pipe");
            }
            pid_t pid2=fork(); //spawn level 3 process as described above
            if(pid2<0){
                //error in creating level 3 process
                fprintf(stderr,"Error in creating child process");
            }else if(pid2>0){
                //level 2 process, needs to run parent command
                dup2(pd[1],STDOUT_FILENO);
                close(pd[0]);
                close(pd[1]);
                execv(parent_input, parent_argv);
                exit(0);
            }else{
                //level 3 process, needs to run child command
                dup2(pd[0],STDIN_FILENO);
                close(pd[1]);
                close(pd[0]);
                execv(child_input, child_argv);
                exit(0);
            }
            
        }

        outside_fork:
        printf("parent_input is: %s\nparent_argv1 is: %s\nparent_argv2 is: %s\nchild_input is: %s\nchild_argv1 is: %s\nchild_argv2 is: %s\n",parent_input,parent_argv[0],parent_argv[1],child_input,child_argv[0],child_argv[1]);
        while(wait(NULL)>0);
        sleep(1);
        fflush(stdin);
    }while(strncmp(parent_input,"exit",4)!=0);
    printf("GoodBye");
    return (EXIT_SUCCESS);
}

