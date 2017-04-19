//
// Created by v1p3r on 07-04-2017.
//

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "file.h"

int numberOfFiles = 0;  //numero de ficheiros a ler
int numberOfCities = NULL;
//char **filesToRead = NULL;  //TODO: array provisorio

typedef struct cidade{
    int id;
    float x;
    float y;
    int visited;
} cidade;

/**
 * Método para ler todos os ficheiros existentes numa diretoria
 * @param path, diretoria de onde ler
 */
char** readFromDirectory(char * path) {

    char **filesToRead = NULL;
    DIR *d = opendir(path); //abre a diretoria selecionada
    struct dirent *dir; //struct da library <dirent.h>

    while (((dir = readdir(d)) != NULL)) {  //enquanto que existe algo na diretoria, entra

        if ((dir -> d_type != DT_DIR)) {    //se nao for uma diretoria entra, se não ignora

            //--------- Test Print ----------//
            //printf("%s\n", dir->d_name);
            //-------------------------------//

            numberOfFiles++;    //incrementa o numero de ficheiros a ler
        }
    }

    closedir(d);    //fecha a directoria (provisorio)

    d = opendir(path);  //volta a abrir a adirectoria (provisorio

    filesToRead = malloc(sizeof(char*) * numberOfFiles);    //alloca memoria para um array com os nomes dos ficheiros a abrir

    int i =0;
    while (((dir = readdir(d)) != NULL)) {  //enquanto que existe algo na diretoria, entra

        if ((dir -> d_type != DT_DIR)) {    //se nao for uma diretoria entra, se não ignora

            filesToRead[i] = dir->d_name; //guarda o nome do ficheiro no array
            //printf("%d -> %s\n", i+1, filesToRead[i]);
            i++;
        }
    }

    //--------- Test Print ----------//
    printf("\n%d\n", numberOfFiles);    //verificar se foram todos lidos
    //-------------------------------//

    closedir(d);    //fecha a diretoria

    sortFileNames(filesToRead);    //chama a função de ordenação

    addPathToFile("../tspdata/", filesToRead);

    return filesToRead;

};

/**
 * Metodo provisorio para adicionar o path ao nome
 * @param path
 * @param filesToRead
 */
void addPathToFile (char * path, char ** filesToRead) {

    for (int i=0 ; i<numberOfFiles ; i++) {

        char *temp = filesToRead[i];

        char *completePath = (char *) malloc(sizeof(char) * (sizeof(path) / sizeof(char)) + (sizeof(temp) / sizeof(char)));

        strcpy(completePath, path);
        strcat(completePath, temp);
        strcat(completePath, "\0");

        strcpy(filesToRead[i], completePath);

        free(completePath);
    }
}

/**
 * Metodo para ordenar os ficheiros lidos de uma diretoria
 */
void sortFileNames (char ** filesToRead) {

    int i = 0, j = 0;
    int intTemp1 = 0, intTemp2 = 0; //intTemp1 -> primeira posicao da matriz, intTemp2 -> segunda posicao da matriz
    char *temp = NULL;  //temp para o nome do ficheiro
    int **fileNumberOfCities[76][2];    //matriz para ajudar a ordenar os files

    for (i = 0 ; i < numberOfFiles ; i++) {

        char *pointer = filesToRead[i];

        int position = 0; //define a primeira coluna
        while (*pointer) {  //verifica se ainda ha algo para ler

            if (isdigit(*pointer)) {    //verifica se a posição atual é digito

                fileNumberOfCities[i][position] = (int **) (int) strtol(pointer, &pointer, 10);   //da posição e enquanto for numero, guarda o numero na matriz

                position++; //passa para a 2 coluna

            } else {
                pointer++;  //proxima posição
            }

        }
    }


    for (i = 0 ; i<numberOfFiles ; i++) {

        for (j = 0 ; j<numberOfFiles-1 ; j++) {

            if (fileNumberOfCities[j][0] > fileNumberOfCities[j+1][0]) {    //compara se a posição atual e maior que a próxima
                                                                            //se for verdade troca a posicao na matriz e
                                                                            //no array do nome do ficheiro
                //TODO: arranjar maneira de meter o swap numa função
                //Troca o primeiro numero
                intTemp1 = (int) fileNumberOfCities[j][0];
                fileNumberOfCities[j][0] = fileNumberOfCities[j+1][0];
                fileNumberOfCities[j+1][0] = (int **) intTemp1;

                //Troca o segundo numero
                intTemp2 = (int) fileNumberOfCities[j][1];
                fileNumberOfCities[j][1] = fileNumberOfCities[j+1][1];
                fileNumberOfCities[j+1][1] = (int **) intTemp2;

                //Troca o nome do ficheiro
                temp = filesToRead[j];
                filesToRead[j] = filesToRead[j+1];
                filesToRead[j+1] = temp;

            } else if (fileNumberOfCities[j][0] == fileNumberOfCities[j+1][0]) {    //verifica se os numeros sao iguais

                if (fileNumberOfCities[j][1] > fileNumberOfCities[j+1][1]) {    //compara os numeros da 2 coluna da matriz e realiza as trocas

                    //Troca o primeiro numero
                    intTemp1 = (int) fileNumberOfCities[j][0];
                    fileNumberOfCities[j][0] = fileNumberOfCities[j+1][0];
                    fileNumberOfCities[j+1][0] = (int **) intTemp1;

                    //Troca o segundo numero
                    intTemp2 = (int) fileNumberOfCities[j][1];
                    fileNumberOfCities[j][1] = fileNumberOfCities[j+1][1];
                    fileNumberOfCities[j+1][1] = (int **) intTemp2;

                    //Troca o nome do ficheiro
                    temp = filesToRead[j];
                    filesToRead[j] = filesToRead[j+1];
                    filesToRead[j+1] = temp;
                }
            }
        }
    }

    //--------- Test Print ----------//
    for (i = 0; i < numberOfFiles ; ++i) {
        //printf("%d\n", fileNumberOfCities[i][0]);
    }

    printf("\n\n");

    for (i = 0; i < numberOfFiles ; ++i) {
        //printf("%s\n", filesToRead[i]);
    }
    //-------------------------------//
};

/**
 * Teste de string dos ficheiros a ler
 */
void printString (char ** string) {

    for (int i = 0 ; i < numberOfFiles ; ++i) {
        printf("%d -> %s\n", i+1, string[i]);
    }

};

/**
 * Le o conteudo de um determinado ficheiro e retorna uma struct da informacao
 * @param fileName nome do fichero a abrir
 * @return struct cidade
 */
struct cidade * readFromFile (char* fileName) {

    printf("%s\n", fileName);

    FILE *file = fopen(fileName, "r");
    int i=0;
    struct cidade *Cidades = NULL;

    if (file == NULL) {
        printf("Erro ao abrir ficheiro -> %s\n", fileName);
    }

    fscanf(file, "%d\n", &numberOfCities);

    Cidades = malloc(numberOfCities * sizeof(struct cidade));

    for (i=0 ; i<numberOfCities ; i++) {

        fscanf(file, "%f %f", &Cidades[i].x, &Cidades[i].y);
        Cidades[i].id = i+1;
        Cidades[i].visited = 0;
    }

    return Cidades;
};

/**
 * Teste para imprimir a struct
 * @param Cidades
 */
void printStruct (struct cidade *Cidades) {

    for (int i=0 ; i<numberOfCities ; i++) {

        printf("%d -> %d - %.2f - %.2f - %d\n", i+1, Cidades[i].id, Cidades[i].x, Cidades[i].y, Cidades[i].visited);
    }
};