# Containers exercise

In your clone of this repository, find the `3-containers` exercise. It contains two sub-directories `part1` and `part2`. List the files in `part1`:

```bash
$ cd archer2-cpp/exercises/3-containers/part1
$ ls
Makefile  test.cpp  vector_ex.cpp  vector_ex.hpp
```

As before, `test.cpp` holds some basic unit tests and you can compile with `make`.

## Part 1
`vector_ex.cpp`/`.hpp` hold some functions that work on `std::vector` - provide the implementations.

`GetEven` has one argument - `std::vector<int> const& source`.  It should return a new vector containing only the even elements from the input vector.

`PrintVectorOfInt` has two arguments - `std:ostream& output` and `std::vector<int> const& data`. It should print the contents of `data` to the provided output stream.

Example output: `[ 0, 1]`

Or for an empty vector: `[ ]`

## Part 2
List the files in `part2`:

```bash
$ cd archer2-cpp/exercises/3-containers/part2
$ ls
Makefile  test.cpp
```

Implement, in a new header/implementation pair of files (`map_ex.hpp`/`.cpp`), a function (`AddWord`) that adds words to a `std::map`. The map should have string keys and integer values, where the integer value is the length of the key. The function should return `true` if the word was added, or `false` if the word was already present in the map.

For example:

```c++
bool wordAdded = AddWord(wlen_map, "Implement")
```

would add "Implement" to `wlen_map` as a key, with the value set to 9.

You will want to find the documentatation for `map` on https://en.cppreference.com/
