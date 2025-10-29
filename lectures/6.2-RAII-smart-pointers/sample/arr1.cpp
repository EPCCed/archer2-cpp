#include <iostream>

class my_array {
  unsigned size = 0;
  double* data = nullptr;
public:
  my_array() = default;
  my_array(unsigned n) : size(n), data(new double[n]) {
    std::cout << "Constructing: " << data << std::endl;
  }

  // Destructor
  ~my_array() {
    std::cout << "Destroying: " <<data << std::endl;
    delete[] data;
  }

  double& operator[](unsigned i) {
    return data[i];
  }
};

int main() {
  auto null = my_array{};
  auto x = my_array{10};
}
