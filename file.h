//
// Created by v1p3r on 07-04-2017.
//

#ifndef TSP_FILE_H
#define TSP_FILE_H

typedef struct _cidade * cidade;

#endif //TSP_FILE_H

int readFromDirectory(char * path);

void addPathToFile (char * path, char ** filesToRead);

void sortFileNames (char ** filesToRead);

void printString (char ** string);

cidade readFromFile (int fileNumber);

void printStruct (cidade cidades);

char * returnstr (int i);
