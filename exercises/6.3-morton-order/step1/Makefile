include ../config.mk

exes = test_matrix_base

all : $(exes)

test_matrix_base : test_matrix_base.cpp matrix.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean :
	-rm -f *.o $(exes)
