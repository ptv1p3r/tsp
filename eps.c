//
// Created by v1p3r on 25-03-2017.
//
#include <time.h>
#include <stdio.h>
#include "eps.h"

void write_eps_header(FILE * ptr_file, char * title, int width, int height)
{
    time_t timer;
    char date[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(date, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(ptr_file, "%s\n", "%!PS-Adobe-3.0 EPSF-3.0");
    fprintf(ptr_file, "%%%%Creator:%s\n", "Eps Creator - AED ISMAT 2017 a21501217 Pedro Roldan");
    fprintf(ptr_file, "%%%%Title:%s\n", title);
    fprintf(ptr_file, "%%%%BoundingBox: 0 0 %d %d \n", width, height);
    fprintf(ptr_file, "%%%%CreationDate:%s\n", date);
}

void draw_line(FILE * ptr_file,  int x1, int y1, int x2, int y2, float width)
{
    fprintf(ptr_file, "newpath %d %d moveto %d %d lineto %f setlinewidth stroke\n", x1, x2, y1, y2, width );
}