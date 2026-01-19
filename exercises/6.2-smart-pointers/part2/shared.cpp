#include <iostream>
#include <memory>

struct A {
    void printA() { std::cout << "A struct...." << std::endl; }
};

int main() {

// https://en.cppreference.com/w/cpp/memory/shared_ptr

// TODO: Create a shared pointer of A called p1


// Printing the address of the managed object
std::cout << p1.get() << std::endl;
p1->printA();

// Creating a new shared pointer p2 that shares ownership of p1

p2->printA();

// Printing addresses of p1 and p2
std::cout << p1.get() << std::endl;
std::cout << p2.get() << std::endl;

// TODO: Print the use count of p1 and p2

// TODO: Look up how to relinquishes ownership of p1
 
std::cout << p1.get() << std::endl;

// TODO: Print the use count of p1

std::cout << p2.get() << std::endl;

return 0;
}