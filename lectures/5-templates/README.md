template: titleslide
# Templates and Traits
## Luca Parisi, EPCC
### l.parisi@epcc.ed.ac.uk

???

We've hinted at this already, with `std::vector<int>`, `std::shared_ptr<Cowboy>` etc


---
# Motivation

Templates are a method of doing *metaprogramming*: a
program that writes a program.

An easy example:

```C++
int sum(int a, int b) {
  return a+b;
}
double sum(double a, double b) {
  return a+b;
}
```

What if we need this for `float`, `unsigned`, and our `Complex` class
from earlier lectures?

Going to get boring and hard to maintain quickly!

???

Recall the sum functions from the first lecture

---
# Template functions

```C++
template <typename T>
T sum(T a, T b) {
  return a+b;
}
```

We can *instantiate* this template for a particular type explicitly by
giving the type inside angle brackets:

```C++
std::cout << "add unsigned=" << sum<unsigned>(1U, 4U) << std::endl;
std::cout << "add floats=" << sum<float>(1.0f, 4e-2f) << std::endl;
```

???

Here the compiler will replace every use of `T` with the type you
supply and only then will it compile the code

---
# Template functions

```C++
template <typename T>
T sum(T a, T b) {
  return a+b;
}
```

You can also let the compiler *deduce* what `T` is for you

```C++
std::cout << "add unsigned=" << sum(1U, 4U) << endl;
std::cout << "add floats=" << sum(1.0f, 4e-2f) << endl;
```
???

This is called implicit template instantiation - there are a few
wrinkles that we'll talk about soon

---
# Template classes

You can define a template class - i.e. a template that will produce a
class when you instantiate it.

Let's adapt the `my_array` container to hold any type `T`

```C++
template<class T>
class my_array {
  unsigned size = 0;
  T* data = nullptr;

public:
  my_array();
  my_array(unsigned n);
  // Copy / move?
  ~my_array();
  unsigned size() const;
  const T& operator[](unsigned i) const;
  T& operator[](unsigned i);
};
```

???
Talk through the syntax of the template

We use `T*` as the type of the stored data and `T&` as the return type
of `operator[]`

---
# Type aliases

Often it is useful to be able to create a new name for a type

C++ supports a `using` declaration for this.

```C++

using MyImportantType = int;

using iter = std::map<std:string, std::vector<LongTypeName>>::iterator;
```

???

Really common when creating class templates as if you don't it may be
very hard to figure out the type parameters it was instantiated for in
from other code.

---
# Using declaration in class templates

```C++
template<class T>
class my_array {
  unsigned size = 0;
  T* data = nullptr;

public:
  using value_type = T;
  using reference = T&;
  using const_reference = T const&;
  // ...
  const_reference operator[](unsigned i) const;
  reference operator[](unsigned i);
};
```

---
# Where to put your implementation?

```C++
// main.cpp

#include <iostream>

template <typename T>
T addOne(T x); // function template forward declaration

int main()
{
    std::cout << addOne(1) << '\n';
    std::cout << addOne(2.3) << '\n';

    return 0;
}
```

```C++
// add.cpp

template <typename T>
T addOne(T x) // function template definition
{
    return x + 1;
}
```

???
`main.cpp` will compile - it can see the forward declartion and trusts the implementaitons will be compiled.

`add.cpp` will compile, but not it will not instatiate anything as it does
not see any uses of the `addOne` function. Therefore you will get a linker error.

We fix this by putting all the template code in a header file. Each `.cpp` file
will see the template definition and instatiate any functions as needed.

---
# Where to put your implementation?

Templates are *not* executable code - they tell the compiler how to
create it.

So the definition must be available in the translation unit of the user of your template - i.e. typically in a header file.

You can define the functions in place like:

```C++
template<class T>
class my_array {
public:
  my_array() : _size(0), _data(nullptr) {}
};
```

Or at the end of the header (or equivalently in another file that you
include at the end of your header)

```C++
template<class T>
my_array<T>::my_array(unsigned n) : _size(n) {
  _data = new T[n];
}
```

???
Point out the uglier syntax of the second form but on the other hand
the class definition shown earlier is cleaner with only the member
function declarations

But surely this process can cause the same function to be defined in
multiple places? (Next slide)

---
# Templates and the One Definition Rule

So I said earlier that everything used had to be defined exactly once.

This has two exceptions:

1. Templates

2. Functions marked `inline`

These can be repeated in many "translation units" (i.e. separate
invocations of the compiler)

At link time the linker will arbitrarily pick one definition to use in
the final executable (so you need to make sure that they are all
identical).

---
# Templates and type deduction

Recall:
```C++
template<class T>
T sum(T a, T b) {
  return a+b;
}
```

We then used this without specifying, explicitly, what type `T` was - e.g.:
```C++
int x = 1, y = 2;
auto z = sum(x, y);
```

The compiler is doing *template argument deduction*.

This means it examines the types of the expressions given as arguments
to the function and then tries to choose a `T` such that the type of
the argument and the expected type match.

---
# Templates and type deduction

Important to note that the template parameter `T` and the type of
function arguments might be different (but related)

```C++
template <class T>
void f(T x);

template <class T>
void ref(T& x);

template <class T>
void const_ref(T const& x);

template <class T>
void forwarding_ref(T&& x);

template <class T>
void vec(std::vector<T> x);
```

This will affect the deduced argument type

---
# Non-type template parameters

Can also parameterise template with non-types:
- integers
- pointers
- enums
- (and in C++20, floating point types and "literal types")

E.g.:

```C++
template <int N>
class Vec;

template <int ROWS, int COLS>
class Matrix;

template<int ROWS, int COLS>
Vec<ROWS> operator*(Matrix<ROWS, COLS> const& A, Vector<COLS> const& x);
```

???
The compiler will now ensure that the matrix and vector are of compatible
shapes and if you make a mistake will give an error!

The size of the answer is correctly deduced for you

---
# Templates and type deduction

Full rules are quite complex

See Meyer's Effective Modern C++ chapter 1 - free online
https://www.safaribooksonline.com/library/view/effective-modern-c/9781491908419/ch01.html

In short:

![:thumb]( But usually you can ignore these and just think about:
1. Whether you want to copy the argument or not  - if you don't want a
copy add a reference `&`
2. Whether you can handle a const argument - if so add a `const` qualifier
3. If you want *exactly* the type of the expression - if so add `&&` -
   this is known as a forwarding reference)

---
# Auto

The `auto` keyword follows the same rules as template argument
deduction

---
template: titleslide

# Traits
---

# Type traits

- Important C++ generic programming technique, used across the
    standard library

- The "if-then-else" of types

- Provide a template class that has typedefs/member functions that
    specify the configurable parts

- Your generic algorithm then uses this class, specialised on the type
    it is working on, to select behaviour

- You do not have to change the source of either the algorithm or the
    working type

---

# STL traits

Several headers contain these:

-   The header `<type_traits>` has lots of information for handling
    types. E.g. `std::is_pointer<int>::value` has value of false.

-   `std::numeric_limits<T>` gives lots of parameters for the built in
    number types, such as largest and smallest values, whether they are
    integer or floating types, etc.

Other traits are used everywhere behind the scenes for efficiency.

---

# Real example

Suppose you are writing a wrapper around MPI to allow use without
having to always say `MPI_FLOAT` - since the compiler knows the types
already!

```C++
class Comm {
public:
  template <class T>
  void send(const std::vector<T>& data,
			int dest, int tag);
};

auto& world = Mpi::CommWorld();
std::vector<int> data = {2, 4, 6, 8};

world.send(data, other_rank, tag);
```

---

# Real example

Simplified implementation:

```C++
template <class T>
void Comm::send(const std::vector<T>& data, int dest, int tag) {
  MPI_Send(reinterpret_cast<void*>(data.data()), data.size(),
		   DATATYPE,
		   dest, tag, m_comm);
}
```

--
How to fill in the right type?

For the types in the standard, we could
provide a specialisation for each one:

```C++
template <>
void Comm::send<int>(const std::vector<int>& data, int dest, int tag) {
  MPI_Send(reinterpret_cast<void*>(data.data()), data.size(),
		   MPI_INT,
		   dest, tag, m_comm);
}
```

---

# Real example

But there are lots of types (say `M`) and lots of MPI calls (say `N`)
to be wrapped, so we have to write `M * N` specialisations...

Also how to add any custom types? User would have to mess around with
our library.

---
# Real example

Create a traits class that tells our functions how to handle different
types:

```C++
template <class T>
struct DataTypeTraits {
  // Don't provide a default definition
  // (because there is no generic way to make an MPI datatype)
  static MPI_Datatype Get();
};

template <class T>
void Comm::send(const std::vector<T>& data, int dest, int tag) {
  MPI_Send(reinterpret_cast<void*>(data.data()), data.size(),
         DataTypeTraits<T>::Get(),
		 dest, tag, m_comm);
}
```

---

# Real example

Then we can then provide a specialised definition for all the types we
can handle:

```C++
template<>
MPI_Datatype DataTypeTraits<int>::Get() {
  return MPI_INT;
}
  
template<>
MPI_Datatype DataTypeTraits<float>::Get() {
  return MPI_FLOAT;
}

// etc
```

If we try to communicate a data type we haven't specialised for, we
will get a compile time error!

---
template: titleslide
# Exercise

---
# Templates Exercise

In your clone of this repository, find the `5-templates` exercise. It contains two sub-directories `part1` and `part2`.

**Part 1**

1. Have a look at `sum.cpp`. Do you think it will compile? If so, what will the output be?
2. Compile and run the provided code with `make && ./sum`. Is the result what you expected? Can you explain what is happening at line 12?
```C++
11    sum(3, 4);
12    sum(3.2, 5.1);
13    // sum("Hello", "World!");
```
3. Uncomment line 13. What happens when you try to compile?
4. Change the `sum()` function to use type templating. How does this change the output?


**Part 2**

`complex.cpp` contains a working version of the complex number class. Change the class declaration and definitions to use type templating.

As before, `test.cpp` holds some basic unit tests and you can compile with `make`.
