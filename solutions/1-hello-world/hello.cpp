#include <iostream>
#include <string>

void say_hello(std::string name) {
  std::cout << "Hello, " << name << "!" << std::endl;
}

int main(int argc, char* argv[]) {
  std::cout << "What is your name?" << std::endl;
  auto name = std::string{};

  // Read from the terminal
  std::cin >> name;

  // Have the program greet the user by name
  say_hello(name);

  return 0;
}