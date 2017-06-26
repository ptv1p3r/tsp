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

    //time(&timer);
    //tm_info = localtime(&timer);

    //strftime(date, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(ptr_file, "%s\n", "%!PS-Adobe-3.0 EPSF-3.0");
    fprintf(ptr_file, "%%%%Creator:%s\n", "Eps Creator");
    fprintf(ptr_file, "%%%%Title:%s\n", title);
    fprintf(ptr_file, "%%%%BoundingBox: 0 0 %d %d \n", width, height);
    fprintf(ptr_file, "%%%%CreationDate:%s\n", date);
    fprintf(ptr_file, "%%%%Copyright:Pedro Roldan ISMAT 2017 a21501217 / a21501217 Leandro Moreira AED \n");
    fprintf(ptr_file, "%%%%EndComments\n");

    // write down all procedures
    fprintf(ptr_file, "/arrowhead {%% stack: s x1 y1, current point: x0 y0\n");
    fprintf(ptr_file, "gsave\n");
    fprintf(ptr_file, "currentpoint   %% s x1 y1 x0 y0 \n");
    fprintf(ptr_file, "4 2 roll exch  %% s x0 y0 y1 x1 \n");
    fprintf(ptr_file, "4 -1 roll exch %% s y0 y1 x0 x1 \n");
    fprintf(ptr_file, "sub 3 1 roll   %% s x1-x2 y0 y1 \n");
    fprintf(ptr_file, "sub exch       %% s y0-y1 x1-x2 \n");
    fprintf(ptr_file, "atan rotate    %% rotate over arctan((y0-y1)/(x1-x2)) \n");
    fprintf(ptr_file, "dup scale      %% scale by factor s \n");
    fprintf(ptr_file, "-7 2 rlineto 1 -2 rlineto -1 -2 rlineto \n");
    fprintf(ptr_file, "closepath fill  %% fill arrowhead \n");
    fprintf(ptr_file, "grestore \n");
    fprintf(ptr_file, "newpath \n");
    fprintf(ptr_file, "} def \n");
}

void drawText(FILE * file_ptr, rgb color, float scale, float x, float y, char * text){
    fprintf(file_ptr, "/Times-Roman findfont %f %f %f setrgbcolor %.2f scalefont setfont newpath %.2f %.2f moveto (%s) show\n",
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
            color.r, color.g, color.b, x1, y1, 0, x2, y2, 0, 0, -y2, -y2, 0, width );
}

void drawLine(FILE * file_ptr, rgb color, int x1, int y1, int x2, int y2, float width){
    fprintf(file_ptr, "%.2f %.2f %.2f setrgbcolor newpath %d %d moveto %d %d lineto %.2f setlinewidth stroke\n", color.r, color.g, color.b, x1, y1, x2, y2, width );
}

void drawCircle(FILE * ptr_file, rgb color,float x, float y, float radius, float strokeWidth){
    fprintf(ptr_file, "newpath %.2f %.2f %.2f setrgbcolor newpath %.2f %.2f %.2f 0 360 arc closepath %.2f setlinewidth stroke \n", color.r, color.g, color.b, x, y, radius, strokeWidth);

}

void drawLink(FILE * file_ptr, rgb color, float x1, float y1, float x2, float y2, float strokeWidth){
    fprintf(file_ptr, "%.2f %.2f translate\n", x1, y1);
    fprintf(file_ptr, "%f %f %f setrgbcolor 0 0 moveto %.2f %.2f lineto stroke\n", color.r, color.g, color.b, x2, y2 );
    fprintf(file_ptr, "newpath %.2f %.2f moveto %.2f 0 0 arrowhead \n", x2, y2, strokeWidth);
}
