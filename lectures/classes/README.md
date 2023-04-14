template: titleslide
# Classes
## Maurice Jamieson, EPCC
## m.jamieson@epcc.ed.ac.uk


---
# User defined types

Called "class types" formally - can be defined with either the `class`
or `struct` keyword.

```C++
struct Complex {
  double re;
  double im;
};
```

Let's show this on Compiler Explorer: https://godbolt.org/z/j8Kf31T89

This style of type is often called a "plain old data" (POD) type or a
"trivial" type.

This simply aggregates together several *members* which have a name
and type. You can then pass them around together and access the data.

???

Talked already about the built in types and one of the library
provided types (`std::string`)


---
# Class types

Creating trivial types - give the class name then list the values to be assigned to the
members, _in order_, inside braces:

```C++
Complex mk_imaginary_unit(void) {
  return Complex{0, 1};
}
```
This is called aggregate initialisation.

Alternatively:
```C++
Complex mk_imaginary_unit(void) {
  Complex sqrt_m1; // Values are uninitialised
  sqrt_m1.re = 0;
  sqrt_m1.im = 1;
  return sqrt_m1;
}
```

---
# Class types

Using trivial types:

```C++
void test(void) {
  Complex z = mk_imaginary_unit();
  assert(z.re == 0);
  assert(z.im == 1);
  return 0;
}
```

Any piece of code can access the member variables inside the object.

???

This is probably something you're familiar with from other languages and the
same as C

---
template: titleslide
# Creating instances

---
# Default member initialisers

In the class definition you can (should?) provide default values for
member variables:

```C++
struct Complex {
  double re = 0.0;
  double im = 0.0;
};
```

Now when you create an object it will be initialised to a known state
for you:

```C++
void test(void) {
  Complex z;
  assert(z.re == 0);
  assert(z.im == 0);
}
```

???

Why "should"? 

The compiler will generate code for you to set the defaults whenever
you create these objects - can't forget to do this.

Why not should?

Perhaps your types act as much like the builtin types as
possible. Initialising members incurs a RUNTIME COST which perhaps you
don't wish to pay.

---
# Default member initialisers

A note for C++11: you lose the ability to set the member variables by
just providing the values:

```C++
struct Complex {
  double re = 0.0;
  double im = 0.0;
};

Complex mk_imaginary_unit(void) {
  return Complex{0, 1};
}
```

GCC says:
```
error: no matching constructor for initialization of 'Complex'
  return Complex{0,1};
```

---
# Constructors
Often you want to control the creation of instances of your classes.

You do this with _constructors_ - these are special member "functions"
with the same name as the type.

```C++
struct Complex {
  Complex() = default;
  Complex(double re);
  Complex(double re, double im);
  double re = 0.0;
  double im = 0.0;
};
```

Note we declare three:
- one that initialises with a purely real value
- one that initialises with a real and imaginary value
- a *default constructor* which needs no arguments (that we tell the
  compiler to generate for us as before with `= default` )

???

Control in more detail than just starting from a default value or
having to provide *all* the of member values.

Constructors are not strictly functions in C++ but very nearly (next slide)

Why do you have to "explictly default the default constructor"?

Because the language rules say if the user provides any constructors,
the compiler must not create one unless asked to...

---
# Constructors

- Constructors are not directy callable
- Constructors do not return a value
- Constructors can do initialisation of member variables before the body begins execution


Let's define the ones we declared just now:

```C++
Complex::Complex(double real) : re(real) {
}

Complex::Complex(double real, double imag) : re(real), im(imag) {
}
```

???

Point out the member initialiser syntax after the colon

Assert that this is where you want to do as much initialisation as you
possibly can.


---
# Creating complexes

We can now create complex numbers different ways
```C++
auto zero = Complex{}; // Uses default member initialisers
auto pi = Complex{3.14159}; // pi.im == 0.0
auto sqrt_minus_one = Complex{0, 1};
Complex one = 1.0;
```

---
template: titleslide
# Member functions

---
# Object-oriented programming

Object oriented programming is one of the major paradigms supported by
C++

> OOP is based on the concept of "objects", which may contain data and
> code. A feature of objects is that an object's procedures can access
> and often modify the data of the object with which they are
> associated.

In C++ these attached bits of code are known as member functions -
other languages might call them methods

For example:

```C++
int main(void) {
  std::string name;
  std::cin >> name;
  std::cout << "Hello, " << name << ". "
            << "Your name has " << name.size() << " characters." << std::endl;
  return 0;
}
```
???

Quote from wikipedia

Note that an object in C++ may not be an object in the OOP sense!

---
# Member functions

Typically these are declared in the class definition...

```C++
// complex.hpp
struct Complex {
  // Constructors as before
  double magnitude(void) const;

  double re = 0.0;
  double im = 0.0;
};
```

???

If anyone asks, discussion of const is coming up!

---
# Member functions

... and defined out of line

```C++
// complex.cpp
double Complex::magnitude(void) const {
  return std::sqrt(re*re + im*im);
}
```

Within a member function we can access the members (data or function)
by just giving their names.

Outside the class, we need to have an instance to use:

```C++
Complex z{3, 4};
assert(z.magnitude() == 5.0);
```

???

The compiler inserts an implicit argument referring to the current
instance for us, known as the 'this' pointer. See https://www.learncpp.com/cpp-tutorial/the-hidden-this-pointer/
for more info

---
# More on operator overloading

Complex numbers have the usual arithmetic operations: `\(+-\times\div\)`

We can provide operator overloads, like:

```C++
struct Complex {
  // Other members...

  Complex& operator+=(Complex const & increment) {
    re += increment.re;
    im += increment.im;
    return *this;
  }
};
Complex operator+(Complex const& a, Complex const& b) {
  return Complex{a.re+b.re, a.im+b.im};
}
```

Here, `operator+=` is using the implicit `this` pointer

???

Recall that these are just functions (with funny names)

We have a member function `operator+=` and a non-member (aka free
function)

The compiler is already implicitly turning `a+b` into plus(a, b)
internally.

If anyone asks, references and `const` coming up

---
# More on operator overloading

Complex numbers have the usual arithmetic operations
(`\(+-\times\div\)`) and comparisons.

We can now use the natural syntax to add these values

```C++
Complex i{0, 1};

Complex z;
z += i;

assert(z.re == 0 && z.im == 1);

auto c = z + i;
assert(c == 2*i);
```

???

We could also overload multiplication and equality comparison as shown
in the last line

Go look up the complete list on CPP Reference!

---
# Classes and structs

You define a class using either the `struct` or `class` keywords -
technically the difference is only the default _accessibility_ of
members.

Members can be:

- `public`: usable from any piece of code - i.e. the public interface
  of the class - default for `struct`

- `private`: only usable from with a the context of the class -
  i.e. an implementation detail of the class that should be of no
  interest to code that uses it - default for `class`

Restricting access to implementation details is part of encapsulation:
another common aspect of OOP


???

Context of a class means from inside a member function or from
elsewhere in the class scope


---
# Access Control

```C++
class Greeter {
  std::string greetee;
  void say_hello(void) const {
    std::cout << "Hello, " << greetee << std::endl;
  }
};

void test(Greeter const& g) {
  g.say_hello();
}
```
???

Compiler will say something like
`error: 'say_hello' is a private member of 'Greeter'`

---
# Access Control

```C++
class Greeter {
  std::string greetee;
public:
  void say_hello(void) const {
    std::cout << "Hello, " << greetee << std::endl;
  }
};

void test(Greeter const & g) {
  g.say_hello();
}
```
???

To fix this need to add the `public` access specifier

Why is encapsulation worth bothering with? Enforces modularity and can
(sometimes) swap out parts of the implementation for e.g. performance
without have to re-write the client code

A class can declare another function (or class) its `friend` which
allows only that bit of code to access its private member variables.

This is a controlled, partial relaxation of encapsulation that often
makes the whole system more isolated.


---
template: titleslide
# Constants

---
# Const-ness

Variables can be qualified with the `const` keyword

- objects marked with `const` cannot be modified

- compiler will give errors if you try 

```C++
int main(void) {
  int const i = 42;
  std::cout << i << std::endl;
  // prints 42

  i += 10;
  // error: cannot assign to variable 'i' with const-qualified type 'const int'
  return 0;
}
```

You should be adding `const` to your local variables whenever possible.

???

We can have a few degrees of constantness

1. known at compile time: the value of pi is
   always 3.14159... Compiler might be able to help us here

2. local variable: the variable gets a single value for that one
   execution of that block of code. Compiler probably won't speed it
   up, but it helps us humans:
	* You are giving something a *name* so you can refer to it again. It
	means you won't accidentally change something
	* give it a proper name: `local_mean_density` not `d`
    * Maybe do this even if you only use it once (compiler will
      probably optimise it away)

---
# Const-ness

Since function parameters are just local variables, they can be
`const` too.

```C++
Complex operator-(Complex const a, Complex const b) {
  return Complex{a.re - b.re, a.im - b.im};
}
```

Since this function has no need to modify it's arguments, they should
be marked as `const`

???

Deliberately omitting the `&` for references - that's next


---
# Const-ness

Member functions have an implicit argument of the instance they
"belong" to.

If they do not need to change an instance, then they should be marked
`const` also:

```C++
struct Complex {
  double magnitude(void) const;
};
```

???

`this` pointer, if anyone asks, but we don't like pointers


Member variables can be marked `const`, but don't do it

---
# East-const vs West-const

As far as the compiler and language specification are concerned, both
of these are identical:

.columns[
.col[
```C++
const int i = 42;
```

Rule: `const` applies to what is on its left, unless there is nothing on its left, then it applies to what is on its right

]
.col[
```C++
int const i = 42;
```
Rule: Always put `const` on the right of what it modifes
]
]

It doesn't really matter as long as you're **consistent** within a project.

???

East const is a little more logical hence using it here!

Older codebases (and C++ programmers) will be West const (e.g. RWN)

---
template: titleslide
# References

---
# Copying

By default, if assign a variable a new value, C++ will copy it
```C++
double copy = original;
```

Same if you pass a value of some type to a function, it will be
copied to a new local variable for the invocation of a function:

```C++
SimState AdvanceOneTimeStep(SimState old);

// later...
next_state = AdvanceOneTimeStep(current_state);
```

???
Exactly what copying means for a class type is up to the programmer -
forms part of the interface

If you're doing some complex simulation like computational fluid
dynamics/molecular dynamics, the `current_state` will be large and be
expensive (in time and memory) to copy.

---
# References

C++ has the concept of a **reference**.

- A reference is a name that aliases an already existing object

- A reference must be initialised (function arguments are initialised
  by calling)

- A reference cannot be rebound to a new object

```C++
void ScaleVector(double scale, std::vector<double>& x) {
  // Multiply every element of x by scale
}

void test(void) {
  std::vector<double> data = ReadLargeFile();
  ScaleVector(-1.0, data);
}
```

???

We qualify the type with the ampersand `&` after the type and before
the variable name.

When I say must be intialised, mean that you can't just declare a
reference variable without initialising it

At the call site the reference is bound to parameter and the function
can refer to `data` without copying it

This is close to the way that Fortran passes arguemnts to subroutines

---
# References and Const

You can qualify a reference as const:

```C++
SimState AdvanceOneTimeStep(SimState const& old) {
  // do some science...
  return new_state;
}
```

???

This means that the program cannot modify the contents of `old`
through that name.

The compiler will give an error if you try to change it (or a call a
function that could change it).

---
# Functions can return a reference

Many classes have data members that they want to let their client have
some access to without (necessarily) copying

Or access to a single value from the many they might contain

```C++
class AtomList {
  std::vector<Vec3> position;
  std::vector<Vec3> velocity;
  std::vector<double> charge;
public:
  std::vector<double> const& GetCharge(void) const {
    return charge;
  }
};

void analyse_md_data(void) {
  AtomList const atoms = ReadFromFile();
  std::vector<double> const& charges = atoms.GetCharge();
  std::cout << "Average charge = "
            << std::accumulate(charges.begin(), charges.end()) / charges.size()
			<< std::endl;
}
```

???

So when we call the `GetCharge` the local var `charges` refers to the
same data contained inside `atoms` without doing any copying

Returning references is very common - especially for containers that
we'll talk about later.

---
# References and const with `auto`

When you declare a variable with `auto` you can qualify it it as a
reference and/or `const`:

- Use `auto x` when you want a modifiable copy

- Use `auto&& x` when you want a reference and the same `const`-ness
  as the initialiser

- Use `auto const &x` when you want a reference to original item and
  will not modify it

![:thumb](Use the last whenever possible)

???

Note double ampersand in 2nd point - it's called a 'forwarding reference' and we will
come back to it

Refer back to the last slide codes and ask

- what happens if instead of `std::vector<double> const&` we put
  `auto charges`? (charges deduces to `std::vector` and we copy)

- `auto const & charges` (charges deduces just that same as written -
  we have a reference)

- `auto&& charges`? (exactly as before but *if* we had returned a
  mutable reference then it would be a mutable ref while `auto const&`
  would have stayed constant)


---
template: titleslide
# C++ compilation

---
# Declarations vs Definitions

C++ distinguishes between *declaration* and *definition*.

A **declaration** tells the compiler that a name exists, what kind of
entity it refers to and (if it is a function or variable) its
type. For most uses this is all the compiler needs. Declarations can
be repeated, as long as they match *exactly*.

A **definition** tells the compiler everything it needs to create
something in its entirety. A definition is also a declaration. The
one-definition rule says that definitions must not be repeated (with
an exception).

???

The exceptions being templates and `inline` functions if anyone asks

---
# Where to put these

- Conventionally, one puts declarations of functions, definitions of
  classes, and global constants in **header** files.

	- Common suffixes are: `.hpp`, `.h`, `.H`

- Definitions of most functions should be in **implementation** files

	- Common suffixes are `.cpp`, `.cxx`, `.cc`, `.C`

- Headers can be be `#include` into other files that need to use the
  types and function declared there.

???

Suffixes mostly meaningless to the compiler but don't surprise people!

Prefer earlier in the list i.e. .hpp and .cpp to differentiate between C++
and C code

---
# Where to put these

E.g. Complex.hpp:

```C++
#ifndef COMPLEX_HPP
#define COMPLEX_HPP

struct Complex {
  Complex() = default;
  // etc...
private:
  double re;
  double im;
};

Complex operator+(Complex const& a, Complex const& b);
// Etc...

#endif
```
???

Draw attention to the include guard idiom - include the file only once

---
# Exercise

In your clone of this repository, find the `complex` exercise and list
the files

```
$ cd archer2-cpp/exercises/complex
$ ls
Makefile	complex.cpp	complex.hpp	test.cpp
```

The files `complex.hpp` and `complex.cpp` contain a partially working
complex number class and `test.cpp` holds some basic unit tests.

You can compile and run with:
```
$ make && ./test
c++ --std=c++14 -I../include   -c -o complex.o complex.cpp
c++ --std=c++14 -I../include   -c -o test.o test.cpp
c++ complex.o test.o -o test
===============================================================================
All tests passed (34 assertions in 6 test cases)
```

But to get to this point you need to complete the code and fix a few
bugs!

???

Ask who knows about 'make' maybe?
