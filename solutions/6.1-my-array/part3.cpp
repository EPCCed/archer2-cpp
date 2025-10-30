#include "my_array.hpp"

int main() {
  {
    auto null = my_array{};
    auto x = my_array{"x", 10};
    auto x_cp = x;
    null = x;
  }
  auto y = my_array{"y", 100};;
  auto y_mv = std::move(y);
  y = std::move(y_mv);
}