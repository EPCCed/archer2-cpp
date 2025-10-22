# Complex class exercise

In your clone of this repository, find the `2.2-complex` exercise and list the files

```
$ cd archer2-cpp/exercises/2.2-complex$ ls Makefile    complex.cpp    complex.hpp    test.cpp
```

The files `complex.hpp` and `complex.cpp` contain a partially working complex number class and `test.cpp` holds some basic unit tests.

You can compile and run with:

```
$ make && ./test
g++ --std=c++14 -I../include   -c -o complex.o complex.cpp
g++ --std=c++14 -I../include   -c -o test.o test.cpp
g++ complex.o test.o -o test
===============================================================================
All tests passed (34 assertions in 6 test cases)
```

But to get to this point you need to complete the code and fix a few bugs!
