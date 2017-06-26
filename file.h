//
// Created by v1p3r on 07-04-2017.
//

#ifndef TSP_FILE_H
#define TSP_FILE_H

typedef struct _cidade{
    int id;
    float x;
    float y;
    float normX;
    float normY;
    int visited;
} cidade;

cidade * cidades;
int numberOfFiles;  //numero de ficheiros a ler
int numberOfCities;
char **filesToRead;

#endif //TSP_FILE_H

int readFromDirectory(char * path);

void addPathToFile (char * path);

void insertionSort ();

void printString (char ** string);

void readFromFile (int fileNumber);

void printStruct ();

char * returnstr (int i);
