#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"

/* takes two complex numbers and multiplies them */
struct complex complex_mult(struct complex x, struct complex y) {
	double ac = x.a * y.a;
	double bd = x.b * y.b;
	double prod_of_sums = (x.a + x.b) * (y.a + y.b);
	struct complex result = {ac - bd, prod_of_sums - ac - bd};
	return result;
}

/* takes two complex numbers and adds them */
struct complex complex_add(struct complex x, struct complex y) {
	struct complex result = {x.a + y.a, x.b + y.b};
	return result;
}

/* takes a complex number and returns it's distance from the origin */
double distance(struct complex z) {
	return sqrt(pow(z.a, 2) + pow(z.b, 2));
}

/* takes a complex number and returns how many times it takes
 to go out of bounds, stops and returns -1 if it reaches the max */
int mandlebrot(struct complex c, int max_iterations) {
	struct complex z = {0, 0};
	int count = 0;

	while (distance(z) <= 2 && count < max_iterations) {
		z = complex_mult(z, z);
		z = complex_add(z, c);
		count++;
	}

	if (count==max_iterations)
		return -1;
	else
		return count;
}

/* takes the number of iterations to go out of bounds and returns
an rgb struct */
struct rgb get_color(int n) {
	struct rgb result = {0, 0, 0};
	if (n == -1) {
		return result;
	} else {
		result.r = 255 - pow(n, 2);
		result.g = 255 - n;
		result.b = 255; //- pow(n, 3); //* atan(n * 3.14 / 180) * 2.0 / 3.14; 
		return result;
	}

}

/* takes pixels per unit, the coordinates of the top left corner
 of the image, a logical width and a height and makes a graph object */
struct graph *make_graph(long pixel_density, double x, double y, double log_width, double log_height, int max) {
	long physical_width = log_width * pixel_density;
	long physical_height = log_height * pixel_density;
	long size = physical_height * physical_width;

	struct graph *plane = malloc(sizeof(struct graph));
	plane->pixels = malloc(sizeof(struct rgb) * size);

	plane->log_width = log_width;
	plane->log_height = log_height;
	plane->phys_width = physical_width;
	plane->phys_height = physical_height;
	plane->color_depth = 255;

	if (plane == 0 || plane->pixels == 0) {
		fprintf(stderr, "make_graph: allocation failed\n");
		exit(1);
	}

	double logical_pixel_size = log_width / (double)pixel_density;

	for (long i = 0; i < size; i++) {
		double a = x + ((i % physical_width) * logical_pixel_size);
		double b = y - (floor(i / (double)physical_width) * logical_pixel_size);
		struct complex c = {a, b};
		plane->pixels[i] = get_color(mandlebrot(c, max));
	}

	return plane;
}


int main()
{
	// --- tests ---

	/* complex_mult
	struct complex x = {1, 1};
	struct complex y = {0, 5};
	struct complex z = {2, 7};
	printf("(1+1i)(0+5i) = %d + %di\n", complex_mult(x, y).a, complex_mult(x,y).b);
	printf("(2+7i)(0+5i) = %d + %di\n", complex_mult(z, y).a, complex_mult(z,y).b); */

	/* mandlebrot
	struct complex x = {-1, 0};
	printf("%f + %fi goes out of bound in %d steps \n", x.a, x.b, mandlebrot(x, 1000));
	struct complex y = {2, 0};	
	printf("%f + %fi goes out of bound in %d steps \n", y.a, y.b, mandlebrot(y, 1000));
	struct complex h1 = {1, 0};	
	printf("%f + %fi goes out of bound in %d steps \n", h1.a, h1.b, mandlebrot(h1, 1000));
	struct complex h2 = {0.25, 0};	
	printf("%f + %fi goes out of bound in %d steps \n", h2.a, h2.b, mandlebrot(h2, 1000));
	struct complex h3 = {0.26, 0};	
	printf("%f + %fi goes out of bound in %d steps \n", h3.a, h3.b, mandlebrot(h3, 1000));
	struct complex h4 = {0.3, 0};	
	printf("%f + %fi goes out of bound in %d steps \n", h4.a, h4.b, mandlebrot(h4, 1000)); */

	// --- CHANGE SETTINGS HERE ---

	// default / zoomed out version
	//struct graph *g = make_graph(600, -3, 1, 2, 1, 1000);
	// zoomed in 
	struct graph *g = make_graph(1000, -1.5, 0.75, 1, 1, 100);

 	// ... loop(s) to write horizontally-mirrored image to stdout ...

	printf("P3\n");
  	printf("%d %d\n", g->phys_width, g->phys_height);
  	printf("%d\n", g->color_depth);

  	for (int i =0; i < g->phys_height; i++) {
  		for (int j = 0; j < g->phys_width; j++) {
  			printf("%d ", g->pixels[(i * g->phys_width) + j].r);
  			printf("%d ", g->pixels[(i * g->phys_width) + j].g);
  			printf("%d ", g->pixels[(i * g->phys_width) + j].b);
  		}
  		printf("\n");
  	}

  	free(g->pixels);
  	free(g);
  	return 0;  

}









