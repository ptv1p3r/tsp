//
// Created by v1p3r on 25-03-2017.
//
#include <time.h>
#include <stdio.h>
#include "eps.h"
#include <limits.h>
#include <string.h>

#define MAX_SCALE 12

void setHeader(FILE * ptr_file, char * title, int width, int height){
    time_t timer;
    char date[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(date, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(ptr_file, "%s\n", "%!PS-Adobe-3.0 EPSF-3.0");
    fprintf(ptr_file, "%%%%Creator:%s\n", "Eps Creator");
    fprintf(ptr_file, "%%%%Title:%s\n", title);
    fprintf(ptr_file, "%%%%BoundingBox: 0 0 %d %d \n", width, height);
    fprintf(ptr_file, "%%%%CreationDate:%s\n", date);
    fprintf(ptr_file, "%%%%Copyright:Pedro Roldan ISMAT 2017 a21501217 AED \n");
}

void drawText(FILE * file_ptr, rgb color, int scale, float x, float y, char * text){
    fprintf(file_ptr, "/Times-Roman findfont %.2f %.2f %.2f setrgbcolor %d scalefont setfont newpath %.2f %.2f moveto (%s) show\n",
            color.r, color.g, color.b, scale, x, y, text);
}

void drawArray(FILE * file_ptr, int * array, int start, int end, int x, int y, int scale, rgb bgcolor, rgb fgcolor){
    int i;
    for(i = start ; i <= end ; i++)
    {
        drawSquare(file_ptr, bgcolor,  x + (i * scale * scale) , y , (scale * scale), (scale * scale), 1);
        char str[10];
        sprintf(str, "%d", array[i-1]);
        drawText(file_ptr, fgcolor, 20, (x + (i * scale * scale) ) + scale * scale /2 - scale, y + scale * scale /2 -scale, str);
    }
}

void drawSquare(FILE * file_ptr, rgb color,  int x1, int y1, int x2, int y2, float width){
    fprintf(file_ptr, "%.2f %.2f %.2f setrgbcolor newpath %d %d moveto %d %d rlineto %d %d rlineto %d %d rlineto %d %d rlineto  closepath  %.2f setlinewidth stroke \n",
            color.r, color.g, color.b, x1, y1, 0, y2, y2, 0, 0, -y2, -y2, 0, width );
}

void drawLine(FILE * file_ptr, rgb color, int x1, int y1, int x2, int y2, float width){
    fprintf(file_ptr, "%.2f %.2f %.2f setrgbcolor newpath %d %d moveto %d %d lineto %.2f setlinewidth stroke\n", color.r, color.g, color.b, x1, y1, x2, y2, width );
}

void drawCircle(FILE * ptr_file, float x, float y, float radius, int startAngle, int endAngle, float strokeWidth){
    fprintf(ptr_file, "%f setlinewidth\n", strokeWidth);
    fprintf(ptr_file, "%.2f %.2f %.2f %d %d arc closepath stroke\n", x, y, radius, startAngle, endAngle);
}