// Catch2 is a unit testing library
// Here we let it create a main() function for us
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "complex.hpp"

TEST_CASE("Complex numbers are constructed real/imag parts readable") {
  Complex zero;
  REQUIRE(zero.real() == 0.0);
  REQUIRE(zero.imag() == 0.0);

  Complex one{1.0};
  REQUIRE(one.real() == 1.0);
  REQUIRE(one.imag() == 0.0);

  Complex i{0, 1};
  REQUIRE(i.real() == 0.0);
  REQUIRE(i.imag() == 1.0);

  Complex z1{1, -83};
  Complex z2 = z1;
  REQUIRE(z1.real() == z2.real());
  REQUIRE(z1.imag() == z2.imag());
  REQUIRE(z2.real() == 1.0);
  REQUIRE(z2.imag() == -83.0);
}

TEST_CASE("Complex numbers can have magnitude computed") {
  REQUIRE(Complex{}.norm() == 0.0);
  REQUIRE(Complex{3,4}.norm() == 5.0);
}

// Pure real => z == z*
void CheckConjReal(double x) {
  Complex z{x};
  Complex z_conj = z.conj();
  REQUIRE(z_conj.equals(z));
}
// Pure imaginary => z* == -z
void CheckConjImag(double y) {
  Complex z{0.0, y};
  Complex expected{0.0, -y};
  Complex z_conj = z.conj();
  REQUIRE(z_conj.equals(expected));
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

TEST_CASE("Complex numbers can be compared") {
  Complex zero;
  Complex one{1.0};
  Complex i{0, 1};
  REQUIRE(zero.equals(zero));
  REQUIRE(one.equals(one));
  REQUIRE(i.equals(i));
  REQUIRE(!zero.equals(one));
  REQUIRE(!zero.equals(i));
  REQUIRE(!one.equals(i));
}

void CheckZplusZeq2Z(Complex z) {
  Complex expected = Complex{2*z.real(), 2*z.imag()};
  Complex result = z.add(z);
  REQUIRE(result.equals(expected));
}
void CheckZminusZeq0(Complex z) {
  Complex expected = Complex{};
  Complex z_minus = Complex{-z.real(), -z.imag()};
  Complex result = z.add(z_minus);
  REQUIRE(result.equals(expected));
}

TEST_CASE("Complex number can be added") {
  CheckZplusZeq2Z(1);
  CheckZplusZeq2Z(0);
  CheckZplusZeq2Z(-1);
  CheckZplusZeq2Z(Complex{1, 2});
  CheckZplusZeq2Z(Complex{-42, 1e-3});

  CheckZminusZeq0(1);
  CheckZminusZeq0(0);
  CheckZminusZeq0(-1);
  CheckZminusZeq0(Complex{1, 2});
  CheckZminusZeq0(Complex{-42, 1e-3});
}