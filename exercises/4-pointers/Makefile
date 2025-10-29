CXXFLAGS = --std=c++17

pointers : pointers.o
	$(CXX) $^ -o $@

run : pointers
	./pointers

clean :
	rm -rf *.o pointers