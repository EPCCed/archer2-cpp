CXXFLAGS = --std=c++17

my_array : my_array.o
	$(CXX) $^ -o $@

run : my_array
	./my_array

clean :
	rm -rf *.o my_array