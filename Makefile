.PHONY: clean

mandle : graph.h mandel.c
	clang -Wall -o mandel mandel.c -lm

clean :
	rm -f mandel