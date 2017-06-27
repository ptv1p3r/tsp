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

void createTourFile(char * file_path, int width, int height);
float getTourDistance();

void printHelp() {
    printf("Uso: tsp -o directory \n\n");
    printf("Opção           Descrição\n");
    printf(" -h,--help      Lista completa de comandos\n");
    printf(" -o directory   Directoria onde se encontra os ficheiros de dados\n");
}

//TESTING//
cidade * swap2opt (int i, int k) {

    cidade temp;

    // 1. take route[0] to route[i-1] and add them in order to new_route
    for ( int c = 0; c <= i - 1; ++c ) {
        temp = cidades[c];
        cidades[c] = cidades[c+1];
        cidades[c+1] = temp;

    }

    // 2. take route[i] to route[k] and add them in reverse order to new_route
    int dec = 0;
    for ( int c = i; c <= k; ++c )
    {

        temp = cidades[c];
        cidades[c] = cidades[ k - dec ];
        cidades[ k - dec ] = temp;

        dec++;
    }

    // 3. take route[k+1] to end and add them in order to new_route
    for ( int c = k + 1; c < numberOfCities; ++c )
    {

        temp = cidades[c];
        cidades[c] = cidades[ c + 1];
        cidades[ c + 1 ] = temp;
    }
}

int main(int argc, char *argv[]) {

    int count;

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

                    int status = readFromDirectory("../tspdata");

                    if (status!=0) {
                        for (int i = 1 ; i <2 ; ++i) {
                            printf("--------- %d ----------\n", i + 1);

                            readFromFile(i);    //le o file da lista

                            //printStruct();  //test print

                            char * tt = fileNames[i];

                            createTourFile(file_path,width,height);

                            //free(cidades);

                            printf("-----------------------\n\n");

                        }
                    }



                    // TODO Aplicar o 2 opt ao array de struct
    //TESTING//
    float improve=1, bestDistance;

    cidade *newRoute = (cidade*) malloc(numberOfCities * sizeof(cidade));

    while ( improve > 0 ) {

        bestDistance = getTourDistance();

        for ( int i = 0; i < numberOfCities - 1; i++ ) {
            for ( int k = i + 1; k < numberOfCities; k++) {

                newRoute = swap2opt(i, k);

                float new_distance = 0;
                for (int j = 0; j < numberOfCities-1 ; ++j) {
                    new_distance += distance(cidades[j], cidades[j+1]);
                }

                if (new_distance < bestDistance) {
                    cidades = newRoute;
                }
            }
        }
    }
    //TESTING//


                    // TODO Imprimir novo eps com os links entre cada cidade optimizada

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

float getTourDistance(){
    float custoTotal=0.0;

    for (int i=0 ; i < numberOfCities-1; i++) {
        custoTotal += distance(cidades[i], cidades[i+1]);
    }
    custoTotal += distance(cidades[numberOfCities-1], cidades[0]); // addiciona custo final entre ultima cidade e casa

    return custoTotal;
}


void createTourFile(char * file_path, int width, int height){
    float custo=0.0;

    FILE * file_ptr = fopen(file_path, "w+");
    setHeader(file_ptr, "Travel Salesman Problem", width, height);

    char headerText[50];
    sprintf( headerText, "Cities: %d", numberOfCities );

    drawText(file_ptr, (rgb){0,0,0}, 20,  0, height -50, headerText);
    drawLine(file_ptr, (rgb){0,0,0}, 2, height -52 ,  width -2, height -52, 1);

    // normaliza a posicao das cidades no viewport do eps
    draw_tsp(file_ptr, numberOfCities, width-2, height-55);

    for (int i=0 ; i < numberOfCities-1; i++) { // percorre todas as cidades e efetua a ligacao entre cada uma

        drawLine(file_ptr, (rgb){0,0,1}, cidades[i].normX, cidades[i].normY, cidades[i+1].normX,cidades[i+1].normY, 2); // desenha o link entre cidades
        //drawLink(file_ptr, (rgb){0,0,1}, cidades[i].normX, cidades[i].normY, cidades[i+1].normX-cidades[i].normX, cidades[i+1].normY-cidades[i].normY, 2); // desenha o link entre cidades

        custo += distance(cidades[i], cidades[i+1]);

    }

    drawLine(file_ptr, (rgb){0,0,1}, cidades[numberOfCities-1].normX, cidades[numberOfCities-1].normY, cidades[0].normX,cidades[0].normY, 2); // desenha o link entre ultima cidade e casa
    custo += distance(cidades[numberOfCities-1], cidades[0]); // addiciona custo final entre ultima cidade e casa
    //printf("custo: %.2f \n", custo);

    char costText[50];
    sprintf( costText, "Tour cost: %.2f", custo );
    drawText(file_ptr, (rgb){0,0,0}, 20,  100, height -50, costText);

    fprintf(file_ptr, "showpage\n");
    fprintf(file_ptr, "%%%%EOF");
    fclose(file_ptr);
}