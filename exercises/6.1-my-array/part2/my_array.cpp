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

  // Destructor
  ~my_array() {
    std::cout << "Destroying: " <<data << std::endl;
    // TODO: Implement destructor
  }

  double& operator[](unsigned i) {
    return data[i];
  }
};

int main() {
  auto null = my_array{};  // Default constructor
  auto x = my_array{10};   // Construct from int
  auto x_cp = x;           // Copy constructing
  null = x;                // Copy assigning
}