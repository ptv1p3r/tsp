//
// Created by v1p3r on 07-04-2017.
//

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "file.h"

#define MAX_LENGHT 25


/**
 * Método para ler todos os ficheiros existentes numa diretoria
 * @param path, diretoria de onde ler
 */
int readFromDirectory(char * path) {

    int i=0;
    DIR *d = opendir(path); //abre a diretoria selecionada
    struct dirent *dir; //struct da library <dirent.h>

    while ( (dir = readdir(d)) ) {  //enquanto que existe algo na diretoria, entra

        if ((dir -> d_type != DT_DIR)) {    //se nao for uma diretoria entra, se não ignora
            //printf("%d -> %s\n", ++i, dir->d_name);
            numberOfFiles++;    //incrementa o numero de ficheiros a ler
        }
    }

    closedir(d);    //fecha a directoria (provisorio)

    //verifica se foi lido alguma coisa
    if (numberOfFiles > 0) {

        d = opendir(path);  //volta a abrir a adirectoria (provisorio

        filesToRead = malloc (sizeof(char*) * numberOfFiles);    //alloca memoria para um array com os nomes dos ficheiros a abrir
        fileNames = malloc (sizeof(char*) * numberOfFiles);    //alloca memoria para um array com apenas os nomes dos ficheiros


        i = 0;
        while (((dir = readdir(d)) != NULL)) {  //enquanto que existe algo na diretoria, entra

            if ((dir -> d_type != DT_DIR)) {    //se nao for uma diretoria entra, se não ignora

                filesToRead[i] = (char *) malloc (strlen(dir->d_name) + 1);
                strcpy(filesToRead[i] , dir->d_name); //guarda o nome do ficheiro no array

                fileNames[i] = (char *) malloc (strlen(dir->d_name) + 1);
                strcpy(fileNames[i] , dir->d_name); //guarda o nome do ficheiro no array
                //printf("%d -> %s\n", i+1, filesToRead[i]);
                i++;
            }
        }

        printf("\n%d\n", numberOfFiles);    //verificar se foram todos lidos


        closedir(d);    //fecha a diretoria

        insertionSort(filesToRead);    //chama a função de ordenação
        insertionSort(fileNames);    //chama a função de ordenação

        addPathToFile("../tspdata/");  //adiciona o path ao nome do ficheiro (temporario)

        //printString(filesToRead);   //imprime os ficheiros a ler

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
void addPathToFile (char * path) {

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
void insertionSort(char ** array) {    //TODO: Finish this shit

    int i, j;
    char key[MAX_LENGHT];
    char temp[MAX_LENGHT];

    for (i = 1; i < numberOfFiles; ++i) {

        strcpy(key, array[i]);  //copies the next value to check to key

        j = i - 1;

        while (j >= 0) {

            if (strlen(array[j]) == strlen(key)) {   //checks if lengths are equal

                if ((strcasecmp(array[j], key) > 0)) {    //compares the values

                    //swapping
                    strcpy(temp, array[j]);
                    strcpy(array[j], array[j + 1]);
                    strcpy(array[j + 1], temp);
                }

            } else if (strlen(array[j]) > strlen(key)) {
                //if length of current position is bigger than the key while comparing in a crescent way, swap.

                //swapping
                strcpy(temp, array[j]);
                strcpy(array[j], array[j + 1]);
                strcpy(array[j + 1], temp);

            } else {    //gets out of the loop

                break;
            }

            j--;
        }
    }
}


/**
 * Teste de string dos ficheiros a ler
 */
void printString (char ** string) {

    printf("---------- Ficheiros a abrir ----------\n");

    char name[15];
    for (int i = 0 ; i < numberOfFiles ; ++i) {

        strcpy(name, string[i]);
        printf("%d -> %s\n", i+1, string[i]);
    }

    printf("---------------------------------------\n\n");
}

/**
 * Le o conteudo de um determinado ficheiro e retorna uma struct da informacao
 * @param fileName nome do fichero a abrir
 * @return struct cidade
 */
void readFromFile (int fileNumber) {

    printf("%s\n", filesToRead[fileNumber]);    //teste de impressao do nome do ficheiro

    FILE *file = fopen(filesToRead[fileNumber], "r");

    if (file == NULL) {
        printf("Erro ao abrir ficheiro -> %s\n", filesToRead[fileNumber]);
    }

    fscanf(file, "%d\n", &numberOfCities);

    cidades = (cidade*) malloc(numberOfCities * sizeof(cidade));

    int i=0;
    for (i=0 ; i<numberOfCities ; i++) {    //le a informacao do ficheiro e guarda no array de struct Cidades

        fscanf(file, "%f %f", &cidades[i].x, &cidades[i].y);
        cidades[i].id = i+1;
        cidades[i].visited = 0;
    }

};

/**
 * Teste para imprimir a struct
 * @param Cidades
 */
void printStruct () {

    printf("\t\t Id\t x\t\t y\t\t visited\n");  //header

    for (int i=0 ; i<numberOfCities ; i++) {    //print da informacao

        printf("%d ->\t %d\t %.2f\t %.2f\t %d\n", i+1, cidades[i].id, cidades[i].x, cidades[i].y, cidades[i].visited);
    }
};