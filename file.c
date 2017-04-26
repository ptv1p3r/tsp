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
char **filesToRead = NULL;  //TODO: array provisorio

struct _cidade{
    int id;
    float x;
    float y;
    int visited;
};

/**
 * Método para ler todos os ficheiros existentes numa diretoria
 * @param path, diretoria de onde ler
 */
int readFromDirectory(char * path) {

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

    //verifica se foi lido alguma coisa
    if (numberOfFiles > 0) {

        d = opendir(path);  //volta a abrir a adirectoria (provisorio

        filesToRead = (char **) malloc (sizeof(char*) * numberOfFiles);    //alloca memoria para um array com os nomes dos ficheiros a abrir

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

        addPathToFile("../tspdata/", filesToRead);  //adiciona o path ao nome do ficheiro (temporario)

        printString(filesToRead);   //imprime os ficheiros a ler

        return 1;   //success

    } else { //caso contrario devolve 0

        printf("Não foram lidos ficheiros");
        return 0;   //failure
    }
};

/**
 * Metodo provisorio para adicionar o path ao nome
 * @param path
 * @param filesToRead
 */
void addPathToFile (char * path, char ** filesToRead) {

    for (int i=0 ; i<numberOfFiles ; i++) {

        char *temp = filesToRead[i];

        //alloca uma string com o size exato do path
        char *completePath = (char *) malloc (sizeof(char) * (strlen(path) / sizeof(char)) + (strlen(temp) / sizeof(char)) + sizeof(char));

        strcpy(completePath, path);
        strcat(completePath, temp);

        strcpy(filesToRead[i], completePath);   //adiciona a noca string ao array

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

    printf("---------- Ficheiros a abrir ----------\n");

    for (int i = 0 ; i < numberOfFiles ; ++i) {
        printf("%d -> %s\n", i+1, string[i]);
    }

    printf("---------------------------------------\n\n");
};

/**
 * Le o conteudo de um determinado ficheiro e retorna uma struct da informacao
 * @param fileName nome do fichero a abrir
 * @return struct cidade
 */
cidade readFromFile (int fileNumber) {

    printf("%s\n", filesToRead[fileNumber]);    //teste de impressao do nome do ficheiro

    char * temp = filesToRead[fileNumber];  //teste de usar outra variavel para abrir o ficheiro

    FILE *file = fopen(temp, "r");
    int i=0;
    cidade city = NULL;

    if (file == NULL) {
        printf("Erro ao abrir ficheiro -> %s\n", filesToRead[fileNumber]);
    }

    fscanf(file, "%d\n", &numberOfCities);

    city = malloc(numberOfCities * sizeof(cidade));

    for (i=0 ; i<numberOfCities ; i++) {    //le a informacao do ficheiro e guarda no array de struct Cidades

        fscanf(file, "%f %f", &city[i].x, &city[i].y);
        city[i].id = i+1;
        city[i].visited = 0;
    }

    fclose(file);

    return city;
};

/**
 * Teste para imprimir a struct
 * @param Cidades
 */
void printStruct (cidade cidades) {

    printf("\t\t Id\t x\t\t y\t\t visited\n");  //header

    for (int i=0 ; i<numberOfCities ; i++) {    //print da informacao

        printf("%d ->\t %d\t %.2f\t %.2f\t %d\n", i+1, cidades[i].id, cidades[i].x, cidades[i].y, cidades[i].visited);
    }
};