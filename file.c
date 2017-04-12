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
char *array [76] = {};  //TODO: array provisorio
void sortFileNames ();

/**
 * Método para ler todos os ficheiros existentes numa diretoria
 * @param path, diretoria de onde ler
 */
void readFromDirectory(char * path) {

    DIR *d = opendir(path); //abre a diretoria selecionada
    struct dirent *dir; //struct da library <dirent.h>

    while (((dir = readdir(d)) != NULL)) {  //enquanto que existe algo na diretoria, entra

        if ((dir -> d_type != DT_DIR)) {    //se nao for uma diretoria entra, se não ignora

            //--------- Test Print ----------//
            printf("%s\n", dir->d_name);
            //-------------------------------//

            array[numberOfFiles] = dir->d_name; //guarda o nome do ficheiro no array
            numberOfFiles++;    //incrementa o numero de ficheiros a ler
        }
    }

    //--------- Test Print ----------//
    printf("\n\n%d\n\n", numberOfFiles);    //verificar se foram todos lidos
    //-------------------------------//

    closedir(d);    //fecha a diretoria

    sortFileNames();    //chama a função de ordenação

}

/**
 * Metodo para ordenar os ficheiros lidos de uma diretoria
 */
void sortFileNames () {

    int i = 0, j = 0;
    int intTemp1 = 0, intTemp2 = 0; //intTemp1 -> primeira posicao da matriz, intTemp2 -> segunda posicao da matriz
    char *temp = NULL;  //temp para o nome do ficheiro
    int **fileNumberOfCities[76][2];    //matriz para ajudar a ordenar os files

    for (i = 0 ; i < numberOfFiles ; i++) {

        char *pointer = array[i];

        int position = 0; //define a primeira coluna
        while (*pointer) {  //verifica se ainda ha algo para ler

            if (isdigit(*pointer)) {    //verifica se a posição atual é digito

                fileNumberOfCities[i][position] = (int) strtol(pointer, &pointer, 10);   //da posição e enquanto for numero, guarda o numero na matriz

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
                intTemp1 = fileNumberOfCities[j][0];
                fileNumberOfCities[j][0] = fileNumberOfCities[j+1][0];
                fileNumberOfCities[j+1][0] = intTemp1;

                //Troca o segundo numero
                intTemp2 = fileNumberOfCities[j][1];
                fileNumberOfCities[j][1] = fileNumberOfCities[j+1][1];
                fileNumberOfCities[j+1][1] = intTemp2;

                //Troca o nome do ficheiro
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;

            } else if (fileNumberOfCities[j][0] == fileNumberOfCities[j+1][0]) {    //verifica se os numeros sao iguais

                if (fileNumberOfCities[j][1] > fileNumberOfCities[j+1][1]) {    //compara os numeros da 2 coluna da matriz e realiza as trocas

                    //Troca o primeiro numero
                    intTemp1 = fileNumberOfCities[j][0];
                    fileNumberOfCities[j][0] = fileNumberOfCities[j+1][0];
                    fileNumberOfCities[j+1][0] = intTemp1;

                    //Troca o segundo numero
                    intTemp2 = fileNumberOfCities[j][1];
                    fileNumberOfCities[j][1] = fileNumberOfCities[j+1][1];
                    fileNumberOfCities[j+1][1] = intTemp2;

                    //Troca o nome do ficheiro
                    temp = array[j];
                    array[j] = array[j+1];
                    array[j+1] = temp;
                }
            }
        }
    }

    //--------- Test Print ----------//
    for (i = 0; i < numberOfFiles ; ++i) {
        printf("%d\n", fileNumberOfCities[i][0]);
    }

    printf("\n\n");

    for (i = 0; i < numberOfFiles ; ++i) {
        printf("%s\n", array[i]);
    }
    //-------------------------------//
};
