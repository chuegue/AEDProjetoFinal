#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

/*
 * Função: InitStack()
 * --------------------
 *
 * Cria e retorna um ponteiro para um stack inicializado a null
 *
 * Argumentos:
 *
 *      Nenhum
 *
 *  Return:
 *      StackElement*: ponteiro para um stack
 *
 */
StackElement *InitStack()
{
    StackElement *S = NULL;
    return S;
}

/*
 * Função: Push()
 * --------------------
 *
 * Coloca no stack o x e o y introduzidos
 *
 * Argumentos:
 *
 *      StackElement **S: Ponteiro para um stack passado por referência onde é para colocar os valores fornecidos
 *      int x: valor de x que é para colocar no stack
 *      int y: valor de y que é para colocar no stack
 *
 *  Return:
 *      Nada(void)
 * 
 */
void Push(StackElement **S, int x, int y)
{   
    //cria uma estrutura para colocar no stack
    StackElement *new;
    //aloca memória para essa estrutura e verificar a alocação da memória
    if (!(new = (StackElement *)malloc(sizeof(StackElement))))
    {
        exit(0);
    }
    //põe os dados fornecidos no elemento que é para colocar na stack
    new->x = x;
    new->y = y;
    //elemento criado agora é a cabeça da stack
    new->next = (*S);
    (*S) = new;
    return;
}

/*
 * Função: Pop()
 * --------------------
 *
 * retorna os valores de x e y na primeira posição da stack
 *
 * Argumentos:
 *
 *      StackElement **S: Ponteiro para um stack passado por referência de onde é para retirar os valores no primeiro elemento da stack
 *      int *aux: array de 2 inteiros onde é para escrever os valores de x e y
 *
 *  Return:
 *  int *: array de 2 inteiros onde estão escritos os valores de x e y em aux[0] e aux[1] respetivamente OU null se a stack fornecida estiver vazia
 * 
 */
int *Pop(StackElement **S, int *aux)
{
    //so se a stack não estiver vazia é que se retira alguma coisa de lá
    if (!IsEmpty(*S))
    {
        //coloca o valor de x no inicio da stack em aux[0] e de y em aux[1]
        aux[0] = (*S)->x;
        aux[1] = (*S)->y;
        //liberta a memória alocada para a estrutura no inicio da stack e atualiza o ponteiro para o primeiro elemento da stack
        StackElement *temp = *S;
        *S = (*S)->next;
        free(temp);
        return aux;
    }
    //se a stack estiver vazia, retorna null
    return NULL;
}

/*
 * Função: IsEmpty()
 * --------------------
 *
 * Retorna 1 se a stack estiver vazia e 0 se não estiver
 *
 * Argumentos:
 *
 *      StackElement *S: stack fornecido que é para ser analisado se está vazio ou não     
 * 
 *  Return:
 *      int: retorna 1 ou 0
 * 
 */
int IsEmpty(StackElement *S)
{
    if (!S)
        return 1;
    return 0;
}

/*
 * Função: FreeStack()
 * --------------------
 *
 * Liberta a memória alocada para o stack
 *
 * Argumentos:
 *
 *      StackElement **S: Ponteiro para um stack passado por referência cuja memória é para ser libertada
 *
 *  Return:
 *      Nada(void)
 * 
 */
void FreeStack(StackElement **S)
{
    StackElement *temp = *S;
    //Percorre o stack todo
    while (temp)
    {
        //liberta o nó em que se está atualmente e passa para o próximo, se existir
        *S = (*S)->next;
        free(temp);
        temp = *S;
    }
}