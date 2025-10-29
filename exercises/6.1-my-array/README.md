# my_array exercise

In your clone of this repository, find the `6.1-my-array` exercise and list the files:

```bash
$ cd archer2-cpp/exercises/6.1-my-array
$ ls
Makefile  README.md  my_array.hpp part1.cpp  part2.cpp  part3.cpp  test.cpp
```

`my_array.hpp` contains a partial implementation of an array class. You need to implement the appropriate constructors, assignment operators, and destructors to control the allocation and deletion of memory over the object's lifecycle. 

`part1.cpp`, `part2.cpp`, and `part3.cpp` contain examples using the `my_array` class that you can use to check your implementation and understanding.

For each part (e.g. part1), you can compile by running:

```
$ make part1
g++ --std=c++17 -I../include -c part1.cpp -o part1.o
g++ part1.o -o part1
```

Then run the example using:

```bash
$ ./part1
     Constructing: 0x2300eb0 [x] 
       Destroying: 0x2300eb0 [x] 
       Destroying:         0 [default]
```

Once you have completed all the parts, `test.cpp` contains some basic unit tests to check your implementation. You can compile and run with:

```bash
$ make test && ./test
g++ --std=c++17 -I../include -c test.cpp -o test.o
g++ test.o -o test
===============================================================================
All tests passed (64 assertions in 6 test cases)
```

## Part 1

1. Implement the constructor
2. Implement the destructor

## Part 2

1. Uncomment the marked lines in `array.hpp`
2. Implement the copy constructor
3. Implement the copy assignment operator

## Part 3

1. Uncomment the marked lines in `array.hpp`
2. Implement the move constructor
3. Implement the move assignment operator
