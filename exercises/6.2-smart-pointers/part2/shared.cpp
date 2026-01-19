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

  // TODO: Create a shared pointer of A called p1

  // TODO: Call printA()

  // TODO: Print address of the containing pointer


  std::cout << std::endl
    << "------------" << std::endl
    << " Create p2 " << std::endl
    << "------------" << std::endl;

  // TODO: Create a new shared pointer p2 that shares ownership of p1

  // TODO: Call printA()

  // TODO: Print the addresses of p1 and p2


  std::cout << std::endl
    << "------------------" << std::endl
    << " Manage ownership " << std::endl
    << "------------------" << std::endl;

  // TODO: Print the use count of p1 and p2

  // TODO: Look up how to relinquish ownership of a resource
  // Relinquish ownership of p1

  // TODO: Print the use count of p1 and p2

  // TODO: Print the addresses of p1 and p2

  return 0;
}