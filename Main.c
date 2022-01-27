#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utilities.h"
#include "Variantes.h"

/*
 * Função: main()
 * --------------------
 * Ponto de Entrada do programa
 *
 * Argumentos:
 *
 *      int argc: número de argumentos passados na consola
 *      char *argv[]: tabela de strings que contém os argumentos passados na consola
 *
 *  Return:
 *      0: A função acaba sempre com código 0, seja bem sucedida ou não.
 *
 */
int main(int argc, char *argv[])
{
    char *FileNameIn;
    FILE *fp;

    //se só houver um argumento (  argc == 2  ) estamos na fase final
    if (argc == 2)
    {
        //se o argumento fornecido acabar em .in, continua. Senão, acaba a execução
        if (strstr(argv[1], ".in"))
        {
            //Alocar memória suficiente para ter "./<argumento>.sol\0"
            FileNameIn = (char *)calloc(strlen(argv[1]) + 4, sizeof(char));
            //verificação da alocação da memória
            if (!FileNameIn)
                exit(0);
            //FileNameIn = "./<argumento>"
            strcat(FileNameIn, "./");
            //fp é o apontador para o ficheiro de entrada, do qual se vão ler os dados
            fp = fopen(strcat(FileNameIn, argv[1]), "r");
            //aux é apontador para a última ocorrência do caracter '.'
            char *aux = strrchr(FileNameIn, '.');
            //coloca em aux a string ".sol"
            memcpy(aux, ".sol", 4);
            //põe o caracter '\0' no final da string
            FileNameIn[strlen(FileNameIn)] = '\0';
            //fout é o apontador para o ficheiro de saída, no qual se vai escrever
            FILE *fout = fopen(FileNameIn, "w");
            //se fp é null, então não existe nenhum ficheiro com o nome argv[1]
            if (!fp)
            {
                //remove o ficheiro criado apontado por fout
                remove(FileNameIn);
                //liberta a memória alocada para a string com o nome de entrada/saída do ficheiro
                free(FileNameIn);
                //fecha o ficheiro de saída
                fclose(fout);
                exit(0);
            }
            //é chamada a função que lê os dados em fp e escreve em fout os valores devidos
            ReadFileFinal(fp, fout);
            //fecha os valores pedidos
            fclose(fp);
            fclose(fout);
            //liberta a memória alocada para a string que com o nome de entrada/saída do ficheiro
            free(FileNameIn);
        }
        else
            exit(0);
    }
    //se houverem 2 argumentos (argc == 3) então estamos na fase intermédia
    else if (argc == 3)
    {
        //se o primeiro argumento for "-s" e o segundo for acabado em ".in1" continua. senão, sai do programa 
        if (!strcmp(argv[1], "-s") && strstr(argv[2], ".in1"))
        {
            //Alocar memória suficiente para ter "./<argumento>.sol1\0"
            FileNameIn = (char *)calloc(strlen(argv[2]) + 4, sizeof(char));
            //verificação da alocação da memória
            if (!FileNameIn)
                exit(0);
            //FileNameIn = "./<argumento>"
            strcat(FileNameIn, "./");
            //fp é o apontador para o ficheiro de entrada, do qual se vão ler os dados
            fp = fopen(strcat(FileNameIn, argv[2]), "r");
            //aux é apontador para a última ocorrência do caracter '.'
            char *aux = strrchr(FileNameIn, '.');
            //coloca em aux a string ".sol1"
            memcpy(aux, ".sol1", 6);
            //fout é o apontador para o ficheiro de saída, no qual se vai escrever
            FILE *fout = fopen(FileNameIn, "w");
            //se fp é null, então não existe nenhum ficheiro com o nome argv[1]
            if (!fp)
            {
                //remove o ficheiro criado apontado por fout
                remove(FileNameIn);
                //liberta a memória alocada para a string com o nome de entrada/saída do ficheiro
                free(FileNameIn);
                //fecha o ficheiro de saída
                fclose(fout);
                exit(0);
            }
            //é chamada a função que lê os dados em fp e escreve em fout os valores devidos
            ReadFileIntermedio(fp, fout);
            //fecha os valores pedidos
            fclose(fp);
            fclose(fout);
            //liberta a memória alocada para a string que com o nome de entrada/saída do ficheiro
            free(FileNameIn);
        }
        else
            exit(0);
    }
    else
        exit(0);

    exit(0);
}