#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include "eps.h"
#include "file.h"
#include "tsp.h"

// command line app
// abre ficheiro
// calcula rota
// cria eps com cidades
// cria ficheiro rota (tour + cost)
// cria eps com rota grafica, texto tour + text cost + text date/time

#define DATAPATH_OUTPUT "./output"
#define PI 3.141592653589793238
#define SPACE_BETWEEN_CIRCLES_RATIO 0.05

void printHelp() {
    printf("Uso: tsp -o directory \n\n");
    printf("Opção           Descrição\n");
    printf(" -h,--help      Lista completa de comandos\n");
    printf(" -o directory   Directoria onde se encontra os ficheiros de dados\n");
}

int main(int argc, char *argv[]) {

    int count, n=5;
    char * file_path = "../results/out.eps";
    //char * file_path = "../out.eps";
    char *chrDataLocation;
    float min_x, min_y;
    float max_x, max_y;
    float total = 0.0;
    int height = 800;
    int width = 600;
    int myArray[5] = { 0 };

    float square_scale = 1.0f;


    int status = readFromDirectory("../tspdata");

    if (status!=0) {
        for (int i = 0 ; i <1 ; ++i) {
            printf("--------- %d ----------\n", i + 1);

            readFromFile(i);    //le o file da lista

            printStruct();  //test print

            //free(cidades);

            printf("-----------------------\n\n");

        }
    }


//    if (argc > 1) { /* Valida número de argumentos */
//
//        for (count=1; count<argc; count++) {
//
//            /* Valida opção --help */
//            if ((strcmp(argv[count], "--help") == 0) || (strcmp(argv[count], "-h") == 0)) {
//                printHelp();
//                exit(EXIT_SUCCESS);
//            }   /* Valida opção -o */
//            else if ((strcmp(argv[count], "-o") == 0)) {
//
//                if (count+1 < argc) {
//                    chrDataLocation = argv[count+1];
//                    printf("input %s \n", chrDataLocation);
//                    // TODO Envio da localizacao de dados para recolha

                    FILE * file_ptr = fopen(file_path, "w+");
                    setHeader(file_ptr, "Travel Salesman Problem", width, height);

//                    drawText(file_ptr, (rgb){0,0,0}, 40,  0, height -50, "Cities: 5");
//                    drawLine(file_ptr, (rgb){0,0,0}, 2, height -52 ,  width -2, height -52, 1);

                    printf("Number of cities is: %d \n", n);
                    // normaliza a posicao das cidades no viewport do eps
                    draw_tsp(file_ptr, n, width, height);

                    // TODO percorrer a struct de cidades e desenhar o link entre cada uma
                    drawLink(file_ptr, (rgb){0,0,1},cidades[0].normX,cidades[0].normY,cidades[1].normX,cidades[1].normY, 2); // desenha o link entre cidades
                    drawLink(file_ptr, (rgb){0,0,1},cidades[1].normX,cidades[1].normY,cidades[3].normX,cidades[3].normY, 2); // desenha o link entre cidades


                    // TODO Aplicar o 2 opt ao array de struct


                    // TODO Imprimir novo eps com os links entre cada cidade optimizada


                    fprintf(file_ptr, "showpage\n");
                    fprintf(file_ptr, "%%%%EOF");
                    fclose(file_ptr);

//                    myArray[0] = cidades[0].id;
//
//                    // local search
//                    for (int i=0;i<n;i++) {
//                        cidades[i].visited = 1 ;
//
//                        for(int j = i + 1; j < n - 1; j++) {
//
//                            if (cidades[j].visited != 1){
//                                total = distance(cidades[i],cidades[j]);
//
//
//                            }
//                        }
//                    }



//                } else {
//                    printf("Uso: -o [directory]\n");
//                    exit(EXIT_SUCCESS);
//                }
//            }
//        }
//
//    }  else {
//        printf("Uso: --help para uma lista completa de comandos.\n");
//        exit(EXIT_SUCCESS);
//    }

    return 0;
}