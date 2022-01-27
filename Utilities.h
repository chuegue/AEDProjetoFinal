#ifndef UTILITIES
#define UTILITIES

typedef struct
{
    int up[2];
    int down[2];
    int right[2];
    int left[2];
} Neighbours;

int **InitGrid(int l, int c);

void FreeGrid(int **, int, int);

Neighbours DefineArround(int x, int y, int c, int l);

void ReadFileIntermedio(FILE *fp, FILE *fout);

void ReadFileFinal(FILE *fp, FILE *fout);

#endif