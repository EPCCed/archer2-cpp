template: titleslide

# Resource management
## Nathan Mannall, EPCC
## n.mannall@epcc.ed.ac.uk

---
# Resources

In a program you often need to manage things like:

- memory

- open files

- GPUs

- network sockets

???

Let's talk a bit about memory first

---
# Memory: overview

.columns[
.col[
Modern OSes given each process a flat address space

Each byte can be accessed by its address, which is just a number.

For most purposes this can be considered in two parts:
- stack
- heap
]
.col[
.center[
![:scale_img 50%](mem_layout.jpg)
]
]
]

---
# Memory: stack

In C++ (and C and many other compiled languages) local variables are
stored in the **stack**.

As your program runs, the local variables that are defined, get space
allocated by the compiler relative to the current stack frame.

Each time you call a function, you start a new stack frame by
incrementing the stack pointer.

Variables are implemented as offsets from this, so allocating a local
variable has no run-time cost.

When you return from a function, the stack pointer is updated and
deallocation also has no cost

These allocations are called *static* because they have to be prepared
at compile time

---
# Memory: heap

The language and OS also make available some memory for dynamic
allocation: the *heap*

You need to request some memory to store an object and then give it
back when you are finished

???

Fortran has allocatable arrays and somewhat restricted pointers

C programmers will be familiar with malloc and free, which is also
present in C++, but should never be used (I can't recall ever having
done so)

---
# Pointers in C++

In C++ you can get a pointer to an object using `&` (the *address of* operator)

You can read or write the value-that-is-pointed-to with `*` (the *dereference* operator)
 
```C++
int main() {
  int i = 99;
  int* i_ptr = &i;

  *i_ptr += 1;
  std::cout << i << std::endl;
}
```

---
# Pointers vs references

Pointers are a lot like references, but they are not guaranteed to be
initialised to a valid value!

It is valid to assign an arbitrary value to a pointer, but actually
using it is **undefined behaviour** - typically a crash but could be
silent corruption of data.

```C++
int main() {
  int* i_ptr = 0xdeadbeef;

  *i_ptr += 1;
  std::cout << i << std::endl;
}
```
Use pointers with great caution!

---
# Pointers vs references

Pointers are a lot like references, but they are not guaranteed to be
initialised to a valid value!

It is valid to assign an arbitrary value to a pointer, but actually
using it is **undefined behaviour** - typically a crash but could be
silent corruption of data.

```C++
int* make_bad_pointer() {
  int i = 42;
  return &i;
}
```

Returning a pointer to a local variable is a recipe for problems

???

Because once that function returns the lifetime of the target object
has ended and accessing it is UB

---
# Pointers to dynamically allocated memory

In C++ you can manually create instances of objects dynamically with
`new` and try to remember to destroy them with `delete`

But doing so is a recipe for problems!

???

Using new and delete throughout your code is generally going to cause
you problems, even with extensive use of tools like AddressSanitizer (ASan)
and Valgrind

But C++ has a design pattern that can tame this - first another feature of the language

---
# Pointers exercise

Write a new C++ code to test your understanding of pointers.

Start with an int x and give it a value.

Create a pointer to x and show how to dereference the pointer and increment the value of x.

Make sure your print the location of the pointer and x in memory so you convince yourself no data movement has occurred.

Second create an double array y of 4 elements and give each element a value.

Create two pointers one for each of the 0th and 1st members of the array.

Incrementing the pointer to the 0th element of the array and show the pointer now points to the 1st element of the array.

Make sure to print the location of the pointer and array elements in memory to convince yourself no data movement has occurred.
