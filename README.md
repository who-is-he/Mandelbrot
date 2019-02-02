# Mandlebrot
A C program that generates bitmap (.ppm) images of the Mandelbrot Set

![Sea Horse Valley](Scrapbook/seahorse_valley2.ppm)

## How to use
The function make_graph takes seven inputs:
1) pixel density: the number of pixels used to represent a length of one on the complex plane.
2) logcial x: the x-coordinate of the top left corner of the viewing window on the complex plane. 
3) logcial y: the y-coordinate of the top left corner of the viewing window on the complex plane.
4) logical width: the width of the viewing window on the complex plane.
5) logical height: the height of the viewing window on the complex plane.
6) max iterations: the maximum nuber of times the program will iterate f_c(z) at each input.
7) color option: 0 for black and white, 1 for color based on the number of iterations to go out of bounds, and 2 for smooth color based on the renormalization of the number of iterations to escape bounds.

Generate different images of the Mandelbrot Set by changing these parameters where make_graph is called in main.

## The Makefile
- Type 'make mandel' in the console to complile.
- Type './mandel > out.ppm' to run.
- Type 'make clean' to delete the executable and any ppms generated.

## Notes for use
The program takes a noticeable number of seconds to run when asked to genereate larger images with higher pixel density. Performance can be dramatically improved by changing the pixel density and max iterations parameters. I still need to fiddle around a little to figure out what the ideal settings are.

## The future
I plan on updating this program in a few ways, first, I want to change the coloration to something that fills the space better, and second, I want to improve the performance, I'm sure this program could be orders of magnitude faster if I knew more about C.