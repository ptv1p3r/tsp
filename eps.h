//
// Created by v1p3r on 25-03-2017.
//

#ifndef EPS_EPS_H
#define EPS_EPS_H

#endif //EPS_EPS_H

typedef struct _rgb
{
    float r;
    float g;
    float b;
}rgb;

void setHeader(FILE * ptr_file, char * title, int width, int height);

void drawLine(FILE * file_ptr, rgb color, int x1, int y1, int x2, int y2, float width);

void drawSquare(FILE * file_ptr, rgb color,  int x1, int y1, int x2, int y2, float width);

void drawText(FILE * file_ptr, rgb color, int scale, int x, int y, char * text);

void drawArray(FILE * file_ptr, int * array, int start, int end, int x, int y, int scale, rgb bgcolor, rgb fgcolor);

void drawCircle(FILE * ptr_file, int x, int y, float radius, int startAngle, int endAngle, float strokeWidth);

int binary_search(int * array, int n, int x, FILE * file_ptr, int ypos, int scale);

void selection_sort(int * array, int n, FILE * file_ptr, int ypos, float scale);

void insertion_sort(int * array, int n, FILE * file_ptr, int ypos, float scale);

void bubble_sort(int * array, int n, FILE * file_ptr, int ypos, float scale);