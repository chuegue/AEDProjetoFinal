#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MinHeap.h"

#define LCHILD(x) ((x << 1) + 1)
#define RCHILD(x) ((x << 1) + 2)
#define PARENT(x) ((x - 1) >> 1)

/*
 * Função: Swap()
 * --------------------
 * Função que, dados dois ponteiros a e b, troca o seu conteúdo
 * A função troca qualquer tipo de dados, apenas precisando do tamanho size dos dados guardados nos endereços dos ponteiros
 *
 * Argumentos:
 *
 *      void *a: Ponteiro para um dos elementos para ser trocado
 *      void *b: Ponteiro para um dos elementos para ser trocado
 *
 *  Return:
 *      Nada (void)
 *
 */
void Swap(void *a, void *b, size_t size)
{
    void *temp = malloc(size); // Aloca memória com o tamanho de size para guardar o tipo de dados especificado
    if (temp != (void *)NULL)  // Verificação da alocação de memória correta
    {
        memcpy(temp, a, size); // Põe o conteúdo de a em temp
        memcpy(a, b, size);    // Põe o conteúdo de b em a
        memcpy(b, temp, size); // Põe o conteúdo de temp em b
        free(temp);            // liberta a memória de temp
    }
    else
        exit(0);
}
/*
 * Função: InitMinHeap()
 * --------------------
 * Dado um inteiro n, cria um Acervo com size=0, pos é um array de n inteiros inicializados a -1 e retorna o acervo inicializado
 *
 * Argumentos:
 *
 *      int n: tamanho máximo do acervo
 *
 *  Return:
 *
 *      MinHeap *heap: Ponteiro para o acervo inicializado
 *
 */
MinHeap *InitMinHeap(int n)
{
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap)); // aloca memória para a estrutura MinHeap
    if (heap == (MinHeap *)NULL)                        // verificação da alocação da memória
        exit(0);
    heap->size = 0;                             // número de elementos atualmente presentes no acervo
    heap->pos = (int *)malloc(n * sizeof(int)); // alocação de memória para o array de posições do acervo (para a procura ser feita em o(1))
    if (heap->pos == (int *)NULL)               // verificação da alocação de memória
        exit(0);
    for (int i = 0; i < n; i++) // inicialização do array de posições a -1 (-1 neste array significa que o vertice correspondente a essa entrada não está no acervo)
    {
        heap->pos[i] = -1;
    }

    return heap;
}
/*
 * Função: InserMinHeap()
 * --------------------
 * 
 * Insere um Node no acervo de acordo com a sua prioridade priority, mantendo as propriedades de acervo
 *
 * Argumentos:
 *
 *      MinHeap *heap: acervo onde é para inserir os novos dados
 *      int v: véritce que é para guardar
 *      int priority: prioridade que se vai utilizar para inserir os dados no acervo
 *
 *  Return:
 *      Nada (void)
 *
 */
void InsertMinHeap(MinHeap *heap, int v, int priority)
{
    // se já houver elementos no acervo, aumenta a capacidade do array de Nodes de heap
    if (heap->size)
    {
        heap->heap = (Node *)realloc(heap->heap, (heap->size + 1) * sizeof(Node));
        //verificação da alocação da memória
        if (heap->heap == (Node *)NULL)
            exit(0);
    }
    // se não houver elementos no acervo, aloca memória para um elemento
    else
    {
        heap->heap = (Node *)malloc(sizeof(Node));
        //verificação da alocação da memória
        if (heap->heap == (Node *)NULL)
            exit(0);
    }
    //criação da estrutura para por os dados fornecidos
    Node nd;
    nd.v = v;
    nd.priority = priority;
    //aumentar o número de elementos no acervo
    int i = (heap->size)++;
    //encontrar o lugar certo para inserir os dados no acervo
    while (i > 0 && nd.priority < heap->heap[PARENT(i)].priority)
    {
        //se priority for maior do que o pai da posição que se está a analisar, troca o pai com o filho no acervo
        heap->pos[heap->heap[PARENT(i)].v] = i;
        heap->heap[i] = heap->heap[PARENT(i)];
        i = PARENT(i);
    }
    //coloca os dados no sitio correto no acervo
    heap->heap[i] = nd;
    heap->pos[v] = i;
}

/*
 * Função: Heapify()
 * --------------------
 * 
 * Dado um acervo, ordena o acervo de acordo com as suas propriedades, se não estiver já ordenado. Ou seja, faz um "Fix Down"
 * Começa em i e vai descendo no acervo enquanto as suas propriedades estiverem a ser violadas, ou seja a prioridade de um nó é maior do que a de um dos seus filhos
 *
 * Argumentos:
 *
 *      MinHeap *heap: acervo que é para repor as suas propriedades
 *      int i: indice do acervo a partir do qual é para reordenar o acervo
 *
 *  Return:
 *      Nada (void)
 *
 */
void Heapify(MinHeap *heap, int i)
{
    //vê qual é o elemento que tem menor prioridade (Pai, Filho Direito, Filho Esquerdo)
    int smallest = i;
    if (LCHILD(i) < heap->size && heap->heap[LCHILD(i)].priority < heap->heap[i].priority)
        smallest = LCHILD(i);

    if (RCHILD(i) < heap->size && heap->heap[RCHILD(i)].priority < heap->heap[smallest].priority)
        smallest = RCHILD(i);
    //se o elemento com menor prioridade for o pai (smallest == i) então o acervo já está ordenado. Return
    //se o elemento com menor prioridade for um dos filhos, troca o pai com o filho no acervo e troca as suas posições e chama a função Heapify recursivamente com um index do filho com menor prioridade
    if (smallest != i)
    {
        Swap(&heap->heap[i], &heap->heap[smallest], sizeof(Node));
        Swap(&heap->pos[heap->heap[i].v], &heap->pos[heap->heap[smallest].v], sizeof(int));
        Heapify(heap, smallest);
    }
}

/*
 * Função: GetMin()
 * --------------------
 *
 * Retorna o valor de v da raiz do acervo mantendo as propriedades do acervo
 *
 * Argumentos:
 *
 *      MinHeap *heap: acervo de onde é para retornar o valor de v com menor prioridade
 *      
 *  Return:
 *      int r: valor de v da raiz do acervo
 *
 */
int GetMin(MinHeap *heap)
{
    int r = -1;
    //se o acervo não estiver vazio, retira a raiz
    if (heap->size)
    {
        //valor que é para dar return (v da raiz do acervo)
        r = heap->heap[0].v;
        //dizer que este vertice já não está no acervo
        heap->pos[heap->heap[0].v] = -1;
        //se houver mais algum elemento no acervo além da raiz, põe o último elemento do acervo no lugar da raíz
        //se não houver mais nenhum elemento, o acervo fica vazio e não fazia sentido trocar elementos de lugar
        if (heap->size > 1)
        {
            heap->heap[0] = heap->heap[heap->size - 1];
            heap->pos[heap->heap[0].v] = 0;
        }
        //reduz o número de elementos do acervo
        heap->size--;
        //reduz a memória alocada para o array de nodes no acervo. No caso de heap->size ser zero, este realloc funciona como um free
        heap->heap = (Node *)realloc(heap->heap, (heap->size) * sizeof(Node));
        //repões as propriedades de acervo
        Heapify(heap, 0);
    }
    //se o acervo estiver vazio, dá free à memória alocada pelos arrays do acervo e retorna -1
    else
    {
        free(heap->heap);
        free(heap->pos);
    }
    return r;
}

/*
 * Função: ChangePriority()
 * --------------------
 * 
 * Altera a prioridade de um elemento no acervo
 *
 * Argumentos:
 *
 *      MinHeap *heap: acervo onde é para modificar a prioridade do elemento 
 *      int v: véritce que é para alterar a prioridade
 *      int new_priority: prioridade para que é para mudar
 *
 *  Return:
 *      Nada (void)
 *
 */
void ChangePriority(MinHeap *heap, int v, int new_priority)
{
    //i vai ser a posição do veritce v no acervo
    int i;
    //temp vai guardar os dados do vertice v que estão no acervo (v e prioridade)
    Node temp;
    i = heap->pos[v];
    //altera a prioridade do elemento do acervo com valor v
    heap->heap[i].priority = new_priority;
    temp = heap->heap[i];

    //fix up
    //repõe as propriedades do acervo e atualiza o array de posições
    while (i > 0 && temp.priority < heap->heap[PARENT(i)].priority)
    {
        heap->pos[heap->heap[PARENT(i)].v] = i;
        heap->heap[i] = heap->heap[PARENT(i)];
        i = PARENT(i);
    }
    heap->heap[i] = temp;
    heap->pos[v] = i;
}

/*
 * Função: HeapIsEmpty()
 * --------------------
 * 
 * Retorna 1 se a heap estiver vazia, 0 se não estiver
 * 
 * Argumentos:
 *
 *      MinHeap *heap: acervo que é para ver se está vazio ou não
 *
 *  Return:
 *      int: retorna 1 ou 0
 *
 */
int HeapIsEmpty(MinHeap *heap)
{
    if (heap->size)
        return 0;
    else
        return 1;
}

/*
 * Função: FreeHeap()
 * --------------------
 * 
 * Liberta a memória alocada pelo acervo
 * 
 * Argumentos:
 *
 *      MinHeap *heap: acervo que é para libertar a memória
 *      
 *  Return:
 *      Nada (void)
 *
 */
void FreeHeap(MinHeap *heap)
{
    free(heap->heap);
    free(heap->pos);
    free(heap);
}

/*
 * Função: IsInHeap()
 * --------------------
 * 
 *  Dado um acervo e um vértice, retorna 1 se o verice estiver no acervo e 0 se não estiver
 *
 * Argumentos:
 *
 *      MinHeap *heap: acervo onde é para verificar a existência de v
 *      int v: véritce que é para procurar
 * 
 *  Return:
 *      int: retorna 1 ou 0     
 * 
 */
int IsInHeap(MinHeap *heap, int v)
{
    if (heap->pos[v] == -1)
        return 0;
    else
        return 1;
}