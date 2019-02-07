.PHONY: clean

mandel :
	gcc mandel.c -lm && ./a.out 1000 -3 1 2 1 40 2 && display out.ppm && rm -f a.out

clean :
	rm -f *.ppm
