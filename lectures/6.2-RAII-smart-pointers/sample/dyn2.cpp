#include <iostream>

class dyn_array {
  unsigned size = 0;
  double* data = nullptr;
public:
  dyn_array() = default;
  dyn_array(unsigned n) : size(n), data(new double[n]) {
    std::cout << "Constructing: " << data << std::endl;
  }
  dyn_array(dyn_array const& other) : size(other.size), data(new double[size]) {
    std::cout << "Copy constructing: " << data << std::endl;
    std::copy(other.data, other.data + size, data);
  }
  dyn_array& operator=(dyn_array const& other) {
    std::cout << "Destroying: " <<data << std::endl;
    delete[] data;
    size = other.size;
    data = new double[size];
    std::cout << "Copy assigning: " << data << std::endl;
    std::copy(other.data, other.data + size, data);
    return *this;
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
  auto x_cp = x;
  null = x;
}
