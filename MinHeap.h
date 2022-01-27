#ifndef MINHEAP
#define MINHEAP

//estrutura que vai guardar os vertices e as suas prioridades no acervo
typedef struct _Node
{
    int v;
    int priority;
} Node;

//estrutura principal do acervo:
//contem um int size que indica quantos elementos estão atualmente no acervo
//contem um array de estruturas Node que vai servir para guardar os dados necessários
//contem um array de ints com as posições dos respetivos vertices no acervo, para procura e acesso em O(1)
typedef struct _MinHeap
{
    int size;
    Node *heap;
    int *pos;
} MinHeap;

int Index(int i, int j, int c);

MinHeap *InitMinHeap(int n);

void InsertMinHeap(MinHeap *heap, int v, int priority);

int GetMin(MinHeap *heap);

void ChangePriority(MinHeap *heap, int v, int new_priority);

int HeapIsEmpty(MinHeap *heap);

void FreeHeap(MinHeap *heap);

int IsInHeap(MinHeap *heap, int v);

#endif