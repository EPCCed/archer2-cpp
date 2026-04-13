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


## Part 2 - Multiple Inheritance

List the files in `part2`:

```bash
$ cd archer2-cpp/exercises/7-inheritance/part2
$ ls
Makefile  element.hpp  main.cpp  tetrahedron.hpp  triangle.hpp
```

1. Copy your completed versions of `element.hpp`, `main.cpp`, `tetrahedron.hpp` and `triangle.hpp` from part 1.
2. Implement the new `Material` class in `material.hpp`. A material should be defined by its name and density, and contain a single method `describe()` that runs a string.
3. Update the `Tetrahedron` class to inherit from both `Element3D` and `Material`.
4. Update `main.cpp` to print the new material properties of a tetrahedron using the `describe()` method.

## Part 3 - Virtual Functions

List the files in `part3`:

```bash
$ cd archer2-cpp/exercises/5-templates/part3
$ ls
Makefile  element.hpp  main.cpp  tetrahedron.hpp
```

We have provided completed versions of `Element3D`, `Triangle` and `Tetrahedron` in `element.hpp`, `triangle.hpp` and `tetrahedron.hpp` respectively, as well as a test program in `main.cpp`.

1. Run `main.cpp`. Make a note of the output.
2. Change the argument type of the `print()` function in `main.cpp` to `Element3D`.
3. Run `main.cpp` again and compare to the previous output. Is the output what you expected? Can you explain why this happened?
4. Update `Element` and `Element3D` to use virtual functions where necessary. Use the `override` keyword for functions overriding virtual functions.

> ### Extension
> 
> Lookup "pure virtual functions". Can you use these to convert `Element` and `Element3D` into abstract base classes? Which member functions should be pure virtual functions?
