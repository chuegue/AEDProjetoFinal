#include <stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "MinHeap.h"
#include "List.h"
#include "Queue.h"

#define INFINITY 1147483647

typedef struct
{
    int V;
    int W;
    int x;
    int y;
} Edge;
typedef struct
{
    int N;
    LinkedList **V;
} Graph;

// liberta a memória alocada por uma tabela bi-dimensional
void FreeGrid(int **grid, int l, int c)
{

    for (int i = 0; i < l; i++)
        free(grid[i]);
    free(grid);
}

// aloca memória e retorna um ponteiro para uma estrutura Graph inicializada
Graph *InitGraph(int n)
{
    // Alocação do grafo
    Graph *g = (Graph *)malloc(sizeof(Graph));
    if (g != (Graph *)NULL)
    {
        // Insereção dos dados do grafo
        g->N = n;
        // Alocação e inicialização da lista de adjacências
        g->V = (LinkedList **)malloc(n * sizeof(LinkedList *));
        if (g->V != (LinkedList **)NULL)
        {
            for (int i = 0; i < n; i++)
            {
                g->V[i] = (LinkedList *)initLinkedList();
            }
        }
        else
            exit(0);
    }
    else
        exit(0);
    return g;
}

/*
 * Função: InsertEdge()
 * --------------------
 *
 *  Dado um grafo g, insere um "Edge" entre v1 e v2 se o Edge não existir. Caso já exista ligação
 *  apenas insere se o peso de "Edge" exkstente for maior do que estamos a tentar inserir.
 *
 * Argumentos:
 *
 *      Graph *g: grafo
 *      int l: número de linhas da matriz
 *      int c: número de colunas da matriz
 *  Return:
 *      nada (void)
 *
 */
void InsertEdge(Graph *g, int v1, int v2, int w, int x, int y)
{
    // Alocação dos Edges
    Edge *this = (Edge *)malloc(sizeof(Edge));
    Edge *that = (Edge *)malloc(sizeof(Edge));
    // Se não for possível alocar memória, exit(0)
    if (this == (Edge *)NULL || that == (Edge *)NULL)
        exit(0);
    // Atribuição dos parâmetros às Edges
    this->V = v1;
    that->V = v2;
    this->W = w;
    that->W = w;
    this->x = x;
    that->x = x;
    this->y = y;
    that->y = y;

    // Procura o vértice na lista.
    LinkedList *aux = g->V[v1];
    int flag = 0;
    // Loop que percorre toda a list de adjacência à procura do vértice que pretendemos adicionar
    while (aux)
    {
        // Caso exista, a flag passa a 1
        if (((Edge *)getItemLinkedList(aux))->V == v2)
        {
            flag = 1;
            break;
        }

        aux = getNextNodeLinkedList(aux);
    }
    // Caso flag = 0 (Edge não existe): insere no inicio da lista
    if (!flag)
    {
        g->V[v1] = insertUnsortedLinkedList(g->V[v1], (Item)that);
    }
    // Caso flag = 1 (Edge existe): verifica se o peso da Edge que estamos a tentar existir é maior que
    // o peso da Edge que já está inserida.
    else
    {
        if (((Edge *)getItemLinkedList(aux))->W > w)
        {
            SetItemLinkedList(aux, (Item)that);
        }
        else
        {
            free(that);
        }
    }
    // Repete o processo para o vértice 2
    aux = g->V[v2];
    flag = 0;
    while (aux)
    {
        if (((Edge *)getItemLinkedList(aux))->V == v1)
        {
            flag = 1;
            break;
        }

        aux = getNextNodeLinkedList(aux);
    }
    if (!flag)
    {
        g->V[v2] = insertUnsortedLinkedList(g->V[v2], (Item)this);
    }
    else
    {
        if (((Edge *)getItemLinkedList(aux))->W > w)
        {
            SetItemLinkedList(aux, (Item)this);
        }
        else
        {
            free(this);
        }
    }
}

/*
 * Função: FreeGraph()
 * --------------------
 *
 *  Liberta a memória alocada para um grafo representado em lista de adjacência
 *
 * Argumentos:
 *
 *      Graph *g: grafo
 *
 *  Return:
 *      nada (void)
 *
 */
void FreeGraph(Graph *g)
{
    // Liberta a memória da lista correspondente a cada vérice, sendo N o número de vértices do grafo
    for (int i = 0; i < g->N; i++)
    {
        freeLinkedList(g->V[i], free);
    }
    free(g->V);
    free(g);
}

/*
 * Função: ValidateCoordinates()
 * --------------------
 *
 *  Avalia se as coordenada recebidas são válidas, ou seja, se estão dentro da matriz
 *
 * Argumentos:
 *
 *      Graph *g: grafo
 *      int l: número de linhas da matriz
 *      int c: número de colunas da matriz
 *      int x: componente x da posição a analisar
 *      int y: componente y da posição a analisar
 *
 *  Return:
 *      Retorna o inteiro 1 se as coordenadas estão dentro da matriz, 0 caso contrário
 *
 */
int ValidateCoordinates(int x, int y, int l, int c)
{
    return !(x < 0 || x >= l || y < 0 || y >= c);
}

/*
 * Função: MakeRoom()
 * --------------------
 *
 *  Dada a matriz de entrada e um x e y tal que grid[x][y] = 0, a função vai percorrer a
 *  matriz com o algoritmo breath-first search através de todos os pontos da matriz que
 *  são zero e pintar esses pontos com o valor correspondente. A sala nº 0 vai ser pintada
 *  com -2, a nº1 com -3 e pela mesma lógcia até não haver mais zeros.
 *
 * Argumentos:
 *
 *      int** grid: matriz de inteiros
 *      int l: número de linhas da matriz
 *      int c: número de colunas da matriz
 *      int x: componente x da posição a analisar
 *      int y: componente y da posição a analisar
 *      int nRooms: número de salas já "pintadas"
 *
 *  Return:
 *      Retorna o número de salas já "pintadas" que vai ser mais um que o valor de nRooms
 *      inicialmente recebido como argumento.
 *
 */
int MakeRoom(int **grid, int x, int y, int l, int c, int nRooms)
{
    // Valor com que é para pintar a sala em questão
    int nSala = -2 - nRooms;
    nRooms++; // Incrementa o número de salas "pintadas"
    int v[2], wx, wy;
    int dx[] = {0, 1, -1, 0};
    int dy[] = {1, 0, 0, -1};

    //----------------- BFS -----------------
    Queue *Q = create_queue(); // Inicia Queue para a implementação do algoritmo BFS
    grid[x][y] = nSala;        // Pinta a célula (x, y) com o valor correspondente
    enqueue(Q, x, y);          // Adiciona (x, y) à Queue

    while (!is_empty(Q))
    {
        dequeue(Q, v);
        // Vê todos os vizinhos de v
        for (int i = 0; i < 4; i++)
        {
            wx = v[0] + dx[i];
            wy = v[1] + dy[i];
            // Analisa se as coordenadas de w são válidas, se não forem não vale a pena adicionar na queue para as analisar
            if (!ValidateCoordinates(wx, wy, l, c))
                continue;
            // Vê se a célula é diferente de 0, como só temos interesse em "pintar" as células
            // zero, prosseguimos para avaliar o próximo vizinho
            if (grid[wx][wy] != 0)
                continue;
            // Só se for 0 e válida é que vai ser pintada e adicionada á Queue
            grid[wx][wy] = nSala; // Pinta a célula
            enqueue(Q, wx, wy);   // Adiciona à queue
        }
    }
    free(Q); // Liberta a memória alocada para a estrutura da queue
    return nRooms;
}

/*
 * Função: CheckBreakableX()
 * --------------------
 *
 *      Vê se as coordenadas são quebráveis no eixo dos x
 *
 * Argumentos:
 *
 *      int** grid: matriz de inteiros
 *      int l: número de linhas da matriz
 *      int c: número de colunas da matriz
 *      int x: componente x da posição a analisar
 *      int y: componente y da posição a analisar
 *      int nRooms: número de salas já "pintadas"
 *
 *  Return:
 *      Retorna 1 se a parede
 *
 */
int CheckBreakableX(int **grid, int x, int y, int l, int c)
{
    int upx = x - 1, upy = y, downx = x + 1, downy = y;
    // Vê se a coordenada fornecida é válida
    if (!ValidateCoordinates(upx, upy, l, c) || !ValidateCoordinates(downx, downy, l, c))
        return 0;
    // Vê se as coordenadas acima e abaixo das coordenadas fornecidas são ambas "salas" (neste ponto são casas abaixo de -1)
    if ((grid[upx][upy] == 0 || grid[upx][upy] < -1) && (grid[downx][downy] == 0 || grid[downx][downy] < -1))
        return 1;
    return 0;
}

/*
 * Função: CheckBreakableY()
 * --------------------
 *
 *      Vê se as coordenadas são quebráveis no eixo dos y
 *
 * Argumentos:
 *
 *      int** grid: matriz de inteiros
 *      int l: número de linhas da matriz
 *      int c: número de colunas da matriz
 *      int x: componente x da posição a analisar
 *      int y: componente y da posição a analisar
 *
 *  Return:
 *      Retorna 1 se a parede
 *
 */
int CheckBreakableY(int **grid, int x, int y, int l, int c)
{
    int leftx = x, lefty = y - 1, rightx = x, righty = y + 1;
    // Vê se a coordenada fornecida é válida
    if (!ValidateCoordinates(leftx, lefty, l, c) || !ValidateCoordinates(rightx, righty, l, c))
        return 0;
    // Vê se as coordenadas à esquerda e à direita das coordenadas fornecidas são ambas "salas" (neste ponto são casas abaixo de -1)
    if ((grid[leftx][lefty] == 0 || grid[leftx][lefty] < -1) && (grid[rightx][righty] == 0 || grid[rightx][righty] < -1))
        return 1;
    return 0;
}

/*
 * Função: MatrixToGraph()
 * --------------------
 *
 *      Recebe a matriz com as salas já "pintadas" e, a partir daí, constrói um grafo representado por uma
 *      lista de adjacências. A função recebe um (x, y) cuja grid[x][y] < -1 indicando que são coordenadas
 *      dentro de uma sala e prossegue analisando os seus vizinhos.
 *
 * Argumentos:
 *
 *      int** grid: matriz de inteiros
 *      int l: número de linhas da matriz
 *      int c: número de colunas da matriz
 *      int x: componente x da posição a analisar
 *      int y: componente y da posição a analisar
 *      Graph *g: grafo
 *
 *  Return:
 *      nada (void)
 *
 */
void MatrixToGraph(int **grid, int x, int y, int l, int c, Graph *g)
{
    int v[2], wx, wy;
    int dx[] = {0, 1, -1, 0};
    int dy[] = {1, 0, 0, -1};
    int nextRoom = 0;
    int value = grid[x][y];
    Queue *Q = create_queue();
    grid[x][y] = 0;
    enqueue(Q, x, y);
    while (!is_empty(Q))
    {
        dequeue(Q, v);
        for (int i = 0; i < 4; i++)
        {
            wx = v[0] + dx[i];
            wy = v[1] + dy[i];
            // Vê se as coordenadas estão dentro da matriz e se são quebráveis
            if (!ValidateCoordinates(wx, wy, l, c) || grid[wx][wy] == -1)
                continue;
            // Se for uma parede
            if (grid[wx][wy] > 0)
            {
                // Verifica se é quebrável na direção do vizinho que estamos a analisar
                if (((CheckBreakableX(grid, wx, wy, l, c) && dx[i] != 0) || (CheckBreakableY(grid, wx, wy, l, c) && dy[i] != 0)))
                {
                    // Se estivermos a ver um vizinho horizontal, o valor da sala seguinte é igual ao valor da célula
                    // à direita (para dx = 1) ou à esquerda (para dx = -1)
                    if (dx[i] != 0)
                    {
                        nextRoom = grid[wx + dx[i]][wy];
                    }
                    // Se estivermos a ver um vizinho vertical, o valor da sala seguinte é igual ao valor da célula
                    // em baixo (para dy = 1) ou em cima (para dy = -1) do vizinho
                    else if (dy[i] != 0)
                    {
                        nextRoom = grid[wx][wy + dy[i]];
                    }
                    // Caso exista sala adjacente (célula diferente de 0, não vista anteriormente), adiciona
                    // "Edge" com vértice igual módulo do ao valor da sala mais 2 (assim, a primeira
                    // sala com valor -2 corresponde ao vértice 0), vértice 2 igual ao valor da sala
                    // ao lado, "weight" igual ao valor da sala que quebrámos e com as coordenadas da célula que quebrámos
                    if (nextRoom)
                        InsertEdge(g, (value + 2) * -1, (nextRoom + 2) * -1, grid[wx][wy], wx, wy);
                }
            }
            else
            {
                // Se o vizinho pertencer à mesma sala da célula que está a ser analisada
                if (grid[wx][wy] == value)
                    enqueue(Q, wx, wy);
                grid[wx][wy] = 0; // Volta a marcar como 0, indicando que já foi visitado
            }
        }
    }
    free(Q); // Liberta a memória alocada para a estrutura da queue
}

/*
 * Função: getWeightEdge()
 * --------------------
 *
 *      _
 *
 * Argumentos:
 *
 *      Linked List *node:
 *      int v:
 *
 *  Return:
 *      _
 *
 */
int getWeightEdge(LinkedList *node, int v)
{
    LinkedList *aux = node;
    while (aux)
    {
        if (((Edge *)getItemLinkedList(aux))->V == v)
        {
            return (((Edge *)getItemLinkedList(aux))->W);
        }
        aux = getNextNodeLinkedList(aux);
    }
    return 0;
}

Edge *getEdge(LinkedList *node, int v)
{
    LinkedList *aux = node;
    while (aux)
    {
        if (((Edge *)getItemLinkedList(aux))->V == v)
        {
            return (((Edge *)getItemLinkedList(aux)));
        }
        aux = getNextNodeLinkedList(aux);
    }
    return NULL;
}

/*
 * Função: TotalWalls()
 * --------------------
 *
 *      Conta o número de paredes quebradas.
 *
 * Argumentos:
 *
 *      *prev: ponteiro para o vetor que guarda a sala de que veio cada vértice do grafo
 *      int target: vértice do grafo correspondente ao destino
 *
 *  Return:
 *      Número total de paredes quebradas.
 *
 */
int TotalWalls(int *prev, int target)
{
    int n = 0;

    while (prev[target] != -1)
    {
        n++;
        target = prev[target];
    }
    return n;
}

void ReconstructPath(FILE *fout, int *prev, int target, Graph *g)
{
    if (prev[target] == -1)
        return;
    ReconstructPath(fout, prev, prev[target], g);
    fprintf(fout, "%i %i %i\n", getEdge(g->V[target], prev[target])->x + 1, getEdge(g->V[target], prev[target])->y + 1, getWeightEdge(g->V[target], prev[target]));
}

// Instead of filling the priority queue with all nodes in the initialization phase,
//  it is also possible to initialize it to contain only source; then, inside the if alt < dist[v] block,
// the decrease_priority() becomes an add_with_priority() operation if the node is not already in the queue

void Dijkstra(int **grid, int l, int c, int targetX, int targetY, FILE *fout)
{

    // Se as coordenadas de destino estão fora da matriz, forem igual à origem ou corresponderem a uma célula diferente de zero ou se as
    // coordenadas de origem não estiverem dentro de uma sala, imprime -1 no ficheiro de saída
    if (!ValidateCoordinates(targetX, targetY, l, c) || (targetX == 0 && targetY == 0) || (grid[0][0] != 0) || grid[targetX][targetY] != 0)
    {
        fprintf(fout, "-1\n\n");
        FreeGrid(grid, l, c); // Liberta a memória alocada para a matriz
        return;
    }

    int nRooms = 0; // Número de salas (áreas com apenas células zero) na matriz
    // Loop que percorre a matriz para criar as salas
    for (int j = 0; j < c; j++)
    {
        for (int i = 0; i < l; i++)
        {
            if (grid[i][j] == 0)
            {
                nRooms = MakeRoom(grid, i, j, l, c, nRooms);
            }
        }
    }
    // Neste ponto as salas já estão criadas e, consequentemente, as células que, inicialmente tinham valor zero, têm agora valores menores que -1

    int target = grid[targetX][targetY]; // target vai ter o valor da sala a que pertence
    // Se o target tiver na mesma sala que a origem, não é necessário quebrar nenhuma parede e como tal imprime 0 no ficheiro de saída
    if (grid[0][0] == target)
    {
        fprintf(fout, "0\n\n");
        FreeGrid(grid, l, c); // Liberta a memória alocada para a matriz
        return;
    }

    // Nos restantes casos, isto é, quando o destino é válido e não está na mesma sala que a origem, teremos de utilizar o grafo representado em
    // lista de adjacências para encontrar o caminho de menor custo
    target = (target + 2) * -1;       // target vai ter o valor do vértice no grafo
    Graph *graph = InitGraph(nRooms); // Inicializa-se o grafo com o número de salas

    // Loop vai transformar a matriz em grafo
    for (int j = 0; j < c; j++)
    {
        for (int i = 0; i < l; i++)
        {
            if (grid[i][j] < -1)
                MatrixToGraph(grid, i, j, l, c, graph);
        }
    }

    //----------------- DIJKSTRA -----------------

    // Inicialização dos vetores necessários à implememtação do algortimo
    int *dist = (int *)malloc(nRooms * sizeof(int)); // Guarda as distâncias desde o vértice inicial para os outros vértices
    if (dist == (int *)NULL)
        exit(0);
    int *prev = (int *)malloc(nRooms * sizeof(int)); // Guarda de que sala veio para cada vértice
    if (prev == (int *)NULL)
        exit(0);

    dist[0] = 0;                         // Distância da origem é inicializada a 0
    prev[0] = -1;                        // Previous vértice é inicializado a -1 (indefinidos)
    MinHeap *heap = InitMinHeap(nRooms); // Iniciliza-se o asservo com o número de salas

    for (int i = 1; i < nRooms; i++) // Inicialmente todas as distâncias desde o vértice inicial são INFINITY e todos os previous são -1 (indefinidos)
    {
        dist[i] = INFINITY;
        prev[i] = -1;
    }
    InsertMinHeap(heap, 0, dist[0]); // Adiciona-se o vértice inicial ao asservo
    while (!HeapIsEmpty(heap))
    {
        int u = GetMin(heap); // Dá o vértice com maior prioridade, ou seja, menor distância
        if (u == target)      // Se o vértice for o vértice de destino, já encontrámos o caminho mais curto
            break;
        LinkedList *aux = graph->V[u]; // aux aponta para o primeiro vizinho do vertice u
        while (aux)                    // Analisando todos os vizinhos do vértice u
        {
            int v = ((Edge *)getItemLinkedList(aux))->V; // v vai ser o vértice vizinho que está a ser analisado
            int alt = dist[u] + getWeightEdge(aux, v);   // alta é a distância da origem ao vizinho v passando por u

            // Se o caminho passando por u é mais curto do que o caminho que já la está, dist[v] passa a guardar o valor de alt e prev[v]
            // passa a guardar o vértice u, uma vez que o caminho mais curto da origem até v, encontrado até ao momento foi passando por u
            if (alt < dist[v])
            {
                dist[v] = alt;
                prev[v] = u;
                if (!IsInHeap(heap, v))
                {
                    InsertMinHeap(heap, v, alt);
                }
                else
                {
                    ChangePriority(heap, v, alt);
                }
            }
            aux = getNextNodeLinkedList(aux); // aux passa a apontar para o próximo vizinho de u
        }
    }

    int IsReachable = dist[target] - INFINITY;
    if (IsReachable == 0) // Caso em que dist[target] é infinito, apenas acontce quando é impossível chegar ao target
    {
        fprintf(fout, "-1\n");
    }
    // Quando é preciso quebrar paredes para ir da origem ao destino, temos de imprimir no ficheiro de saída o custo do caminho com menos custo,
    // o número de paredes quebradas e quais paredes quebradas
    else
    {
        fprintf(fout, "%i\n", dist[target]);             // dist[target] tem o valor do caminho com menos custo
        fprintf(fout, "%i\n", TotalWalls(prev, target)); // TotalWalls devolve o número de paredes quebradas
        ReconstructPath(fout, prev, target, graph);      // ReconstructWalls imprime todas as células quebradas e o seu custo
    }
    fprintf(fout, "\n");
    FreeHeap(heap);       // Liberta a memória alocada para o asservo
    FreeGraph(graph);     // Liberta a memória alocada para o grafo
    free(dist);           // Liberta a memória do vetor das distâncias
    free(prev);           // Liberta a memória do vetor das salas anteriores
    FreeGrid(grid, l, c); // Libert a memória da matriz do labirinto
}