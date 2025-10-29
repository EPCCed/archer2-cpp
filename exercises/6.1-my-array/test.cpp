// Catch2 is a unit testing library
// Here we let it create a main() function for us
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <type_traits>

#define MY_ARRAY_NO_LOGGING
#include "my_array.hpp"

template <class T>
std::enable_if_t<!std::numeric_limits<T>::is_integer, bool>
equal_within_ulps(T x, T y)
{
  // Copied from: https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
  // Since `epsilon()` is the gap size (ULP, unit in the last place)
  // of floating-point numbers in interval [1, 2), we can scale it to
  // the gap size in interval [2^e, 2^{e+1}), where `e` is the exponent
  // of `x` and `y`.

  // If `x` and `y` have different gap sizes (which means they have
  // different exponents), we take the smaller one. Taking the bigger
  // one is also reasonable, I guess.
  const T m = std::min(std::fabs(x), std::fabs(y));

  // Subnormal numbers have fixed exponent, which is `min_exponent - 1`.
  const int exp = m < std::numeric_limits<T>::min()
                ? std::numeric_limits<T>::min_exponent - 1
                : std::ilogb(m);

  // We consider `x` and `y` equal if the difference between them is
  // within `n` ULPs.
  return std::fabs(x - y) <= std::ldexp(std::numeric_limits<T>::epsilon(), exp);
}

my_array make_array() {
  my_array const x{"x", 10};
  for (double i = 0; i < 10; ++i) {
    x[i] = i;
  }
  return x;
}

void check_array(my_array const& x) {
  for (double i = 0; i < 10; ++i) {
    INFO(x[i] << " != " << i);
    REQUIRE(equal_within_ulps(x[i], i));
  }
}


// TEST CASES START HERE //////////////////////////////////////////////

TEST_CASE("Default constructor") {
  my_array const default_array;
  REQUIRE(default_array.name == "default");
  REQUIRE(default_array.size == 0);
  REQUIRE(default_array.data == nullptr);
}

TEST_CASE("Constructor") {
  my_array const x{"x", 10};
  REQUIRE(x.name == "x");
  REQUIRE(x.size == 10);
}

TEST_CASE("Copy constructor") {
  my_array const x = make_array();
  my_array const x_cp = x;
  REQUIRE(x_cp.name == "x_cp");
  REQUIRE(x_cp.size == 10);
  REQUIRE(x_cp.data != x.data);
  check_array(x_cp);
}

TEST_CASE("Copy assignment") {
  my_array const x = make_array();
  my_array y{"y", 5};
  double* y_data = y.data;
  y = x;
  REQUIRE(y.name == "y");
  REQUIRE(y.size == 10);
  REQUIRE(y.data != x.data);
  INFO("The pointer y.data has not changed - did you delete the previous pointer?");
  REQUIRE(y.data != y_data);
  check_array(y);
}

TEST_CASE("Move constructor") {
  my_array x = make_array();
  double* x_data = x.data;
  my_array const x_mv = std::move(x);
  REQUIRE(x_mv.name == "x_mv");
  REQUIRE(x_mv.size == 10);
  REQUIRE(x_mv.data == x_data);
  REQUIRE(x.name == "x");
  REQUIRE(x.size == 0);
  REQUIRE(x.data == nullptr);
  check_array(x_mv);
}

TEST_CASE("Move assignment") {
  my_array x = make_array();
  double* x_data = x.data;
  my_array y{"y", 5};
  double* y_data = y.data;
  y = std::move(x);
  REQUIRE(y.name == "y");
  REQUIRE(y.size == 10);
  REQUIRE(y.data == x_data);
  REQUIRE(x.name == "x");
  REQUIRE(x.size == 5);
  REQUIRE(x.data == y_data);
  check_array(y);
}
