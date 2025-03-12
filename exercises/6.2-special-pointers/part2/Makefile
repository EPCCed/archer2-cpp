CXXFLAGS = --std=c++17

pointers : shared.o
	$(CXX) $^ -o $@

run : shared
	./shared

clean :
	rm -rf *.o shared