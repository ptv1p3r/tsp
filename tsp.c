/** @file tsp.c
 *  @brief Imeplementations of the TSP generic functions found in tsp.h.
 *	
 *  @author AL-Tam, Faroq
 *  @bug No known bugs.
 */

#include "tsp.h"
#include "eps.h"

#define PI 3.141592653589793238
#define SPACE_BETWEEN_CIRCLES_RATIO 0.10 // this value will help us to calculate the radius of the circle
										 // the greater it is the bigger will be the circles

/** @brief Draw a TSP problem into an EPS file
 *  @param file_ptr FILE * struct of the EPS file
 *  @param n   int, the number of cities
 *  @param eps_width float, the width of the eps canvas
 *  @param eps_height float, the height of the eps canvas
 *  @return void
 */

void draw_tsp(FILE * file_ptr, int n, float eps_width, float eps_height) {
	int i = 0;

	// let us try to make this code robust so that it adapts to the problem size

	// normalize the cities positions so that the fit in the eps canvas
	float min_x, min_y;
	float max_x, max_y;
	min_x = cidades[0].x;
	min_y = cidades[0].y;
	max_x = cidades[0].x;
	max_y = cidades[0].y;

	for(i = 1; i < n; i++)
	{
		if(cidades[i].x < min_x)
			min_x = cidades[i].x;
		else if(cidades[i].x > max_x)
			max_x = cidades[i].x;
		if(cidades[i].y < min_y)
			min_y = cidades[i].y;
		else if(cidades[i].y > max_y)
			max_y = cidades[i].y;
	}

	for(i = 0; i < n; i++)
	{
		// calculate the radius
		float radius = (float) (sqrt((eps_width * eps_height / (float) n) / 2 * PI) * SPACE_BETWEEN_CIRCLES_RATIO);
		// calculate the correct x and y and shift for the edge positions
		float x = (radius) + (cidades[i].x - min_x) / (max_x - min_x) * (eps_width - (2 * radius));
		float y = (radius) + (cidades[i].y - min_y) / (max_y - min_y) * (eps_height - (2 * radius));

        // guardamos as coordenadas normalizadas para a cidade
        cidades[i].normX = x;
        cidades[i].normY = y;

		drawCircle(file_ptr, (rgb){0,1,0},x ,y , radius, 0.25);
		char str[5];
		sprintf(str, "%d", cidades[i].id);
		drawText(file_ptr, (rgb){0,0,0}, radius, x, y , str);

	}
}

 /**
 *  @brief Calcuate the distance between two cities
 *  @param a city, first city
 *  @param b city, the second city
 *  @return the distance between a and b
 */
float distance (cidade a, cidade b) {
	 return (float) sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
 }



  /**
 *  @brief Check if a given tour is valid.
 *	a valid tour contains all cities, and each city is visited only once
 *	therefore, we check if all cities in the tour are different, ie no repeatation
 * 	since the tour will only have the home city being repeated at the end, we execlude the last element form the validation
 *  @param cities city *, an array of cities
 *  @param n int, the number of cities in this array
 *  @return 1 if the tour is valid, and 0 otherwise.
 */
int is_valid_tour(cidade * cities, int n) {

	  int i, j;
	  for (i = 0; i < n - 1; i++) {
		  for (j = i + 1; j < n - 1; j++) {
			  if (cities[i].id == cities[j].id) {
				  return 0; // it is not valid
			  }
		  }
	  }
	  return 1; // it is a valid tour
  }