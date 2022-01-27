#ifndef VARIANTES
#define VARIANTES

void Variante1(int **grid, int l, int c, int x, int y, FILE *fout);

void Variante3(int **grid, int l, int c, int x, int y, FILE *fout);

void CheckNeighbours(int **grid, int l, int c, int x, int y, FILE *fout, int color);

void Variante5(int **grid, int l, int c, int x, int y, FILE *fout);

void Variante6(int **grid, int l, int c, int x1, int y1, int x2, int y2, FILE *fout);
#endif