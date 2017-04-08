#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include "eps.h"
#include "file.h"

// command line app
// abre ficheiro
// calcula rota
// cria eps com cidades
// cria ficheiro rota (tour + cost)
// cria eps com rota grafica, texto tour + text cost + text date/time

#define DATAPATH_OUTPUT "./output"

typedef struct {
    int cidadeId;
    float x;
    float y;
} cidade;

/*
float calculaDistancia(cidade a, cidade b){
    return (float) sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)  );
}
*/

void printHelp() {
    printf("Uso: tsp -o directory \n\n");
    printf("Opção           Descrição\n");
    printf(" -h,--help      Lista completa de comandos\n");
    printf(" -o directory   Directoria onde se encontra os ficheiros de dados\n");
}

int main(int argc, char *argv[]) {
    int count;
    char *chrDataLocation;

    if (argc > 1) { /* Valida número de argumentos */

        for (count=1; count<argc; count++) {

            /* Valida opção --help */
            if ((strcmp(argv[count], "--help") == 0) || (strcmp(argv[count], "-h") == 0)) {
                printHelp();
                exit(EXIT_SUCCESS);
            }   /* Valida opção -o */
            else if ((strcmp(argv[count], "-o") == 0)) {

                if (count+1 < argc) {
                    chrDataLocation = argv[count+1];
                    printf("input %s \n", chrDataLocation);
                } else {
                    printf("Uso: -o [directory]\n");
                    exit(EXIT_SUCCESS);
                }
            }
        }

    }  else {
        printf("Uso: --help para uma lista completa de comandos.\n");
        exit(EXIT_SUCCESS);
    }

    return 0;
}