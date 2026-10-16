CXXFLAGS = --std=c++17 -I../include

main : main.cpp element.hpp material.hpp tetrahedron.hpp triangle.hpp vector.o vertex.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o : ../include/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

run : main
	./main

clean :
	rm -rf *.o test
