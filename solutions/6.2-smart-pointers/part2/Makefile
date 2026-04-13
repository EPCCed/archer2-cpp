CXXFLAGS = --std=c++17

shared : shared.o
	$(CXX) $^ -o $@

run : shared
	./shared

clean :
	rm -rf *.o shared