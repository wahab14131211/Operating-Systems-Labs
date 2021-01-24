#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;
/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author YOUR NAME
 */
void PQ_insert(int priority, char * data) {
    Node_ptr_t new_node, tmp;
    new_node=(Node_ptr_t)malloc(sizeof(Node_t));
    new_node->data = data;
    new_node->priority = priority;
    if (head == NULL){
        new_node->next = NULL;
        head=new_node;
    }else if (head->priority < new_node->priority){
        new_node->next = head;
        head=new_node;
    }else{
        for (tmp=head;tmp->next->next != NULL && new_node->priority < tmp->next->priority; tmp=tmp->next){
        }
        new_node->next = tmp->next;
        tmp->next = new_node;
    }
}
/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
    Node_ptr_t return_node = head;
    head=head->next;
    return return_node;
}

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
//    if(head != NULL){
//        fprintf(stderr, "head priority is: %d\n",head->priority);
//    }
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++){
    }
    return size;
}


