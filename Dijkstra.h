#ifndef DIJKSTRA
#define DIJKSTRA

void Dijkstra(int **Graph, int l, int c, int targetX, int targetY, FILE *fout);

void FreeGrid(int **grid, int l, int c);

#endif