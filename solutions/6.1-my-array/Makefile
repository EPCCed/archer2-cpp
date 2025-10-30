CXXFLAGS = --std=c++17 -I../include

all: part1 part2 part3 test

clean :
	rm -rf *.o part1 part2 part3 test

part1 : part1.o
	$(CXX) $^ -o $@

part2 : part2.o
	$(CXX) $^ -o $@

part3 : part3.o
	$(CXX) $^ -o $@

test : test.o
	$(CXX) $^ -o $@

%.o: %.cpp my_array.hpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@