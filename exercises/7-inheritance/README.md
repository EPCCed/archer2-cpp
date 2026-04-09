# Inheritance exercise

In your clone of this repository, find the `7-inheritance` exercise. It contains three sub-directories `include`, `part1`, `part2` and `part3`.

The `include` sub-directory contains two files: `vector.hpp` and `vertex.hpp`. These contain pre-made `Vector` and `Vertex` classes that you will need for the exercise - you do not need to modify these files.

You can construct a `Vertex` as follows:

```c++
Vertex v1 {1.2, 5.4, 2.0};
Vertex v2 {3.5, 1.0, 0.0};
```

You can construct a `Vector` from two vertices. The resulting vector points from `v1` to `v2`:

```c++
Vector AB {v1, v2};
```

Given two vectors `AB` and `AC`, you can perform mathematical operations:

```c++
AB.magnitude()             // |AB|
AB.dot(AC)                 // AB . AC
AB.cross(AC)               // AB x AC
AB.cross(AC).magnitude()   // |AB x AC|
```

## Part 1 - Multilevel Inheritance

List the files in `part1`:

```bash
$ cd archer2-cpp/exercises/7-inheritance/part1
$ ls
Makefile  element.hpp  main.cpp  tetrahedron.hpp  triangle.hpp
```

We are using header files as these classes require minimal implemenation details, and to reduce the number of files you need to edit. It would still be best practise to use seperate `.hpp` and `.cpp` files for definition and implementation.

As before, you can compile with `make`.

1. `element.hpp` contains a base class for geometric elements defined by a set of vertices called `Element`. This is mostly complete - add access specifiers to the class definition.
2. Implement the `Element2D` and `Element3D` classes in `element.hpp`. These should both inherit from `Element`.
3. Implement the `Triangle` class in `triangle.hpp`. This inherits from `Element2D`.
4. Implement the `Tetrahedron` class in `tetrahedron.hpp`. This inherits from `Element3D`.
5. Test your implementation using `main.cpp`. For each of the member functions of `Triangle` and `Tetrahedron`, which class in the inheritance stack originally defined the function? Which class is providing the implementation?


## Part 2 - Virtual Functions

List the files in `part2`:

```bash
$ cd archer2-cpp/exercises/5-templates/part2
$ ls
Makefile  element.hpp  main.cpp  tetrahedron.hpp
```

We have provided completed versions of `Element3D` and `Tetrahedron` in `element.hpp` and `tetrahedron.hpp` respectively, as well as a test program in `main.cpp`.

1. Run `main.cpp`. Make a note of the output.
2. Change the argument type of the `print()` function in `main.cpp` to `Element3D`.
3. Run `main.cpp` again and compare to the previous output. Is the output what you expected? Can you explain why this happened?
4. Update `Element` and `Element3D` to use virtual functions where necessary. Use the `override` keyword for functions overriding virtual functions.

> ### Extension
> 
> Lookup "pure virtual functions". Can you use these to convert `Element` and `Element3D` into abstract base classes? Which member functions should be pure virtual functions?


## Part 3 - The Diamond Problem (Virtual Inheritance)

List the files in `part3`:

```bash
$ cd archer2-cpp/exercises/5-templates/part3
$ ls
Makefile  element.hpp  main.cpp  quadrilateral.hpp  tetrahedron.hpp  triangle.hpp
```

We have provided completed versions of `element.hpp` and `tetrahedron.hpp`, as well as `parallelogram.hpp` and a test program in `main.cpp`.

Both `Tetrahedron` and `Parallelogram` are defined using 4 vertices. They each have accessor functions `v1()`, `v2()`, `v3()` and `v4()` for each of the vertices.

1. Lets extract these functions (along with `getNumVertices()`) and create a new `Element4V` class that inherits from `Element` to represent an element with 4 vertices. It should contain these accessor methods and `getNumVertices()`.
2. Change `Tetrahedron` and `Parallelogram` to inherit from `Element4V` as well as `Element3D` and `Element2D` respectively.
3. Run `make` to compile `main.cpp`. Can you explain the error message?
4. Use virtual inheritance to solve the diamond problem. HINT: What changes do you need to make to the constructors? Derived classes are responsible for calling the constructor of any virtual classes they inherit.

> ### Extension
> 
> Could we reduce the code duplication in the `Tetrahedron` and `Parallelogram` constructors by creating default constructors for some of the parent classes? There isn't a "right" answer, but C++ gives us flexibility to choose how we design our classes, and how we want to use them.
