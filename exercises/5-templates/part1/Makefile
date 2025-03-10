CXXFLAGS = --std=c++14 -I../../include

sum : sum.o
	$(CXX) $^ -o $@

run : sum
	./sum

clean :
	rm -rf *.o sum
