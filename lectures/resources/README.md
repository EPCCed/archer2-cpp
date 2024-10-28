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
# Destructors

You can also control what happens when your objects reach the end of
their lifetime.

When this happens is deterministic:
- when a local variable goes out of scope
- when an object that contains them is destroyed
- when the programmer `delete`s them

For a class `Name` they are declared like:

```C++
struct Name {
  ~Name();
};
```

It's important to note that you should **never call this directly** -
the compiler will call it for you when your objects are deallocated.

???

Note the tilde syntax is the logical negation of the class. Cf
annihilation operators for any physicists.


---
# Resource allocation is instantiation

A very important pattern in C++ is **RAII**: resource allocation is
instantiation.

Also known as constructor acquires, destructor releases (CADRe).

This odd name is trying to communicate that any resource you have
should be tied to the lifetime of an object.

So the when the compiler destroys your object it will release the
resource (e.g. memory).

???

Saying that in some philosophical sense allocating a resource is the
creation of something, which implies its destruction later.

---
# RAII example

A very simple copy of `std::vector<double>`:

```C++
class my_array {
  unsigned size = 0;
  double* data = nullptr;
public:
  my_array() = default;
  explicit my_array(unsigned n) : size(n), data(new double[size]) {}
  ~my_array() {
    delete[] data;
  }
  double& operator[](unsigned i) {
    return data[i];
  }
};
```

???

This class allocates some memory to store `n` doubles when constructed

When it reaches the end of its life the destructor returns the memory
to the OS

It allows users to access elements (with no bounds checking)

---
# What happens when we compile and run?

Add a few annotations to print in the contructor/destructor

???

Open sample/arr1.cpp
Compile and run

What happens if we copy x?

Add `auto x_cp = x;` (same as `auto x_cp = my_array{x};`)

---
# Copying

When you value assign an object in C++ this will only be valid if
there is a *copy constructor* or *copy assignment operator*

--

Copy constructor - when you create a new object as the destination:

```C++
my_array x{10}; // Direct initialisation
my_array y{x}; // Direct initialisation
my_array z = x; // Copy initialization
```

--
Copy assignment - when you assign a new value to an existing object

```C++
my_array x{10};
x = my_array{2000};
```

???

What's the diff?

In the last case, you have to deal with releasing any resources held
by the target object

---
# Implicit copy

The compiler will automatically generate these operations for us if
all the data members of you class are copyable.

So what went wrong with the example shown?

--
A pointer is just a number and so it can be copied implicitly - hence the double delete

If we want to copy our array then we need to either:
- copy the data (aka deep copy)
- share the data and somehow keep track of when the last reference to it is destroyed (aka shallow copy)

???

Deep copies are more expensive at run time but somewhat safer

Shallow copies can be faster but harder to implement correctly and can have thread safety issues

Do we want to copy?

---
# User-defined copy

Of course, you can control how your objects are copied


```C++
class my_array {
  unsigned size = 0;
  double* data = nullptr;
public:
  my_array() = default;
  explicit my_array(unsigned n) : size(n) data(new double[size]) {}
  my_array(my_array const& other) : size(other.size), data(new double[size]) {
    // Copy data
  }
  my_array& operator=(my_array const& other) {
    delete[] data;
    size = other.size;
    data = new double[size];
	// Copy data
	return *this;
  }
  ~my_array() {
    delete[] data;
  }
};
```
???

Open arr2.cpp

Note the signature

---
# Returning a value looks a lot like copying

When a function returns a value, you might think that will copy it to the target:

```C++
std::vector<int> ReadData() {
  std::vector<int> answer;
  // Read it from somewhere
  return answer;
}

int main() {
  auto data = ReadData();
}
```

???

Thinking about std::vector examples we've seen and that you might have implemented

Have previously said that you should use bare auto when you want a
copy - by that what we really mean is you want to *own* the object and
control its lifetime.

Copying a vector of billions of elements is going to get expensive and
would be counter to C++'s zero overhead abstractions principle

---
# Move instead

Since C++11, the language has supported the concept of *moving* from
objects which the compiler knows (or the programmer asserts) will not
be used any more.

Examples are:
- temporaries (i.e. the result of a function call/constructor expression)
- automatic variables that are going out of scope
- the result of calling `std::move` on an object

The destination object "steals" the contained resources from the
source object and sets the source to a valid but undefined state -
typically the only operations you can perform on a moved-from object
are destruction and assignment.

---
# Move implementation

Going back to our simple array:
```C++
class my_array {
  unsigned size = 0;
  double* data = nullptr;
public:
  // c'tors, copy assignment, d'tor
  my_array(my_array&& other) noexcept : size(other.size), data(other.data) {
    other.size = 0;
    other.data = nullptr;
  }
  my_array& operator=(my_array&& other) noexcept {
    std::swap(size, other.size);
    std::swap(data, other.data);
  }
};
```

???

Comment on `noexcept` - this is for STL compatibility. The containers
will copy if your move operations are not noexcept. These ones cannot
throw exceptions so this is safe.


Look at arr3.cpp

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
# Standard library to the rescue!

The standard library contains some help:

`std::unique_ptr` is a pointer that uniquely owns the object(s) it
points to.

Pointers can be moved but *not* copied - this is achieved by the copy
constructor and copy assignment operators being `delete`d:

```
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

Try out some of this with exercises/morton-order

Instructions can be found here:

archer2-cpp/exercises/morton-order/instructions.md

