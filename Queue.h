#ifndef __SIMPLE_QUEUE__
#define __SIMPLE_QUEUE__

typedef struct NodeQ NodeQ;
typedef struct Queue Queue;

Queue *create_queue(void);
unsigned is_empty(Queue *);
void enqueue(Queue *, int x, int y);
void dequeue(Queue *, int *u);

#endif