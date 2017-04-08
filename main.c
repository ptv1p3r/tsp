#include <stdio.h>
#include <math.h>
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
int main(int argc, char *argv[]) {

    printf("Hello, World!\n");

    printf("output %s \n", DATAPATH_OUTPUT);

    return 0;
}