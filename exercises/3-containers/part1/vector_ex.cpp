#include "vector_ex.hpp"

// std::vector documentation:
// https://en.cppreference.com/w/cpp/container/vector

std::vector<int> GetEven(std::vector<int> const& source) {
  auto ans = std::vector<int>{};
  for (auto&& elem: source) {
    if (elem % 2 == 0)
      ans.push_back(elem);
  }
  return ans;
}

void PrintVectorOfInt(std::ostream& output, std::vector<int> const& data) {
  output << "[ ";
  bool first = true;
  for (auto const& x: data) {
    if (!first) {
      output << ", ";
    }
    first = false;
    output << x;
  }
  output << "]";
}
