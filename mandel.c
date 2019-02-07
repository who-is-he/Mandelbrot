#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define COLOR_DEPTH 255

typedef struct rgb {
  unsigned int r;
  unsigned int g;
  unsigned int b;
} rgb;

typedef struct complex {
    double a;
    double b;
} complex;

// Takes two complex numbers and multiplies them.
complex complex_mult(complex x, complex y)
{
    double ac = x.a * y.a;
    double bd = x.b * y.b;
    double prod_of_sums = (x.a + x.b) * (y.a + y.b);
    complex result = {ac - bd, prod_of_sums - ac - bd};
    return result;
}

// Takes two complex numbers and adds them.
complex complex_add(complex x, complex y)
{
    complex result = {x.a + y.a, x.b + y.b};
    return result;
}

// Takes a complex number and returns its distance from the origin.
double distance(complex z)
{
    return sqrt(pow(z.a, 2) + pow(z.b, 2));
}

// Takes a complex number and returns how many times it takes
// to go out of bounds. Stops and returns -1 if it reaches the max_iterations.
int mandelbrot(complex c, int max_iterations)
{
    complex z = {0, 0};
    int count = 0;

    while (distance(z) <= 2 && count < max_iterations)
    {
        z = complex_mult(z, z);
        z = complex_add(z, c);
        count++;
    }

    if (count == max_iterations)
        return -1;
    else
        return count;
}

// Takes the number of iterations to go out of bounds and returns an rgb struct.
// Option 0: Black and White. 
// Option 1: Basic coloring.
// Option 2: Color using renormalization of the mandelbrot escape.
rgb get_color(int n, int option, double modulus) {
    double mu;
    rgb result = {0, 0, 0};

    if (n == -1)
    {
        return result;
    }
    else if (option == 0)
    {
        result.r = COLOR_DEPTH;
        result.g = COLOR_DEPTH;
        result.b = COLOR_DEPTH;

        return result;
    }
    else if (option == 1)
    {
        result.r = COLOR_DEPTH - pow(n, 2);
        result.g = COLOR_DEPTH - n;
        result.b = COLOR_DEPTH;

        return result;
    }
    else if (option == 2)
    {
        mu = n - (log(fabs(log(modulus))) / log(2.0));
        // if (mu != mu) 
            // fprintf(stderr, "%f | %f\n", modulus, mu);
        result.r = COLOR_DEPTH * mu / 50;
        result.g = 0;
        result.b = 120;
        
        return result;
    }
    else
    {
        fprintf(stderr, "get_color: invalid option\n");
        exit(1);
    }
}
// Creates a mandelbrot image file. 
int draw_graph(int pixel_density, double x, double y, double log_width, double log_height, int max, int option)
{
    unsigned int row, column;
    unsigned int physical_height = log_height * pixel_density;
    unsigned int physical_width = log_width * pixel_density;
    unsigned int size = physical_height * physical_width;
    double logical_pixel_size, a, b;
    complex c;
    rgb pixel;

    FILE *file_data = fopen("out.ppm", "w");

    if (file_data == NULL)
        return -1;

    logical_pixel_size = log_width / (double)pixel_density;

    fprintf(file_data, "P3\n");
    fprintf(file_data, "%u %u\n", physical_width, physical_height);
    fprintf(file_data, "%d\n", COLOR_DEPTH);

    // Calculate each pixels color using the mandelbrot function.
    for (row = 0; row < physical_height; row++)
    {
        for (column = 0; column < physical_width; column++)
        {
            c.a = x + column * logical_pixel_size;
            c.b = y - row * logical_pixel_size;
            pixel = get_color(mandelbrot(c, max), option, distance(c));
            fprintf(file_data, "%d %d %d ", pixel.r, pixel.g, pixel.b);
        }

        fprintf(file_data, "\n");
    }

    fclose(file_data);
    return 1;
}

int main(int argc, char **argv)
{
    double time_taken;
    clock_t t = clock();

    // default / zoomed out version
    // g = make_graph(600, -3, 1, 2, 1, 100, 2);
    
    if (argc != 8)
    {
        fprintf(stderr, "Incorrect number of arguments. Format is <pixel_density> <x> <y> <log_width> <log_height> <max> <option>\n");
        return -1;
    }

    draw_graph(
        atoi(argv[1]), // int pixel_density
        atof(argv[2]), // double x
        atof(argv[3]), // double y
        atof(argv[4]), // double log_width
        atof(argv[5]), // double log_height
        atoi(argv[6]), // int max
        atoi(argv[7])  // int option
    );

    // higher res version of the default !WARNING takes about a minute to run
    // graph *g = make_graph(2400, -3, 1, 2, 1, 1500, 1);
    // zoomed in 
    // graph *g = make_graph(600, -1.5, 0.75, 1, 1, 100, 1);
    // seahorse valley 1
    // graph *g = make_graph(1200, -1, 0.4, 0.75, 0.6, 100, 1);
    // seahorse valley 2 !WARNING takes about a minute to run
    // graph *g = make_graph(20000, -0.85, 0.2, 0.2, 0.1, 100, 2);

    t = clock() - t; 
    time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Mandelbrot generated in %.4fs.\n", time_taken);

    return 0;
}
