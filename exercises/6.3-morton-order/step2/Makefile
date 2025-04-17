include ../config.mk
exes = test_matrix_base test_matrix_iter

all : $(exes)

test_matrix_base : test_matrix_base.cpp matrix.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

test_matrix_iter : test_matrix_iter.cpp matrix.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean :
	-rm -f *.o $(exes)
