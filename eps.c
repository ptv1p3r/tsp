//
// Created by v1p3r on 25-03-2017.
//
#include <time.h>
#include <stdio.h>
#include "eps.h"
#include <limits.h>
#include <string.h>

#define MAX_SCALE 12

void setHeader(FILE * ptr_file, char * title, int width, int height)
{
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

void drawText(FILE * file_ptr, rgb color, int scale, int x, int y, char * text){
    fprintf(file_ptr, "/Times-Roman findfont %f %f %f setrgbcolor %d scalefont setfont newpath %d %d moveto (%s) show\n",
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
    fprintf(file_ptr, "%f %f %f setrgbcolor newpath %d %d moveto %d %d rlineto %d %d rlineto %d %d rlineto %d %d rlineto  closepath  %f setlinewidth stroke \n",
            color.r, color.g, color.b, x1, y1, 0, y2, y2, 0, 0, -y2, -y2, 0, width );
}

void drawLine(FILE * file_ptr, rgb color, int x1, int y1, int x2, int y2, float width){
    fprintf(file_ptr, "%f %f %f setrgbcolor newpath %d %d moveto %d %d lineto %f setlinewidth stroke\n", color.r, color.g, color.b, x1, y1, x2, y2, width );
}

void drawCircle(FILE * ptr_file, int x, int y, float radius, int startAngle, int endAngle, float strokeWidth){
    fprintf(ptr_file, "%f setlinewidth\n", strokeWidth);
    fprintf(ptr_file, "%d %d %f %d %d arc closepath stroke\n", x, y, radius, startAngle, endAngle);
}

int binary_search(int * array, int n, int x, FILE * file_ptr, int ypos, int scale){
    int p = 0;
    int r = n -1;
    int q;
    while(p <= r)
    {
        drawArray(file_ptr,array ,p+1 ,r+1 , 0, ypos, scale, (rgb){0,1,0}, (rgb){0,0,0});
        ypos -= (scale/MAX_SCALE) * 100;
        q = (int) (p + r) / 2;
        if(array[q] == x)
            return q;
        else
        if(array[q] > x)
            r = q - 1;
        else
            p = q + 1;

    }

    return -1; // not found
}

void selection_sort(int * array, int n, FILE * file_ptr, int ypos, float scale){

    int i, j;
    int min_index;
    int spacing = (int)((scale/MAX_SCALE) * 100);

    for(i = 0; i < n - 1; i++)
    {

        ypos -= spacing;
        // find the index of the minimum
        min_index = i;
        for(j = i + 1; j < n; j++){
            if(array[min_index] <= array[j])
            {
                min_index = j;
            }
        }

        // draw the array before swap
        drawArray(file_ptr,array, 1, n ,0 ,ypos ,scale , (rgb){0,1,0}, (rgb){0,0,0});

        // swap the minimum with the first item
        int temp = array[min_index];
        array[min_index] = array[i];
        array[i] = temp;

        // change the color of the sorted items
        int k;
        for(k = 0; k < i; k++)
        {
            drawSquare(file_ptr, (rgb){0.25,0.25,0.25},  1 + ((k+1) * scale * scale) , ypos , (scale * scale), (scale * scale), 1);
        }

        // draw the min_index position
        drawSquare(file_ptr, (rgb){0,0,1},  1 + ((min_index+1) * scale * scale) , ypos , (scale * scale), (scale * scale), 3);
        // draw the item to be swapped
        drawSquare(file_ptr, (rgb){1,0,0},  1 + ((i+1) * scale * scale) , ypos , (scale * scale), (scale * scale), 3);

    }

    // draw the sorted array
    ypos -= spacing;
    drawArray(file_ptr,array ,1 ,n , 0, ypos, 6, (rgb){0.25,0.25,0.25}, (rgb){0,0,0});

}

void insertion_sort(int * array, int n, FILE * file_ptr, int ypos, float scale){

    int i, j;
    int key;
    int spacing = (int)((scale/MAX_SCALE) * 100);

    for(i = 1; i < n ; i++)
    {

        // draw the array
        ypos -= spacing; //  move on the y position
        drawArray(file_ptr,array, 1, n ,0 ,ypos ,scale , (rgb){0,1,0}, (rgb){0,0,0});

        key = array[i];
        j = i - 1;

        // change the color of the sorted items
        int k;
        for(k = 0; k >=i ; k++)
        {
            if(array[k] > key)
                drawSquare(file_ptr, (rgb){1,0,0},  1 + ((k+1) * scale * scale) , ypos , (scale * scale), (scale * scale), 3);
            else
                drawSquare(file_ptr, (rgb){0.25,0.25,0.25},  1 + ((k+1) * scale * scale) , ypos , (scale * scale), (scale * scale), 1);
        }

        // draw the key position
        drawSquare(file_ptr, (rgb){0,0,1},  1 + ((i+1) * scale * scale) , ypos , (scale * scale), (scale * scale), 3);


        while(j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j]; // move the item to make space for the key
            j = j -1;
        }
        array[j + 1] = key;


    }

    // draw the sorted array
    ypos -= spacing;
    drawArray(file_ptr,array ,1 ,n , 0, ypos, 6, (rgb){0.25,0.25,0.25}, (rgb){0,0,0});

}

void bubble_sort(int * array, int n, FILE * file_ptr, int ypos, float scale){

    int i, j;
    int intTemp;
    int spacing = (int)((scale/MAX_SCALE) * 100);

    for(i = 0; i < n -1 ; i++)
    {
        // draw the array
        ypos -= spacing; //  move on the y position
        drawArray(file_ptr,array, 1, n ,0 ,ypos ,scale , (rgb){0,1,0}, (rgb){0,0,0});

        for (j = n-1; j > i; j-- ){

            if(array[j] < array[j-1]){
                intTemp=array[j-1];
                array[j-1] = array[j];
                array[j]=intTemp;
            }
        }

        // change the color of the sorted items
        int k;
        for(k = 0; k < i; k++)
        {
            drawSquare(file_ptr, (rgb){0.25,0.25,0.25},  1 + ((k+1) * scale * scale) , ypos , (scale * scale), (scale * scale), 1);
        }

        // draw the item to be swapped
        drawSquare(file_ptr, (rgb){1,0,0},  1 + ((i+1) * scale * scale) , ypos , (scale * scale), (scale * scale), 3);

    }


    // draw the sorted array
    ypos -= spacing;
    drawArray(file_ptr,array ,1 ,n , 0, ypos, 6, (rgb){0.25,0.25,0.25}, (rgb){0,0,0});

}