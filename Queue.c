#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

// Dados que são para guardar na Fila: x e y
struct NodeQ
{
    int x;
    int y;
    NodeQ *next;
};

// Guarda os ponteiros para o inicio e fim da fila, para insereção e remoção da fila ser feita em O(1)
struct Queue
{
    NodeQ *head;
    NodeQ *tail;
};

/*
 * Função: create_queue()
 * --------------------
 *
 * Cria, aloca memória e retorna uma nova fila
 *
 * Argumentos:
 *
 *      Nenhum
 *
 *  Return:
 *      Queue * : ponteiro para uma estrutura Queue inicializada.
 *
 */
Queue *create_queue()
{
    // alocação da memória para a estrutura Queue
    Queue *qu = (Queue *)malloc(sizeof(Queue));
    // verificação da alocação de memória
    if (qu == (Queue *)NULL)
        exit(0);
    // inicialização dos ponteiros para o inicio e para o fim da fila a null
    qu->head = NULL;
    qu->tail = NULL;
    return qu;
}

/*
 * Função: is_empty()
 * --------------------
 *
 * retorna 1 se a fila qu estiver vazia e 0 se não estiver vazia
 *
 * Argumentos:
 *
 *      Queue *qu: fila que é para ver se está vazia ou não
 *
 *  Return:
 *      unsigned int: retorna 1 ou 0
 *
 */
unsigned is_empty(Queue *qu)
{
    return qu->head == NULL && qu->tail == NULL;
}

/*
 * Função: enqueue()
 * --------------------
 *
 * Insere os dados x e y na fila qu
 *
 * Argumentos:
 *
 *      Queue *qu: fila onde é para inserir os dados
 *      int x: componente x da estrutura que vai ser inserida na fila
 *      int y: componente y da estrutura que vai ser inserida na fila
 *
 *  Return:
 *      Nada(void)
 *
 */
void enqueue(Queue *qu, int x, int y)
{
    //alocação de memória para a estrutura que é para inserir na fila
    NodeQ *nd = (NodeQ *)malloc(sizeof(NodeQ));
    //verificação da alocação da memória
    if (nd == (NodeQ *)NULL)
        exit(0);
    //preencher os valores da estrutura com os valores passados como argumentos(x e y)
    nd->x = x;
    nd->y = y;
    //vai ser inserido no fim, por isso o seu next é null
    nd->next = NULL;
    //se a fila estiver vazia, os ponteiros para o inicio e para o fim ambos apontam para a estrutura criada agora
    if (is_empty(qu))
    {
        qu->head = nd;
        qu->tail = nd;
    }
    //se a fila não estiver vazia, insere no fim e atualiza o ponteiro para o fim da fila
    else
    {
        qu->tail->next = nd;
        qu->tail = nd;
    }
}


/*
 * Função: dequeue()
 * --------------------
 * 
 * Retorna os valores a estrutura no ínicio da fila e liberta a memória alocada para essa estrutura
 * Os valores não são retornados explicitamente, mas são copiados para um int[2] passado como argumento para a função
 * 
 * Argumentos:
 *
 *      Queue *qu: fila de onde é para retirar os valores que estão no ínicio da fila
 *      int *u: array de dois inteiros onde é para escrever o x e o y do NodeQ no ínicio da fila
 * 
 *  Return:
 *      Nada(void)
 *
 */
void dequeue(Queue *qu, int *u)
{
    //apenas se a fila não estiver vazia é que se faz alguma coisa
    if (!is_empty(qu))
    {
        //escreve x em u[0] e y em u[1]
        u[0] = qu->head->x;
        u[1] = qu->head->y;
        //liberta a memória alocada pela estrutura e atualiza o ponteiro para o inicio da fila
        NodeQ *tmp_NodeQ = qu->head;
        qu->head = tmp_NodeQ->next;
        free(tmp_NodeQ);
        if (qu->head == NULL)
            qu->tail = NULL;
    }
}