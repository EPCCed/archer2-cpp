// Catch2 is a unit testing library
// Here we let it create a main() function for us
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "complex.hpp"

TEST_CASE("Complex numbers are constructed real/imag parts readable") {
  const Complex zero;
  REQUIRE(zero.real() == 0.0);
  REQUIRE(zero.imag() == 0.0);

  const Complex one{1.0};
  REQUIRE(one.real() == 1.0);
  REQUIRE(one.imag() == 0.0);

  const Complex i{0, 1};
  REQUIRE(i.real() == 0.0);
  REQUIRE(i.imag() == 1.0);

  const Complex z1{1, -83};
  const Complex z2 = z1;
  REQUIRE(z1.real() == z2.real());
  REQUIRE(z1.imag() == z2.imag());
  REQUIRE(z2.real() == 1.0);
  REQUIRE(z2.imag() == -83.0);
}

TEST_CASE("Complex numbers can be compared") {
  const Complex zero;
  const Complex one{1.0};
  const Complex i{0, 1};
  REQUIRE(zero == zero);
  REQUIRE(one == one);
  REQUIRE(i == i);
  REQUIRE(zero != one);
  REQUIRE(one != i);
}

TEST_CASE("Complex numbers can have magnitude computed") {
  REQUIRE(Complex{}.norm2() == 0.0);
  REQUIRE(Complex{3,4}.norm2() == 25.0);
}

// Pure real => z == z*
void CheckConjReal(double x) {
  Complex z{x};
  REQUIRE(z == z.conj());
}
// Pure imaginary => z* == -z
void CheckConjImag(double y) {
  Complex z{0.0, y};
  
  REQUIRE(z == -z.conj());
}

TEST_CASE("Complex numbers be conjugated") {
  CheckConjReal(0);
  CheckConjReal(1);
  CheckConjReal(-3.14);
  CheckConjReal(1.876e6);

  CheckConjImag(0);
  CheckConjImag(1);
  CheckConjImag(-3.14);
  CheckConjImag(1.876e6);
}

void CheckZplusZeq2Z(const Complex& z) {
  REQUIRE(z + z == Complex{2*z.real(), 2*z.imag()});
}
void CheckZminusZeq0(const Complex& z) {
  REQUIRE(z - z == Complex{});
}

TEST_CASE("Complex number can be added and subtracted") {
  CheckZplusZeq2Z(1);
  CheckZplusZeq2Z(0);
  CheckZplusZeq2Z(-1);

  CheckZminusZeq0(1);
  CheckZminusZeq0(0);
  CheckZminusZeq0(-1);
  CheckZminusZeq0(Complex{1,2});
  CheckZminusZeq0(Complex{-42, 1e-3});
}

TEST_CASE("Complex numbers can be multiplied") {
  const Complex i{0, 1};
  Complex z{1};
  z = z*i;
  REQUIRE(z == i);
  z = z*i;
  REQUIRE(z == Complex{-1});
  z = z*i;
  REQUIRE(z == -i);
}
