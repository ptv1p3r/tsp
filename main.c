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

typedef struct cidade{
    int id;
    float x;
    float y;
    int visited;
} cidade;


float calculaDistancia(cidade a, cidade b){
    return (float) sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) );
}


void printHelp() {
    printf("Uso: tsp -o directory \n\n");
    printf("Opção           Descrição\n");
    printf(" -h,--help      Lista completa de comandos\n");
    printf(" -o directory   Directoria onde se encontra os ficheiros de dados\n");
}

int main(int argc, char *argv[]) {
    int count;
    char * file_path = "../results/out.eps";
    char *chrDataLocation;
    struct cidade Cidades[5];

    int width = 300;
    int height = 300;


    float square_scale = 1.0f;


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
                    // TODO Envio da localizacao de dados para recolha

                    //Cidades = malloc(5 * sizeof(cidade));

                    Cidades[0].id = 1;
                    Cidades[0].x = 10.0;
                    Cidades[0].y = 10.0;
                    Cidades[0].visited = 0;

                    Cidades[1].id = 2;
                    Cidades[1].x = 80.7;
                    Cidades[1].y = 55.5;
                    Cidades[1].visited = 0;

                    Cidades[2].id = 3;
                    Cidades[2].x = 33.8555;
                    Cidades[2].y = 122.225;
                    Cidades[2].visited = 0;

                    Cidades[3].id = 4;
                    Cidades[3].x = 100.0;
                    Cidades[3].y = 100.0;
                    Cidades[3].visited = 0;

                    Cidades[4].id = 5;
                    Cidades[4].x = 100.0;
                    Cidades[4].y = 55.555;
                    Cidades[4].visited = 0;

                    FILE * file_ptr = fopen(file_path, "w+");
                    setHeader(file_ptr, "Travel Salesman Problem", width, height);
                    drawText(file_ptr, (rgb){0,0,0}, 40,  0, height -50, "Cities: 5");
                    drawLine(file_ptr, (rgb){0,0,0}, 2, height -52 ,  width -2, height -52, 1);

                    for (int i=0;i<5;i++) {
                        char str[5];
                        sprintf(str, "%d", Cidades[i].id);
                        drawText(file_ptr, (rgb){0,0,0}, 5, Cidades[i].x ,  Cidades[i].y + 5, str);
                        drawCircle(file_ptr,Cidades[i].x,Cidades[i].y,5.0,0,360,0.25);
                    }

                    fprintf(file_ptr, "showpage\n");
                    fprintf(file_ptr, "%%%%EOF");
                    fclose(file_ptr);

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