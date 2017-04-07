#include <stdio.h>
#include <math.h>

// command line app
// abre ficheiro
// calcula rota
// cria eps com cidades
// cria ficheiro rota (tour + cost)
// cria eps com rota grafica, texto tour + text cost + text date/time

typedef struct cidade {
    int cidadeId;
    float x;
    float y;
};

float calculaDistancia(struct cidade a, struct cidade b){
    return (float) sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)  );
}

int main() {
    printf("Hello, World!\n");
    return 0;
}