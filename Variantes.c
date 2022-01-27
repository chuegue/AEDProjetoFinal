#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utilities.h"
#include "Stack.h"

/*
 * Função: Variante1()
 * --------------------
 *
 * Dada uma matriz int **grid e uma coordenada (x,y), escreve no ficheiro FILE *fout o valor da
 * célula ou -2 se a célula estiver fora da matriz
 *
 * Argumentos:
 *
 *      int** grid: matriz de inteiros
 *      int l: número de linhas da matriz
 *      int c: número de colunas da matriz
 *      int x: componente x da posição a analisar
 *      int y: componente y da posição a analisar
 *      FILE *fout: ficheiro de escrita do programa
 *
 *  Return:
 *      nada (void)
 *
 */

void Variante1(int **grid, int l, int c, int x, int y, FILE *fout)
{
    if (x - 1 < 0 || y - 1 < 0 || x - 1 > l - 1 || y - 1 > c - 1)
    {
        fprintf(fout, "-2\n\n");
        return;
    }
    fprintf(fout, "%i\n\n", grid[x - 1][y - 1]);
}

/*
 * Função: Variante3()
 * --------------------
 *
 * Dada uma matriz int **grid e uma coordenada (x,y), escreve no ficheiro FILE *fout 1 se a célula
 * tiver alguma célula vizinha cinzenta, 0 se não tiver e -2 se a célula estiver fora do labirinto
 *
 * Argumentos:
 *
 *      int** grid: matriz de inteiros
 *      int l: número de linhas da matriz
 *      int c: número de colunas da matriz
 *      int x: componente x da posição a analisar
 *      int y: componente y da posição a analisar
 *      FILE *fout: ficheiro de escrita do programa
 *
 *  Return:
 *      nada (void)
 *
 */

void Variante3(int **grid, int l, int c, int x, int y, FILE *fout)
{
    if (x - 1 < 0 || y - 1 < 0 || x - 1 > l - 1 || y - 1 > c - 1)
    {
        fprintf(fout, "-2\n\n");
        return;
    }
    x--;
    y--;
    int upx = x, upy = y - 1, rightx = x + 1, righty = y, downx = x, downy = y + 1, leftx = x - 1, lefty = y;
    if (upx < l && upx >= 0 && upy < c && upy >= 0 && grid[upx][upy] > 0)
    {
        fprintf(fout, "1\n\n");
        return;
    }
    if (downx < l && downx >= 0 && downy < c && downy >= 0 && grid[downx][downy] > 0)
    {
        fprintf(fout, "1\n\n");
        return;
    }
    if (leftx < l && leftx >= 0 && lefty < c && lefty >= 0 && grid[leftx][lefty] > 0)
    {
        fprintf(fout, "1\n\n");
        return;
    }
    if (rightx < l && rightx >= 0 && righty < c && righty >= 0 && grid[rightx][righty] > 0)
    {
        fprintf(fout, "1\n\n");
        return;
    }
    fprintf(fout, "0\n\n");
}

/*
 * Função: Variante5()
 * --------------------
 *
 * Dada uma matriz int **grid e uma coordenada (x,y), escreve no ficheiro FILE *fout 1 se a célula
 * for cinzenta e quebrável, 0 se for cinzenta e não quebrável, -1 se não for cinzenta
 * e -2 se a célula estiver fora do labirinto
 *
 * Argumentos:
 *
 *      int** grid: matriz de inteiros
 *      int l: número de linhas da matriz
 *      int c: número de colunas da matriz
 *      int x: componente x da posição a analisar
 *      int y: componente y da posição a analisar
 *      FILE *fout: ficheiro de escrita do programa
 *
 *  Return:
 *      nada (void)
 *
 */

void Variante5(int **grid, int l, int c, int x, int y, FILE *fout)
{
    if (x - 1 < 0 || y - 1 < 0 || x - 1 > l - 1 || y - 1 > c - 1)
    {
        fprintf(fout, "-2\n\n");
        return;
    }
    if (grid[x - 1][y - 1] == -1 || grid[x - 1][y - 1] == 0)
    {
        fprintf(fout, "-1\n\n");
        return;
    }
    x--;
    y--;
    int upx = x, upy = y - 1, rightx = x + 1, righty = y, downx = x, downy = y + 1, leftx = x - 1, lefty = y;
    if ((upx < l && upx >= 0 && upy < c && upy >= 0 && grid[upx][upy] == 0 &&
         downx < l && downx >= 0 && downy < c && downy >= 0 && grid[downx][downy] == 0) ||
        (leftx < l && leftx >= 0 && lefty < c && lefty >= 0 && grid[leftx][lefty] == 0 &&
         rightx < l && rightx >= 0 && righty < c && righty >= 0 && grid[rightx][righty] == 0))
    {
        fprintf(fout, "1\n\n");
        return;
    }
    fprintf(fout, "0\n\n");
}

/*
 * Função: CheckNeighbours()
 * --------------------
 *
 * Esta função implementa as variantes 2 e 4. Dada uma matriz int **grid, uma coordenada (x,y) e um tipo de célula int color, a funçáo
 * escreve 1 no ficheiro FILE *fout se algum dos vizinhos da célula for igual a color, 0 se nenhum dos vizinhos for igual a color e -2 se
 * a célula estiver fora do labirinto
 *
 * Argumentos:
 *
 *      int** grid: matriz de inteiros
 *      int l: número de linhas da matriz
 *      int c: número de colunas da matriz
 *      int x: componente x da posição a analisar
 *      int y: componente y da posição a analisar
 *      FILE *fout: ficheiro de escrita do programa
 *      int color: tipo de célula a testar
 *
 *  Return:
 *      nada (void)
 *
 */

void CheckNeighbours(int **grid, int l, int c, int x, int y, FILE *fout, int color)
{
    if (x - 1 < 0 || y - 1 < 0 || x - 1 > l - 1 || y - 1 > c - 1)
    {
        fprintf(fout, "-2\n\n");
        return;
    }
    x--;
    y--;
    Neighbours arround = DefineArround(x, y, l, c);
    if ((arround.up[1] != -10) && (arround.up[0] != -10))
    {
        if (grid[arround.up[0]][arround.up[1]] == color)
        {
            fprintf(fout, "1\n\n");
            return;
        }
    }
    if ((arround.down[1] != -10) && (arround.down[0] != -10))
    {
        if (grid[arround.down[0]][arround.down[1]] == color)
        {
            fprintf(fout, "1\n\n");
            return;
        }
    }
    if ((arround.left[1] != -10) && (arround.left[0] != -10))
    {
        if (grid[arround.left[0]][arround.left[1]] == color)
        {
            fprintf(fout, "1\n\n");
            return;
        }
    }
    if ((arround.right[1] != -10) && (arround.right[0] != -10))
    {
        if (grid[arround.right[0]][arround.right[1]] == color)
        {
            fprintf(fout, "1\n\n");
            return;
        }
    }
    fprintf(fout, "0\n\n");
}

/*
 * Função: Variante6()
 * --------------------
 *
 * Dada uma matriz int **grid, uma coordenada (x1,y1) e  uma coordenada(x2,y2), a funçáo
 * escreve 1 no ficheiro FILE *fout se as duas células estiverem na mesma sala (se for possível ir de uma célula à outra sem quebrar paredes),
 * 0 se não estriverem na mesma sala e -2 se alguma das células estiver fora do labirinto
 *
 * Argumentos:
 *
 *      int** grid: matriz de inteiros
 *      int l: número de linhas da matriz
 *      int c: número de colunas da matriz
 *      int x1: componente x da posição da primeira célula a analisar
 *      int y1: componente y da posição da primeira célula a analisar
 *      int x2: componente x da posição da segunda célula a analisar
 *      int y2: componente y da posição da segunda célula a analisar
 *      FILE *fout: ficheiro de escrita do programa
 *
 *  Return:
 *      nada (void)
 *
 */

void Variante6(int **grid, int l, int c, int x1, int y1, int x2, int y2, FILE *fout)
{
    x1--;
    x2--;
    y1--;
    y2--;
    if (x1 < 0 || y1 < 0 || x1 > l - 1 || y1 > c - 1)
    {
        fprintf(fout, "-2\n\n");
        return;
    }
    if (x2 < 0 || y2 < 0 || x2 > l - 1 || y2 > c - 1)
    {
        fprintf(fout, "-2\n\n");
        return;
    }
    if (grid[x1][y1] != 0 || grid[x2][y2] != 0)
    {
        fprintf(fout, "0\n\n");
        return;
    }
    int aux[2];
    char **visited;
    int dx[] = {0, 1, -1, 0};
    int dy[] = {1, 0, 0, -1};

    if (!(visited = (char **)malloc(l * sizeof(char *))))
        exit(0);
    for (int i = 0; i < l; i++)
        if (!(visited[i] = (char *)malloc(c * sizeof(char))))
            exit(0);

    for (int i = 0; i < l; i++)
        for (int j = 0; j < c; j++)
            visited[i][j] = 'F';

    //----------------DFS---------------------------
    /*
     *   REFERENCIA: https://en.wikipedia.org/wiki/Depth-first_search
     */
    // procedure DFS_iterative(grafo G, vertice v) is
    // let S be a stack
    StackElement *S = InitStack();
    // S.push(v)
    Push(&S, x1, y1);
    // while S is not empty do
    while (!IsEmpty(S))
    {
        // v = S.pop()
        Pop(&S, aux);
        x1 = aux[0];
        y1 = aux[1];
        // if v is not labeled as discovered then
        if (visited[x1][y1] == 'F')
        {
            // label v as discovered
            visited[x1][y1] = 'V';
            // for all edges from v to w in G.adjacentEdges(v) do
            int auxX = 0, auxY = 0;
            for (int i = 0; i < 4; i++)
            {
                auxX = x1 + dx[i];
                auxY = y1 + dy[i];
                if (auxX == x2 && auxY == y2)
                {
                    for (int i = 0; i < l; i++)
                        free(visited[i]);
                    free(visited);
                    fprintf(fout, "1\n\n");
                    FreeStack(&S);
                    return;
                }
                if (!(auxX < 0 || auxY < 0 || auxX > l - 1 || auxY > c - 1))
                {
                    // S.push(w)
                    if (grid[auxX][auxY] == 0)
                        Push(&S, auxX, auxY);
                }
            }
        }
    }
    for (int i = 0; i < l; i++)
        free(visited[i]);
    free(visited);
    fprintf(fout, "0\n\n");
    FreeStack(&S);
    return;
}
