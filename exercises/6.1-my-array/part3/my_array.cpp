#include <iostream>

class my_array {
  unsigned size = 0;
  double* data = nullptr;
public:
  my_array() = default;
  my_array(unsigned n) {
    std::cout << "Constructing: " << data << std::endl;
    // TODO: Implement constructor
  }

  // Copy constructor
  my_array(my_array const& other) {
    std::cout << "Copy constructing: " << data << std::endl;
    // TODO: Implement copy constructor
  }

  // Copy assignment operator
  my_array& operator=(my_array const& other) {
    std::cout << "Destroying: " << data << std::endl;
    // TODO: Implement copy assignment operator
    std::cout << "Copy assigning: " << data << std::endl;
  }

  // Move constructor
  my_array(my_array&& other) noexcept {
    std::cout << "Move construct: " << data << std::endl;
    // TODO: Implement move constructor
  }

  // Move assignment operator
  my_array& operator=(my_array&& other) noexcept {
    std::cout << "Move assign: " << data << std::endl;
    // TODO: Implement move assignment operator
  }

  // Destructor
  ~my_array() {
    std::cout << "Destroying: " <<data << std::endl;
    // TODO: Implement destructor
  }

  double& operator[](unsigned i) {
    return data[i];
  }
};

my_array make() {
  return my_array{100};
}

int main() {
  {
    auto null = my_array{};
    auto x = my_array{10};
    auto x_cp = x;
    null = x;
  }
  auto y = make();
  auto z = std::move(y);
  y = std::move(z);
}