#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utilities.h"
#include "Variantes.h"
#include "Dijkstra.h"

/*
 * Função: InitGrid()
 * --------------------
 *
 * Dado um l e c, dimensões da
 *
 * Argumentos:
 *
 *      int** grid: matriz de inteiros para alocar
 *      int l: número de linhas da matriz
 *      int c: número de colunas da matriz
 *  Return:
 *      int**: ponteiro para a matriz alocada
 *
 */

int **InitGrid(int l, int c)
{
    int **grid;
    if (!(grid = (int **)malloc(l * sizeof(int *))))
        exit(0);

    for (int i = 0; i < l; i++)
        if (!(grid[i] = (int *)calloc(c, sizeof(int))))
            exit(0);
    return grid;
}

/*
 * Função: DefineArround()
 * --------------------
 *
 *  Dada uma matriz int **grid com l linhas e c colunas e uma posição (x,y), a função devolve as
 *  posições das células vizinhas dessa posição numa struct. Caso um dos vizinhos esteja fora do
 *  tabuleiro, a posição devolvida desse vizinho é uma posição inválida (-10,-10)
 *
 * Argumentos:
 *
 *      int** grid: matriz de inteiros
 *      int x: componente x da posição a analisar
 *      int y: componente y da posição a analisar
 *      int l: número de linhas da matriz
 *      int c: número de colunas da matriz
 *  Return:
 *      Neighbours arround: struct com as posições respetivas dos vizinhos das células
 *
 */

Neighbours DefineArround(int x, int y, int c, int l)
{
    Neighbours arround;
    if (x < c && x >= 0 && (y - 1) < l && (y - 1) >= 0)
        arround.up[0] = x, arround.up[1] = y - 1;
    else
        arround.up[0] = -10, arround.up[1] = -10;

    if (x < c && x >= 0 && (y + 1) < l && (y + 1) >= 0)
        arround.down[0] = x, arround.down[1] = y + 1;
    else
        arround.down[0] = -10, arround.down[1] = -10;

    if ((x - 1) < c && (x - 1) >= 0 && y < l && y >= 0)
        arround.left[0] = x - 1, arround.left[1] = y;
    else
        arround.left[0] = -10, arround.left[1] = -10;

    if ((x + 1) < c && (x + 1) >= 0 && y < l && y >= 0)
        arround.right[0] = x + 1, arround.right[1] = y;
    else
        arround.right[0] = -10, arround.right[1] = -10;

    return arround;
}

/*
 * Função: ReadFileIntermedio()
 * --------------------
 *
 *  Função principal do programa, a seguir à main. Esta função lê os conteúdos do ficheiro FILE *fp e processa os dados
 *  lidos com as regras da Entrega Intermédia
 *
 * Argumentos:
 *
 *      FILE *fp: ficheiro de leitura
 *      FILE *fout: ficheiro de escrita
 *  Return:
 *      nada (void)
 *
 */

void ReadFileIntermedio(FILE *fp, FILE *fout)
{
    int **labirinto;
    int targetX1, targetY1, targetX2, targetY2, l, c, n = 0;
    char variante[4];
    // lê ficheiro enquanto houver labirintos
    // lê a descrição do labirinto, começando pelos nºs de linhas e colunas, seguido pela primeira célula em qual é suposto fazer um teste, seguido da variante
    while (fscanf(fp, "%i %i %i %i %s", &l, &c, &targetX1, &targetY1, variante) == 5)
    {
        // se a variante lida for a A6, lê a segunda célula, que é a célula destino na variante A6
        if (!strcmp(variante, "A6"))
        {
            if (fscanf(fp, "%i %i", &targetX2, &targetY2) != 2)
                exit(0);
        }
        //lê o número de paredes pretas ou cinzentas que o labirinto tem
        if (fscanf(fp, "%i", &n) != 1)
            exit(0);
        //inicializa a matriz com o labirinto
        labirinto = InitGrid(l, c);
        int x = 0, y = 0, value = 0;
        //lê as n paredes na descrição do labirinto e coloca os valores na posição respetiva da matriz
        for (int i = 0; i < n; i++)
            if (fscanf(fp, "%i %i %i", &x, &y, &value))
                labirinto[--x][--y] = value;
            else
                exit(0);
        //de acordo com a variante pedida no ficheiro, vai ser chaamada a função respetiva
        if (!strcmp(variante, "A1"))
            Variante1(labirinto, l, c, targetX1, targetY1, fout);
        else if (!strcmp(variante, "A2") || !strcmp(variante, "A4"))
            CheckNeighbours(labirinto, l, c, targetX1, targetY1, fout, 0);
        else if (!strcmp(variante, "A3"))
            Variante3(labirinto, l, c, targetX1, targetY1, fout);
        else if (!strcmp(variante, "A5"))
            Variante5(labirinto, l, c, targetX1, targetY1, fout);
        else if (!strcmp(variante, "A6"))
            Variante6(labirinto, l, c, targetX1, targetY1, targetX2, targetY2, fout);
        //libertação da memória alocada para a matriz com o labirinto
        FreeGrid(labirinto, l, c);
    }
}

/*
 * Função: ReadFileFinal()
 * --------------------
 *
 *  Função principal do programa, a seguir à main. Esta função lê os conteúdos do ficheiro FILE *fp e processa os dados
 *  lidos com as regras da Entrega Final
 *
 * Argumentos:
 *
 *      FILE *fp: ficheiro de leitura
 *      FILE *fout: ficheiro de escrita
 *  Return:
 *      nada (void)
 *
 */
void ReadFileFinal(FILE *fp, FILE *fout)
{
    int **labirinto;
    int targetX, targetY, l, c, n = 0;
    //lê ficheiro enquanto houver labirintos
    //lê a descrição do labirinto, começando pelos nºs de linhas e colunas, seguido pela célula de destino e o nº de paredes cinzentas ou pretas
    while (fscanf(fp, "%i %i %i %i %i", &l, &c, &targetX, &targetY, &n) == 5)
    {
        //inicializa a matriz que vai guardar o labirinto
        labirinto = InitGrid(l, c);
        int x = 0, y = 0, value = 0;
        //lê as n paredes que há no labirinto e coloca as na posição respetiva
        for (int i = 0; i < n; i++)
            if (fscanf(fp, "%i %i %i", &x, &y, &value))
                labirinto[--x][--y] = value;
        //chama a função que vai dar o caminho com menor custo da célula (1,1) à célula (targetX, targetY) 
        Dijkstra(labirinto, l, c, --targetX, --targetY, fout);
    }
}