CXXFLAGS = --std=c++17 -I../../include

sum : sum.o
	$(CXX) $^ -o $@

run : sum
	./sum

clean :
	rm -rf *.o sum
