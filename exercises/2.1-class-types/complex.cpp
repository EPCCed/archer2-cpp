#include "complex.hpp"
#include <cmath>

Complex::Complex(double real) : re(real) {
}

Complex::Complex(double real, double imag) : re(real), im(imag) {
}

double Complex::real() {
  return re;
}

double Complex::imag() {
  return im;
}

Complex Complex::conj() {
  return Complex{re, -im};
}

double Complex::norm() {
  return std::sqrt(re*re + im*im);
}

Complex Complex::add(Complex other_complex) {
  return Complex{re + other_complex.re, im + other_complex.im};
}

bool Complex::equals(Complex other_complex) {
  return re == other_complex.re && im == other_complex.im;
}
