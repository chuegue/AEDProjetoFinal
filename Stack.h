#ifndef STACK
#define STACK

//A Stack vai ser uma lista destas estruturas:
//Contém x e y
//Contém ponteiro para o próximo elemento da stack
typedef struct _StackElement
{
    int x;
    int y;
    struct _StackElement *next;
} StackElement;

StackElement *InitStack();

void Push(StackElement **S, int x, int y);

int IsEmpty(StackElement *S);

int *Pop(StackElement **S, int *aux);

void FreeStack(StackElement **S);

#endif