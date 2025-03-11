# Templates exercise

In your clone of this repository, find the `5-templates` exercise. It contains two sub-directories `part1` and `part2`.

## Part 1

List the files in `part1`:

```bash
$ cd archer2-cpp/exercises/5-templates/part1
$ ls
Makefile  sum.cpp
```

1. Have a look at `sum.cpp`. Do you think it will compile? If so, what will the output be?
2. Compile and run the provided code with `make && ./sum`. Is the result what you expected? Can you explain what is happening at line 12?
```C++
11    sum(3, 4);
12    sum(3.2, 5.1);
13    // sum("Hello", "World!");
```
3. Uncomment line 13. What happens when you try to compile?
3. Change the `sum()` function to use type templating. How does this change the output? Hint: C++ will not automatically convert from a char array to std::string so you will need to be explicit.


## Part 2

List the files in `part2`:

```bash
$ cd archer2-cpp/exercises/5-templates/part2
$ ls
Makefile  complex.cpp  complex.hpp  test.cpp
```

`complex.cpp` contains a working version of the complex number class. Change the class declaration and definitions to use type templating.
