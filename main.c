#include <stdio.h>
#include <math.h>

// abre ficheiro
// calcula rota
// guarda rota

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