#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include "eps.h"
#include "file.h"
#include "tsp.h"

void createTourFile(char * filename, int width, int height);
float getTourDistance(cidade * tour, int cities);
void copyTour (cidade * validTour, cidade * newTour);
void tour2Opt ();
void swap2Opt (cidade * route, int inicial);
void removeIntersections(cidade * route);
int orientation(cidade cidade1, cidade cidade2, cidade cidade3);

void printHelp() {
    printf("Uso: tsp -o directory \n\n");
    printf("Opção           Descrição\n");
    printf(" -h,--help      Lista completa de comandos\n");
    printf(" -o directory   Directoria onde se encontra os ficheiros de dados\n");
}

int main(int argc, char *argv[]) {
    char *chrDataLocation;
    int count = 0;
    int height = 800;
    int width = 600;

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

                    char fileText[50];
                    sprintf( fileText, "../%s", chrDataLocation );

                    int status = readFromDirectory(fileText);

                    if (status!=0) {
                        for (int i = 0 ; i < numberOfFiles ; ++i) {
                            readFromFile(i);    //le o file da lista

                            createTourFile(fileNames[i],width,height);

                            tour2Opt();

                            char fileName[20];
                            sprintf( fileName, "%s_opt", fileNames[i] );

                            createTourFile(fileName,width,height);

                            free(cidades);
                        }
                    }
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

/**
 * Metodo que aplica o algoritmo 2opt
 */
void tour2Opt () {

    int improve=0;
    float bestDistance,new_distance = 0;

    cidade *newRoute = (cidade*) malloc(numberOfCities * sizeof(cidade));

    bestDistance = getTourDistance(cidades,numberOfCities); // calcula a distancia da tour

    while ( improve < numberOfCities-1 ) {

        for ( int i = 0; i < numberOfCities - 1 ; i++ ) {
            for ( int k = i + 1; k < numberOfCities-1; k++) {

                copyTour(newRoute, cidades);

                swap2Opt(newRoute, i);
                new_distance = getTourDistance(newRoute,numberOfCities);

                if (new_distance < bestDistance) { // encontra uma rota com melhor distancia
                    copyTour(cidades , newRoute); // copia nova rota

                    improve = 0;
                    bestDistance = new_distance;
                }
            }
        }
        improve++;
    }

    removeIntersections(newRoute);

}

/**
 * Metodo que efetua copia entre duas tours
 * @param tour1 lista de cidades
 * @param tour2 lista de cidades a copiar
 */
void copyTour (cidade * tour1, cidade * tour2) {
    for (int i = 0; i < numberOfCities; i++) {
        tour1[i] = tour2[i];
    }
}

/**
 * Metodo que efetua o swap 2opt a uma tour
 * @param route lista de cidades
 * @param inicial
 */
void swap2Opt (cidade * route, int inicial) {

    float custoNormal, custoAlterado;
    int i, j;

    for (i = 0; i < numberOfCities; i++) {
        for (j = 0; j < numberOfCities-1 ; j++) {

            if ( !((i > inicial-1) && (i < inicial+2)) && (i != j)) {

                custoNormal = distance(route[inicial], route[inicial+1]) + distance(route[j], route[j+1]);
                custoAlterado = distance(route[inicial], route[j+1]) + distance(route[inicial+1], route[j]);

                if ( custoNormal > custoAlterado ) {

                    cidade temp;

                    temp = route[j+1];
                    route[j+1] = route[inicial+1];
                    route[inicial+1] = temp;
                }
            }
        }
    }
}

/**
 * Metodo que remove intersecoes de uma tour
 * @param route lista de cidades
 */
void removeIntersections (cidade * route) {

    int i, j;
    int improve = 0;

    while (improve < numberOfCities) {
        for (i = 0; i < numberOfCities - 1; i++) {
            for (j = 0; j < numberOfCities - 1; j++) {

                if ((i != j)) {

                    if ((route[i].id != route[j].id) && (route[i].id != route[j + 1].id) &&
                        (route[i + 1].id != route[j].id) && (route[i + 1].id != route[j + 1].id)) {

                        float p1 = orientation(route[i], route[i + 1], route[j]);
                        float p2 = orientation(route[i], route[i + 1], route[j + 1]);
                        float p3 = orientation(route[j], route[j + 1], route[i]);
                        float p4 = orientation(route[j], route[j + 1], route[i + 1]);

                        if ((p1 != p2 && p3 != p4)) {

                            cidade temp;

                            temp = route[j];
                            route[j] = route[i+1];
                            route[i+1] = temp;

                            copyTour(cidades, route);
                        }
                    }
                }
            }

            if ((route[i].id != route[j].id) && (route[i].id != route[0].id) &&
                (route[i + 1].id != route[j].id) && (route[i + 1].id != route[0].id)) {

                float p1 = orientation(route[i], route[i + 1], route[j]);
                float p2 = orientation(route[i], route[i + 1], route[0]);
                float p3 = orientation(route[j], route[j + 1], route[i]);
                float p4 = orientation(route[j], route[j + 1], route[0]);

                if ((p1 != p2 && p3 != p4)) {

                    cidade temp;

                    temp = route[j];
                    route[j] = route[i+1];
                    route[i+1] = temp;

                    copyTour(cidades, route);
                }
            }
        }

        improve++;
    }
}

/**
 *
 * @param cidade1
 * @param cidade2
 * @param cidade3
 * @return
 */
int orientation(cidade cidade1, cidade cidade2, cidade cidade3) {

    // See http://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (int) ((cidade2.y - cidade1.y) * (cidade3.x - cidade2.x) -
                  (cidade2.x - cidade1.x) * (cidade3.y - cidade2.y));

    if (val == 0) {
        return 0;
    }  // colinear

    if (val > 0) {
        return 1;
    } else {
        return 2;
    }
}

/**
 * Metodo que calcula a distancia de uma tour
 * @param tour lista de cidades
 * @return float soma das distancias entre as cidades de uma tour
 */
float getTourDistance(cidade * tour, int cities){
    float custoTotal=0.0;

    if (is_valid_tour(tour,cities)){
        for (int i=0 ; i < numberOfCities-1; i++) {
            custoTotal += distance(tour[i], tour[i+1]);
        }
        custoTotal += distance(tour[numberOfCities-1], tour[0]); // adiciona custo final entre ultima cidade e casa
    }

    return custoTotal;
}

/**
 * Metodo que cria o output em eps e txt
 * @param filename nome do ficheiro
 * @param width largura
 * @param height altura
 */
void createTourFile(char * filename, int width, int height){
    float custo=0.0;
    char tourPath[100000]={};
    char filePath[200]={};

    sprintf( filePath, "../results/%s.eps", filename );

    FILE * file_ptr = fopen(filePath, "w+");
    setHeader(file_ptr, "Travel Salesman Problem", width, height);

    drawText(file_ptr, (rgb){0,0,0}, 20,  0, height -15, filename);

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

        char tourText[5];
        sprintf( tourText, "%i=>", cidades[i].id );
        strcat(tourPath, tourText);

    }

    drawLine(file_ptr, (rgb){0,0,1}, cidades[numberOfCities-1].normX, cidades[numberOfCities-1].normY, cidades[0].normX,cidades[0].normY, 2); // desenha o link entre ultima cidade e casa
    custo += distance(cidades[numberOfCities-1], cidades[0]); // addiciona custo final entre ultima cidade e casa

    char tourText[5];
    sprintf( tourText, "%i=>%i", cidades[numberOfCities-1].id, cidades[0].id );
    strcat(tourPath, tourText);

    char costText[50];
    sprintf( costText, "Tour cost: %.2f", custo );
    drawText(file_ptr, (rgb){0,0,0}, 20,  100, height -50, costText);

    drawText(file_ptr, (rgb){0,0,0}, 5,  0, height -32, tourPath);

    fprintf(file_ptr, "showpage\n");
    fprintf(file_ptr, "%%%%EOF");
    fclose(file_ptr);

    sprintf( filePath, "../results/%s.txt", filename );

    FILE *f = fopen(filePath, "w");
    if (!f){
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "%.2f\n%s\n", custo, tourPath);
    fclose(f);
}