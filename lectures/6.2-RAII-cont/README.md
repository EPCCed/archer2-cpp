template: titleslide

# RAII continued
## James Richings, EPCC
## j.richings@epcc.ed.ac.uk


---
template: titleslide

# RAII Rules Recap

---

# The Rule of Five

This says that if you define or delete one of the following:
- copy constructor
- copy assignment operator
- move constructor
- move assignment operator
- destructor

then you should probably do so for all five.

???
This can be quite a lot of work!

---
# The Rule of Zero

This says that unless your class is solely deals with ownership, then
it should define none of the five special functions.

This is really a corollary of the general software engineering 
"principle of single responsibility".

You should split your code into a resource manager with all five
functions and a user class that has none, but uses the resource
manager as one or more data members.

???

If it does deal with ownership then rule of 5 applies :(


---
template: titleslide

# Standard library to the rescue!

---

template: titleslide

# But first Pointers...

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

** Exercise **

Code skeleton in exercises 6.1-pointers
---
template: titleslide

# Finally Standard library to the rescue!

---

# Standard library & special pointers to the rescue!

The standard library contains some help:

`std::unique_ptr` is a pointer that uniquely owns the object(s) it
points to.

Pointers can be moved but *not* copied - this is achieved by the copy
constructor and copy assignment operators being `delete`d:

```C++
class unique_ptr {
  unique_ptr(unique_ptr const &) = delete;
  unique_ptr& operator=(unique_ptr const &) = delete;
};
```
???

Ownership means that it will destroy them when it is destroyed

Obviously there would be a lot more code in the implementation

The syntax is basically the same as defaulting a special function

---
# Using std::unique_ptr

```C++
#include <memory>

class Image {
  Image(std::string const& file) {
    // construct by reading from file...
  }
};

std::unique_ptr<Image> ReadImage(std::string const& filename) {
  return std::make_unique<Image>(filename);
}

int main() {
  auto img_ptr = ReadImage("cats.jpg");
}
```

???

What's going on

Include the memory header

Some type `Image` that has a constructor to read it from a file

Instead of constructing it in the usual way, we pass the constructor
arguments to `make_unique` and it will be allocated on the heap for us

We return the value and because of that, the compiler knows it is
moveable so we move into the local variable img_ptr

When this goes out of scope and is destroyed, it will destroy the
object that is pointed-to

---
# Using pointers

```C++
class Image {
  int x() const {
    //return x_size;
  }
  int y() const {
    //return y_size;
  }
};
std::unique_ptr<Image> ReadImage(std::string const& filename) {
  return std::make_unique<Image>(filename);
}

int main() {
  auto img_ptr = ReadImage("cats.jpg");
  Image& img_ref = *img_ptr;

  auto area = img_ref.x() * img_ref.y();
}
```

???

We didn't do anything with that pointer. Let's imagine it has some
member functions that return the size in pixels and we want to compute
the area

We can dereference the pointer with `operator*`

Returns a reference to the thing-that-is-pointed-to which we can use as normal

---
# Using pointers

```C++
class Image {
  int x() const {
    //return x_size;
  }
  int y() const {
    //return y_size;
  }
};
std::unique_ptr<Image> ReadImage(std::string const& filename) {
  return std::make_unique<Image>(filename);
}

int main() {
  auto img_ptr = ReadImage("cats.jpg");


  auto area = (*img_ptr).x() * (*img_ptr).y();
}
```

???
Don't have to bind a name but this syntax looks rather ugly

---
# Using pointers

```C++
class Image {
  int x() const {
    //return x_size;
  }
  int y() const {
    //return y_size;
  }
};
std::unique_ptr<Image> ReadImage(std::string const& filename) {
  return std::make_unique<Image>(filename);
}

int main() {
  auto img_ptr = ReadImage("cats.jpg");


  auto area = img_ptr->x() * img_ref->y();
}
```

???

Can use the pointer member access operator -> as a much more readable shorthand

---
# std::shared_ptr

Sometimes you want to be able to safely share an object between many
users.

Enter `std::shared_ptr`

This keeps count of how many pointers are alive: increasing the count
on copy and decreasing on destruction.

When this reaches zero the object is destroyed.

```C++
int main() {
  auto shared = std::make_shared<BigObject>();

  auto foo = LongLivedObject{shared};
  complicated_function(foo, shared);
}
```

![:thumb](Prefer unique_ptr unless you really need to share)

???

Why not keen on shared_ptr?

More complex, destruction no longer deterministic

2 other annoying problems with solutions

---
# Niggles with shared_ptr 1

Sometimes you want your class to be able to get a `shared_ptr` to
itself (e.g. to create some other object that depends on it)

```C++
class Widget : public std::enable_shared_from_this<Widget> {
public:
  std::shared_ptr<Widget> self() {
    return shared_from_this();
  }
};
```

You must ensure that a `shared_ptr` has been made before calling
shared_from_this!

???

Ensure `shared_ptr` has been made first by e.g. making constructors
private and calling them from a factory function that returns a
`shared_ptr`

---
# Niggles with shared_ptr 2

Cycles:

```C++
class Cowboy {
  using ptr = std::shared_ptr<Cowboy>;
  std::string name;
  std::shared_ptr<Cowboy> partner;
public:
  Cowboy(std::string const& n) : name(n) {}
  ~Cowboy() { std::cout << "Delete " << name << std::endl; }
  friend void partner_up(ptr a, ptr b) {
    a->partner = b; b->partner = a;
  }
};

int main() {
  auto good = std::make_shared<Cowboy>("Alice");
  auto bad = std::make_shared<Cowboy>("Bob");
  //ugly
  partner_up(good, bad);
}
```
???

Show the code in `sample/shared.cpp` - same as above but instrumented.
Compile and run and note no call of destructor!

The way to break cycles is to use `std::weak_ptr` which doesn't count
towards the reference count.

To use a `weak_ptr`, you must call `lock` member function which
returns a `shared_ptr` that ensures the object lives long enough to be
used.

---
# Raw pointers

Now despite having been mean about pointers, there are some valid
uses - in function interfaces

A function can perfectly well accept a raw pointer as long as it
doesn't want to change the lifetime of the object that is pointed-to

![:thumb](Raw pointers do not own resources - use a smart pointer for that)

![:thumb](Raw pointers represent a single object - use a span for a
contiguous range of objects)

???

C++20 has `std::span` but you can use the guideline support library
if, like most of us, not there yet

---
# Special pointers Exercise

These exercises try to get you to test how each of the special pointers work.

** Part 1 **

Try using a unique pointers in a simple example.

Code skeleton in `6.2-special-pointers/part1`

** Part 2 **

Try using shared pointers in a simple example.

Code skeleton in `6.2-special-pointers/part2`

???


---
# Other resources

For example files - compare Python to C++
.columns[
.col[
```Python
with open(filename) as f:
    data = f.read()

# file is closed on exiting the block
```
]
.col[
```C++
std::string data;
{
  auto f = std::fstream{filename};
  f >> data;
} // file closed by destructor

```
]
]
???

Python with statements are opt-in

Compare to C# using statements (types must implement the `IDisposable`
interface - ugh MS Hungarian notation)

---
# RAII for files

```C++
class File {
private:
  std::unique_ptr<std::FILE> handle = nullptr;
public:
  File() = default;
  File(std::string const& fn, char const* mode) :
    handle{std::fopen(fn.c_str(), mode)} {
  }
  ~File() {
    if (handle) {
      std::fclose(handle.get());
    }
  }
  // Read/write member functions
};
int main() {
  auto f = File{"data.dat", "r"};
}
```

???

`nullptr` - special value to indicate an invalid pointer

private constructor + factory static member function

d'tor closes the file if it has a value

C++ destructors technically are also opt-in - but they really are the
single best feature of the language!

Please use them!

Could also have a network connection, handle to a GPU command stream
etc wrapped here.

---
# Exercise

We are now going to look at bring together what we have learnt around classes, resources, RAII and special pointers in an exercise.

The aim of this exercise is to write a new container class that has a simple vector-like interface but a memory efficent data access pattern under the hood.

Instructions can be found here:

archer2-cpp/exercises/morton-order/instructions.md

