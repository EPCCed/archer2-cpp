CXXFLAGS = --std=c++14 -I../include

test : complex.o test.o
	$(CXX) $^ -o $@

test.o : catch.hpp

catch.hpp :
	wget https://github.com/catchorg/Catch2/releases/download/v2.13.6/catch.hpp

run : test
	./test

clean :
	rm -rf *.o test
