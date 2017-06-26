/** @file tsp.h
 *  @brief prototypes of the TSP functions.
 *	
 *  @author AL-Tam, Faroq
 *  @bug No known bugs.
 */

#ifndef _TSP_H 
#define _TSP_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "file.h"


 // the city

/** @brief Draw a TSP problem into an EPS file
 *  @param file_ptr FILE * struct of the EPS file
 *  @param city   city * struct of the cities.
 *  @param n      int, the number of cities
 *  @param eps_with float, the width of the eps canvas
 *  @param eps_height float, the height of the eps canvas
 *  @return void
 */
void draw_tsp(FILE * file_ptr, int n, float eps_width, float eps_height);

/**
 *  @brief Check if a given tour is valid.
 *	a valid tour contains all cities, and each city is visited only once
 *	therefore, we check if all cities in the tour are different, ie no repeatation
 * 	since the tour will only have the home city being repeated at the end, we execlude the last element form the validation
 *  @param cities city *, an array of cities
 *  @param n int, the number of cities in this array
 *  @return 1 if the tour is valid, and 0 otherwise.
 */
int is_valid_tour(cidade * cities, int n);

/**
 *  @brief Calcuate the distance between two cities
 *  @param a city, first city
 *  @param b city, the second city
 *  @return the distance between a and b
 */
float distance (cidade a, cidade b);


#endif