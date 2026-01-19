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

  // TODO: Define a unique pointer of A called p1

  // TODO: Call printA()

  // TODO: Print address of the containing pointer


  std::cout << std::endl
    << "------------" << std::endl
    << " Create p2 " << std::endl
    << "------------" << std::endl;

  // TODO: Make a new unique pointer of A called p2

  // TODO: Call printA()

  // TODO: Print the addresses of p1 and p2


  std::cout << std::endl
    << "-----------" << std::endl
    << " Update p2 " << std::endl
    << "-----------" << std::endl;

  // TODO: Set p2 equal to p1
  // What happens when you compile this?

  // TODO: Use move to move p1 into p2 instead, what happens?

  // TODO: Print the addresses of p1 and p2

  return 0;
}