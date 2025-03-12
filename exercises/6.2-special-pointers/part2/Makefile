CXXFLAGS = --std=c++17

pointers : special.o
	$(CXX) $^ -o $@

run : special
	./special

clean :
	rm -rf *.o special