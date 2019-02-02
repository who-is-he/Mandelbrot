#include <stdio.h>
#include <stdlib.h>

struct rgb {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

struct graph {
	unsigned int log_width;
	unsigned int log_height;
	unsigned int phys_width;
	unsigned int phys_height;
	unsigned char color_depth;
	struct rgb *pixels;
};

struct complex {
	double a;
	double b;
};

/* takes two complex numbers and multiplies them */
struct complex complex_mult(struct complex x, struct complex y);

/* takes a pair of coordinates and returns how many times it takes
 to go out of bounds, stops and returns -1 if it reaches the max */
int mandlebrot(struct complex c, int max_iterations);

/* takes the number of iterations to go out of bounds and returns
an rgb struct */
struct rgb get_color(int n);

/* takes pixels per unit, the coordinates of the top left corner
 of the image, a width and a height and makes a graph object */
struct graph *make_graph(long pixel_density, double x, double y, double log_width, double log_height, int max);