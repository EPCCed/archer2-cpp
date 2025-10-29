#include <iostream>

template <typename T>
T sum(const T& a, const T& b) {
  T result = a + b;

  std::cout << a << " + " << b << " = " << result << std::endl;
  return result;
}

int main() {
  // 3 + 4 = 7
  sum(3, 4);

  // 3.2 + 5.1 = 8.3
  sum(3.2, 5.1);

  sum<std::string>("Hello", "World!");
}