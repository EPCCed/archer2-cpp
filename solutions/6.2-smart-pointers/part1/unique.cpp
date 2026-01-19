#include <iostream>
#include <memory>

struct A
{
  void printA() { std::cout << "A struct...." << std::endl; }
};

int main()
{
  // https://en.cppreference.com/w/cpp/memory/unique_ptr

  std::cout
    << "------------" << std::endl
    << " Create p1 " << std::endl
    << "------------" << std::endl;

  // Define a unique pointer of A called p1
  auto p1 = std::make_unique<A>();

  // Call printA()
  p1->printA();

  // Print address of the containing pointer
  std::cout << "p1: " << p1.get() << std::endl;


  std::cout << std::endl
    << "------------" << std::endl
    << " Create p2 " << std::endl
    << "------------" << std::endl;

  // Make a new unique pointer of A called p2
  auto p2 = std::make_unique<A>();

  // Call printA()
  p2->printA();

  // Print the addresses of p1 and p2
  std::cout << "p1: " << p1.get() << std::endl;
  std::cout << "p2: " << p2.get() << std::endl;


  std::cout << std::endl
    << "-----------" << std::endl
    << " Update p2 " << std::endl
    << "-----------" << std::endl;

  // Set p2 equal to p1
  // What happens when you compile this?
  // p2 = p1;

  // Use move to move p1 into p2 instead, what happens?
  p2 = std::move(p1);

  // Print the addresses of p1 and p2
  std::cout << "p1: " << p1.get() << std::endl;
  std::cout << "p2: " << p2.get() << std::endl;

  return 0;
}