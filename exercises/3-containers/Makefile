CXXFLAGS = --std=c++17 -I../include

test : vector_ex.o map_ex.o test.o
	$(CXX) $^ -o $@

run : test
	./test

clean :
	rm -rf *.o test
