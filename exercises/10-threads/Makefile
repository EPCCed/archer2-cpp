# Makefile for mandelbrot area code

#
# C compiler and options for Intel
#
CC=     icpc 
CFLAGS = -fast -std=c++11 
LIB=    -lm -lpthread 

#
# Object files
#
OBJ=    area.o

#
# Compile
#
area:   $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIB)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

#
# Clean out object files and the executable.
#
clean:
	rm *.o area
