CXXFLAGS = --std=c++17 -I../../include

test : complex.o test.o
	$(CXX) $^ -o $@

run : test
	./test

clean :
	rm -rf *.o test
