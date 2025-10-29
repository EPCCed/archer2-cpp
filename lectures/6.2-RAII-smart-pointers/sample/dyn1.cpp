#include <iostream>

class dyn_array {
  unsigned size = 0;
  double* data = nullptr;
public:
  dyn_array() = default;
  dyn_array(unsigned n) : size(n), data(new double[n]) {
    std::cout << "Constructing: " << data << std::endl;
  }
  ~dyn_array() {
    std::cout << "Destroying: " <<data << std::endl;
    delete[] data;
  }
  double& operator[](unsigned i) {
    return data[i];
  }
};

int main() {
  auto null = dyn_array{};
  auto x = dyn_array{10};
}
