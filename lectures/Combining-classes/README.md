template: titleslide
# Combining classes
## James Richings
## j.richings@epcc.ed.ac.uk



---
# Plan

	- **Inheritance**
		- Inheritance principles
		- Multi-level inheritance
		- Multiple inheritance
		- Access specifiers
		- Polymorphism
	- (new) **Example** (40 mins)
		- Try out different inheritance types 
		- Try out polymorphism 
	- **Design patterns** (optional)
		- What are design patterns?
		- What are some examples?
		- Discuss a couple of each type
			- Creational
			- Structural
			- Behavioural
		- Direct at resources for other patterns but highlight limitation.

---
# Class manipulation so far

We have discussed:

- How to create new object types with classes.
- How to edit the properties of classes around:
  - creation
  - destruction
  - copying
  - movement
- How to build containers with classes with a specific purpose
- How to use templates so that classes can be used in a generic way.

---
# Whats left?

Can we combine classes to make new classes?

- Inheritance
- Multi-level Inheritance
- Multiple Inheritance
- Access specifiers
- Polymorphism
- ... also lots more but we will stop here.

---
# Inheritance

In C++ it is possible to inherit methods and attributes from another class.

There are two types of classes when we talk about inheritance.

- Derived or child classes: A class that inherits from another.
- Base or parent classes: A class that is inherited from.

```
example code
```

---
# Multi-level inheritance

"Its turtles all the way down." - classes

We can have classes that inherit from classes that are have already inherited from a base class.

```
Example code
```

---
# Multiple inheritance

Why limit yourself to one class when you can really confuse yourself...

Classes can also be derived from more than one base class.

```
example code
```

---
# Inheritance and Access specifiers

- Public: Everyone has access
- Private: Only this class has access 
- Protected: Private but also accessible by members of a child class.

```
example code
```

---
# Polymorphism

Allows us to use inheritance to do different things in the derived class than specified in the base class with the same methods.

```
example code
```

---
# Exercise

Take the example complex class we wrote a couple of days ago and ...


- do inheritance: 
  - split complex up so that the contructors and data members live in the base class and a magnitude squared function is in a derived class
- do multi-level inheritance
  - Now in a third class write a absolute magnitude function and have this class inherit from the previous 
- do multiple inheritance 
  - Take new copy of your complex class
  - Write a magnitude class
  - Write an angle class
  - Write a class that represents complex number in polar form that inherits from complex, angle and magnitude
- Polymorphism
  - Write a base class with a function called weatherforecast that prints a message. "rain"
  -  Write a second 





---
# Design patterns

Great we have ways to combine classes together now what?

What are some of the  common ways of combining classes to generate certain effects in code?

Design patterns provide us with a library of code orginisations to draw from to acheive different effects

---
# Types of design pattern

- Creational
  - "These patterns provide various object creation mechanisms, which increase flexibility and reuse of existing code."
- Structural
  - "These patterns explain how to assemble objects and classes into larger structures while keeping these structures flexible and efficient."
- Behavoural
  - "These patterns are concerned with algorithms and the assignment of responsibilities between objects."

Nice resource for this: https://refactoring.guru/design-patterns/catalog

---
# Creational Patterns


- Factory
- Abstract factory
- Builder
- Singleton
- Prototype

---
# Structural

- Adapter
- Bridge
- Composite
- Decorator
- Facade
- Flyweight
- Proxy

---
# Behavourial

- Chain of Responsibility
- Command
- Iterator
- Mediator
- Memento
- Observer
- State
- Strategy
- Template Method
- Visitor

