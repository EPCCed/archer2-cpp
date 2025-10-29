# Containers exercise

In your clone of this repository, find the `3-containers` exercise. It contains two sub-directories `part1` and `part2`. List
the files in `part1`:

```bash
$ cd archer2-cpp/exercises/3-containers/part1
$ ls
Makefile  test.cpp  vector_ex.cpp  vector_ex.hpp
```

As before, `test.cpp` holds some basic unit tests and you can compile with `make`.

## Part 1
`vector_ex.cpp`/`.hpp` hold some functions that work on `std::vector` - provide the implementations

## Part 2
Copy `vector_ex.cpp`/`.hpp` from part 1 into the part 2 folder.

Implement, in a new header/implementation pair of files (`map_ex.hpp`/`.cpp`),
a function (`AddWord`) that adds a string to a `std::map` as the key, the value
being the length of the string.

You will want to find the documentatation for `map` on https://en.cppreference.com/
