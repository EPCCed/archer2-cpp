CXXFLAGS = --std=c++17 -I../../include

test : test.o
	$(CXX) $^ -o $@

run : test
	./test

clean :
	rm -rf *.o test
