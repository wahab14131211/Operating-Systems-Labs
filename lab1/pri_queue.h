#ifndef PRI_QUEUE_H
#define PRI_QUEUE_H
typedef struct node {
    int priority;
    char * data;
    struct node * next;
} Node_t, * Node_ptr_t;
extern void PQ_insert( int, char *);
extern Node_ptr_t PQ_delete();
extern Node_ptr_t PQ_get_head();
extern int PQ_get_size();
#endif /* PRI_QUEUE_H */
