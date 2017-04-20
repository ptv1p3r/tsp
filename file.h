//
// Created by v1p3r on 07-04-2017.
//

#ifndef TSP_FILE_H
#define TSP_FILE_H

#endif //TSP_FILE_H

int readFromDirectory(char * path);

void addPathToFile (char * path, char ** filesToRead);

void sortFileNames (char ** filesToRead);

void printString (char ** string);

struct cidade * readFromFile (int fileNumber);

void printStruct (struct cidade *Cidades);

char * returnstr (int i);
