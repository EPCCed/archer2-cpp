CXXFLAGS = --std=c++20

main : main.o
	$(CXX) $^ -o $@

run : main
	./main

clean :
	rm -rf *.o main
