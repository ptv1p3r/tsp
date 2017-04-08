//
// Created by v1p3r on 25-03-2017.
//

#ifndef EPS_EPS_H
#define EPS_EPS_H

#endif //EPS_EPS_H

typedef struct {
    float r;
    float g;
    float b;
}rgb;

void setHeader(FILE * ptr_file, char * title, int width, int height);

void drawLine(FILE * file_ptr, rgb color, int x1, int y1, int x2, int y2, float width);

void drawSquare(FILE * file_ptr, rgb color,  int x1, int y1, int x2, int y2, float width);

void drawText(FILE * file_ptr, rgb color, int scale, float x, float y, char * text);

void drawArray(FILE * file_ptr, int * array, int start, int end, int x, int y, int scale, rgb bgcolor, rgb fgcolor);

void drawCircle(FILE * ptr_file, float x, float y, float radius, int startAngle, int endAngle, float strokeWidth);

void drawLink(FILE * file_ptr, rgb color, int x1, int y1, int x2, int y2, int width);
