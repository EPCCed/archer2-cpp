# Hello World! exercise

In your clone of this repository, find the `1-hello-world` exercise and list the files

```
$ cd archer2-cpp/exercises/1-hello-world
$ ls
README.md  hello.cpp
```

## Compile and Run

View the program source code. Make sure you understand what each part does.

Compile the program:

```bash
$ g++ --std=c++17 hello.cpp -o hello
```

No output means success!

Run it:

```bash
$ ./hello
```

## Exercise

Update `hello.cpp` so that it greets the user by name:

- Use `std::cout` to print a message to the user asking for their name
- Use `std::cin` to read their response and save it to a variable
- Create a function called `say_hello` that accepts a single string argument and prints `Hello [NAME]` to standard output.
  - Remember to call the function!