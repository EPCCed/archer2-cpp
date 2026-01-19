#include <iostream>
#include <memory>

struct A
{
  void printA() { std::cout << "A struct...." << std::endl; }
};

int main()
{
  // https://en.cppreference.com/w/cpp/memory/shared_ptr

  std::cout
    << "------------" << std::endl
    << " Create p1 " << std::endl
    << "------------" << std::endl;

  // Create a shared pointer of A called p1
  auto p1 = std::make_shared<A>();

  // Call printA()
  p1->printA();

  // Print address of the containing pointer
  std::cout << "p1: " << p1.get() << std::endl;


  std::cout << std::endl
    << "------------" << std::endl
    << " Create p2 " << std::endl
    << "------------" << std::endl;

  // Create a new shared pointer p2 that shares ownership of p1
  auto p2 = p1;

  // Call printA()
  p2->printA();

  // Print the addresses of p1 and p2
  std::cout << "p1: " << p1.get() << std::endl;
  std::cout << "p2: " << p2.get() << std::endl;


  std::cout << std::endl
    << "------------------" << std::endl
    << " Manage ownership " << std::endl
    << "------------------" << std::endl;

  // Print the use count of p1 and p2
  std::cout << "p1: " << p1.use_count() << std::endl;
  std::cout << "p2: " << p2.use_count() << std::endl;

  // Look up how to relinquish ownership of a resource
  // Relinquish ownership of p1
  p1.reset();

  // Print the use count of p1 and p2
  std::cout << "p1: " << p1.use_count() << std::endl;
  std::cout << "p2: " << p2.use_count() << std::endl;

  // Print the addresses of p1 and p2
  std::cout << "p1: " << p1.get() << std::endl;
  std::cout << "p2: " << p2.get() << std::endl;

  return 0;
}