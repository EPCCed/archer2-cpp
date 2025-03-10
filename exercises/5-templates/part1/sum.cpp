#include <iostream>

int sum(const int& a, const int& b) {
  int result = a + b;

  std::cout << a << " + " << b << " = " << result << std::endl;
  return result;
}

int main() {
  // 3 + 4 = 7
  sum(3, 4);

  // 3.2 + 5.1 = 8.3
  sum(3.2, 5.1);

  // sum("Hello", "World!");
}