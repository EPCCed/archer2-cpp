#include <iostream>
#include <memory>

struct A {
    void printA() { std::cout << "A struct...." << std::endl; }
};

int main() {

// https://en.cppreference.com/w/cpp/memory/unique_ptr

// TODO: Define a unique pointer of A called p1 


p1->printA();

// displays address of the containing pointer
std::cout << p1.get() << std::endl;

// TODO: Make a new unique pointer of A p2
// Set it equal to p1
// What happens when you compile this?

// TODO: Use move to move p1 into p2 instead, what happens?

p2->printA();
std::cout << p1.get() << std::endl;
std::cout << p2.get() << std::endl;

    return 0;
}