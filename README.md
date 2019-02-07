# Mandlebrot
A C program that generates bitmap (.ppm) images of the Mandelbrot Set

![The Mandelbrot Set](https://github.com/rabisnath/Mandelbrot/tree/master/Scrapbook/test.png)
![Sea Horse Valley](https://github.com/rabisnath/Mandelbrot/tree/master/Scrapbook/seahorse_valley1.png)
![Sea Horse Valley 2](https://github.com/rabisnath/Mandelbrot/tree/master/Scrapbook/seahorse_valley2.png)

## How To Use
The function draw_graph takes seven inputs:
1) pixel density: The number of pixels used to represent a length of one on the complex plane.
2) logcial x: The x-coordinate of the top left corner of the viewing window on the complex plane. 
3) logcial y: The y-coordinate of the top left corner of the viewing window on the complex plane.
4) logical width: The width of the viewing window on the complex plane.
5) logical height: The height of the viewing window on the complex plane.
6) max iterations: The maximum nuber of times the program will iterate f_c(z) at each input.
7) color option: The inputs are: 0 for black and white, 1 for color based on the number of iterations to go out of bounds, and 2 for smooth color based on the renormalization of the number of iterations to escape bounds.

Generate different images of the Mandelbrot Set by changing these parameters when calling the executable in the command line.

## The Makefile
- Type 'make' in the console to complile.
- Type 'make clean' to delete the executable and any ppms generated.

## Notes For Use
The program takes a noticeable number of seconds to run when asked to genereate larger images with higher pixel density. Performance can be dramatically improved by changing the pixel density and max iterations parameters.

## TODO:
Change the color pallete to something that fills the space better.
Improve performance.
