CXXFLAGS = --std=c++17

pointers : unique.o
	$(CXX) $^ -o $@

run : unique
	./unique

clean :
	rm -rf *.o unique