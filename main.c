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
#define PI 3.141592653589793238
#define SPACE_BETWEEN_CIRCLES_RATIO 0.05

/*
int isValidTour(cidade * cities, int n)
{
    int i, j;
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n - 1; j++)
        {
            if(cities[i].id == cities[j].id)
            {
                return 0; // it is not valid
            }
        }
    }
    return 1; // it is a valid tour
}


float computeDistance(cidade a, cidade b){
    return (float) sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) );
}
*/

void printHelp() {
    printf("Uso: tsp -o directory \n\n");
    printf("Opção           Descrição\n");
    printf(" -h,--help      Lista completa de comandos\n");
    printf(" -o directory   Directoria onde se encontra os ficheiros de dados\n");
}

int main(int argc, char *argv[]) {

    int count, n=5;
    char * file_path = "../results/out.eps";
    char *chrDataLocation;
    cidade Cidades = NULL;
    float min_x, min_y;
    float max_x, max_y;
    float total = 0.0;
    int height = 800;
    int width = 600;
    int myArray[5] = { 0 };

    float square_scale = 1.0f;

    //---------- Test para a parte dos files ----------//
    int status = 0;
    status = readFromDirectory("../tspdata");

    if (status!=0) {
        for (int i = 0 ; i < 5 ; ++i) {
            printf("--------- %d ----------\n", i + 1);

            Cidades = readFromFile(i);

            printStruct(Cidades);

            free(Cidades);

            printf("-----------------------\n\n");

        }
    }
    //-------------------------------------------------//


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
//
//                    //Cidades = malloc(5 * sizeof(cidade));
//
//                    Cidades[0].id = 1;
//                    Cidades[0].x = 10.0;
//                    Cidades[0].y = 10.0;
//                    Cidades[0].visited = 0;
//
//                    Cidades[1].id = 2;
//                    Cidades[1].x = 80.7;
//                    Cidades[1].y = 55.5;
//                    Cidades[1].visited = 0;
//
//                    Cidades[2].id = 3;
//                    Cidades[2].x = 33.8555;
//                    Cidades[2].y = 122.225;
//                    Cidades[2].visited = 0;
//
//                    Cidades[3].id = 4;
//                    Cidades[3].x = 100.0;
//                    Cidades[3].y = 100.0;
//                    Cidades[3].visited = 0;
//
//                    Cidades[4].id = 5;
//                    Cidades[4].x = 100.0;
//                    Cidades[4].y = 55.555;
//                    Cidades[4].visited = 0;
//
//                    FILE * file_ptr = fopen(file_path, "w+");
//                    setHeader(file_ptr, "Travel Salesman Problem", width, height);
//                    drawText(file_ptr, (rgb){0,0,0}, 40,  0, height -50, "Cities: 5");
//                    drawLine(file_ptr, (rgb){0,0,0}, 2, height -52 ,  width -2, height -52, 1);
//
//                    // normaliza a posicao das cidades no viewport do eps
//                    min_x = Cidades[0].x;
//                    min_y = Cidades[0].y;
//                    max_x = Cidades[0].x;
//                    max_y = Cidades[0].y;
//
//                    for(int i = 1; i < n; i++) {
//                        if(Cidades[i].x < min_x)
//                            min_x = Cidades[i].x;
//                        else if(Cidades[i].x > max_x)
//                            max_x = Cidades[i].x;
//                        if(Cidades[i].y < min_y)
//                            min_y = Cidades[i].y;
//                        else if(Cidades[i].y > max_y)
//                            max_y = Cidades[i].y;
//                    }
//
//                    for (int i=0;i<n;i++) {
//
//                        // calculate the radius
//                        float radius = sqrt((width * height / (float) n) / 2 * PI) * SPACE_BETWEEN_CIRCLES_RATIO;
//
//                        // calculate the correct x and y and shift for the edge positions
//                        float x = (radius) + (Cidades[i].x - min_x) / (max_x - min_x) * (width - (2 * radius));
//                        float y = (radius) + (Cidades[i].y - min_y) / (max_y - min_y) * (height - (2 * radius));
//
//
//                        char str[5];
//                        sprintf(str, "%d", Cidades[i].id);
//                        drawCircle(file_ptr,x,y,radius,0,360,0.25);
//                        drawText(file_ptr, (rgb){0,0,0}, radius, x ,  y , str);
//
//                    }
//
//                    drawLink(file_ptr, (rgb){0,0,1}, 10, 10, 180, 155, 2); // desenha o link entre cidades
//
//                    fprintf(file_ptr, "showpage\n");
//                    fprintf(file_ptr, "%%%%EOF");
//                    fclose(file_ptr);
//
//                    myArray[0] = Cidades[0].id;
//
//                    // local search
//                    for (int i=0;i<n;i++) {
//                        Cidades[i].visited = 1 ;
//
//                        for(int j = i + 1; j < n - 1; j++) {
//
//                            if (Cidades[j].visited != 1){
//                                total = computeDistance(Cidades[i],Cidades[j]);
//                            }
//                        }
//                    }
//
//
//
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