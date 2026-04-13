CXXFLAGS = --std=c++17

unique : unique.o
	$(CXX) $^ -o $@

run : unique
	./unique

clean :
	rm -rf *.o unique