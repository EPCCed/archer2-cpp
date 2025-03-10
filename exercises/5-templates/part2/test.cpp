// Catch2 is a unit testing library
// Here we let it create a main() function for us
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "complex.hpp"

TEST_CASE("Complex numbers are constructed real/imag parts readable") {
  const Complex<int> zero;
  REQUIRE(zero.real() == 0.0);
  REQUIRE(zero.imag() == 0.0);

  const Complex<int> one{1};
  REQUIRE(one.real() == 1.0);
  REQUIRE(one.imag() == 0.0);

  const Complex<int> i{0, 1};
  REQUIRE(i.real() == 0.0);
  REQUIRE(i.imag() == 1.0);

  const Complex<int> z1{1, -83};
  const Complex<int> z2 = z1;
  REQUIRE(z1.real() == z2.real());
  REQUIRE(z1.imag() == z2.imag());
  REQUIRE(z2.real() == 1.0);
  REQUIRE(z2.imag() == -83.0);
}

TEST_CASE("Complex numbers can be compared") {
  const Complex<int> zero;
  const Complex<int> one{1};
  const Complex<int> i{0, 1};
  REQUIRE(zero == zero);
  REQUIRE(one == one);
  REQUIRE(i == i);
  REQUIRE(zero != one);
  REQUIRE(zero != i);
  REQUIRE(one != i);
}

TEST_CASE("Complex numbers can have magnitude computed") {
  REQUIRE(Complex<double>{}.norm2() == 0.0);
  REQUIRE(Complex<double>{3,4}.norm2() == 25.0);
}

// Pure real => z == z*
void CheckConjReal(double x) {
  Complex<double> z{x};
  REQUIRE(z == z.conj());
}
// Pure imaginary => z* == -z
void CheckConjImag(double y) {
  Complex<double> z{0.0, y};
  
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

void CheckZplusZeq2Z(const Complex<double>& z) {
  REQUIRE(z + z == Complex<double>{2*z.real(), 2*z.imag()});
}
void CheckZminusZeq0(const Complex<double>& z) {
  REQUIRE(z - z == Complex<double>{});
}

TEST_CASE("Complex number can be added and subtracted") {
  CheckZplusZeq2Z(1);
  CheckZplusZeq2Z(0);
  CheckZplusZeq2Z(-1);

  CheckZminusZeq0(1);
  CheckZminusZeq0(0);
  CheckZminusZeq0(-1);
  CheckZminusZeq0(Complex<double>{1,2});
  CheckZminusZeq0(Complex<double>{-42, 1e-3});
}

TEST_CASE("Complex numbers can be multiplied") {
  const Complex<int> i{0, 1};
  Complex<int> z{1};
  z = z*i;
  REQUIRE(z == i);
  z = z*i;
  REQUIRE(z == Complex<int>{-1});
  z = z*i;
  REQUIRE(z == -i);
}

TEST_CASE("Complex numbers can be templated") {
  const Complex<int> z1{static_cast<int>(3.4), static_cast<int>(5.1)};
  const Complex<double> z2{3.4, 5.1};
  REQUIRE(z1 != z2);
  REQUIRE(z1.real() == 3);
  REQUIRE(z1.imag() == 5);
  REQUIRE(z1.norm2() == 34);
}
