#include "my_array.hpp"

int main() {
  auto null = my_array{};      // Default constructor
  auto x = my_array{"x", 10};  // Construct from string and int
  auto x_cp = x;               // Copy constructing
  null = x;                    // Copy assigning
}