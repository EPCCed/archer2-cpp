template: titleslide
# Templates
## Nathan Mannall
## n.mannall@epcc.ed.ac.uk

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
