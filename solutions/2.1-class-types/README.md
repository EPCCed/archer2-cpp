# Class types exercise

In your clone of this repository, find the `2.1-class-types` exercise and list the files

```
$ cd archer2-cpp/exercises/2.1-class-types
$ ls
Makefile  README.md  complex.cpp  complex.hpp  test.cpp
```

The files `complex.hpp` and `complex.cpp` contain the beginings of a complex number class. Follow the instructions in the comments to complete the missing declarations in `complex.hpp` and then add the required out of line definitions in `complex.cpp`.

To test your implementation, `test.cpp` holds some basic unit tests created using the Catch2 unit testing library.

You can compile by running:

```
$ make
g++ --std=c++14 -I../include -c -o complex.o complex.cpp
g++ complex.o test.o -o test
```

Then run the tests using:

```
$ ./test
===============================================================================
All tests passed (36 assertions in 5 test cases)
```
